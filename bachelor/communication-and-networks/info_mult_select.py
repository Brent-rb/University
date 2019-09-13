__author__ = 'Brent Berghmans 1334252'

import socket
import select
import time

class ComNeServer:
    def addOpenClient(self, client, address):
        #Add client socket to the open client list
        self.mOpenClients.append(client)
        #Add his address to the dictionary
        self.mClientAddresses[client] = address
        #Initialise his buffer to be empty
        self.mClientBuffers[client] = ""

    def removeOpenClient(self, client):
        #Remove client from the open client list
        self.mOpenClients.remove(client)
        #Remove him from the buffer dictionary
        self.mClientBuffers.pop(client, "")
        #Remove him from the address dictionary
        self.mClientAddresses.pop(client, "")

    def isReady(self):
        return self.mSocketReady

    def prepareSocket(self):
        #Ask socket
        self.mSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #Request port does not linger on
        #self.mSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        try:
            self.mSocket.bind((self.mIp, self.mPort))
            self.mSocketReady = True

        except socket.error as msg:
            print "Exception occured on binding socket."

    def startListenServer(self):
        try:
            #Init
            self.mStop = False
            #Add server socket to the ready list
            self.mOpenClients.append(self.mSocket)
            #Stop var for the loop
            shouldStop = False
            #Initial listen
            self.mSocket.listen(1)

            while not shouldStop:
                #Catch timeouts
                try:
                    #Select using the client list
                    resultLists = select.select(self.mOpenClients, list(), self.mOpenClients, 30)

                    #Get the result lists
                    errorList = resultLists[2]
                    writeList = resultLists[1]
                    readyList = resultLists[0]

                    if not errorList and not writeList and not readyList:
                        print 'Timeout'
                        listCopy = list(self.mOpenClients)

                        for soc in listCopy:
                            if soc is not self.mSocket:
                                try:
                                    soc.close()
                                except socket.error as msg:
                                    print "Socket close caused an exception."

                                self.removeOpenClient(soc)

                    #Close all error sockets
                    for soc in errorList:
                        print 'Socket error.'
                        #This could throw an exception is a closed socket is being closed again I think but I'm not sure, just in case
                        try:
                            soc.close()
                        except socket.error as msg:
                            print "Socket close caused an exception in startListenServer Loop."

                        #Remove from the ready list
                        self.removeOpenClient(soc)

                    #Check the other list
                    for soc in readyList:
                        #If the current socket is the server socket, this means we can call an accept()
                        if soc is self.mSocket:
                            print 'Accepted new client.'
                            #Accept client
                            tempSoc, tempAddress  = soc.accept()
                            #Add him to the list
                            self.addOpenClient(tempSoc, tempAddress)
                            #Listen for new connections
                            self.mSocket.listen(1)

                        #If it's not the server socket it's a client
                        else:
                            #Handle the client
                            retval = self.handleSocket(soc, self.mClientAddresses[soc])
                            #If the return value is True we got an EXIT command, but it could be a second EXIT command so we only do something when our member var is changed
                            if retval and not self.mStop:
                                #Remove server socket from list
                                self.mOpenClients.remove(self.mSocket)
                                #Close it so new clients can't connect
                                self.mSocket.close()
                                #Update member var to know we already had an EXIT
                                self.mStop = True

                    if self.mStop:
                        copyList = list(self.mOpenClients)
                        for soc in copyList:
                            soc.close()
                            self.removeOpenClient(soc)

                    #If we should stop AND we have no more connected clients -> stop loop, else keep going for open clients
                    if self.mStop and len(self.mOpenClients) == 0:
                        shouldStop = True

                #Timeouts are no problem, that's why it's in the loop
                except socket.timeout as msg:
                    print "Timeout in listen loop, continuing."

        #Other exceptions will need to stop the loop
        except socket.error as msg:
           print "Exception occured in listen loop. Aborting"


    #Code is the same as in the old tasks, this is one 'step' of the old loop, modified to use member variables
    def handleSocket(self, clientSocket, clientAddress):
        try:
            data = clientSocket.recv(1024)
            buffer = self.mClientBuffers[clientSocket]
            if not data:
                try:
                    clientSocket.close()
                except socket.error as msg:
                    print "Exception in handleSocket"

                self.removeOpenClient(clientSocket)
            else:
                if len(buffer) > 6:
                    returntupple = self.removeUntilNewline(data)
                    reset = returntupple[1]
                    data = ''
                    if reset:
                        clientSocket.send("Invalid Command.")
                        buffer = returntupple[0]

                buffer += data
                returntupple = self.checkBuffer(clientSocket, clientAddress, buffer)

                buffer = returntupple[0]
                self.mClientBuffers[clientSocket] = buffer

                if returntupple[1]:
                    clientSocket.close()
                    self.removeOpenClient(clientSocket)
                    return True

            return False

        except socket.error as msg:
            self.removeOpenClient(clientSocket)
            return False


    #Old code modified to give more feedback this time and use member vars
    def doCommand(self, clientSocket, clientAddress, command):
        try:
            if 'IP' == command:
                print 'Command Valid: IP'
                clientSocket.send(clientAddress[0])
            elif 'TIME' == command:
                print 'Command Valid: TIME'
                clientSocket.send(time.ctime())
            elif 'EXIT' == command:
                print 'Command Valid: EXIT'
                clientSocket.send("Exiting...")
                return True
            else:
                print 'Command Invalid: ' + command
                clientSocket.send("Invalid Command.")

        except socket.error as msg:
            self.removeOpenClient(clientSocket)
            return False

        return False

    #Old code, not really modified
    def checkBuffer(self, clientSocket, clientAddress, buffer):
        command = ''

        if '\r\n' in buffer:
            list = buffer.split('\r\n')
            command = list[0]
            shouldStop = self.doCommand(clientSocket, clientAddress, command)
            buffer = buffer[len(command) + 2:]
            if shouldStop:
                return ('', True)
            else:
                return self.checkBuffer(clientSocket, clientAddress, buffer)
        elif '\n' in buffer:
            list = buffer.split('\n')
            command = list[0]
            shouldStop = self.doCommand(clientSocket, clientAddress, command)
            buffer = buffer[len(command) + 1:]
            if shouldStop:
                return ('', True)
            else:
                return self.checkBuffer(clientSocket, clientAddress, buffer)
        else:
            return (buffer, False)

    #Old code, not modified
    def removeUntilNewline(self, buffer):
        if '\n' in buffer:
            list = buffer.split('\n')
            command = list[0]
            buffer = buffer[len(command) + 1:]
            return (buffer, True)
        else:
            return ('', False)


    def __init__(self, ip, port):
        self.mIp = ip
        self.mPort = port
        self.mSocketReady = False
        self.mStop = False
        self.mOpenClients = list()
        self.mClientAddresses = dict()
        self.mClientBuffers = dict()
        self.prepareSocket()


server = ComNeServer("localhost", 2000)
if server.isReady():
    server.startListenServer()
