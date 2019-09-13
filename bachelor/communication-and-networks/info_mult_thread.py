__author__ = 'Brent Berghmans 1334252'

import socket
from threading import Lock
from threading import Thread
from threading import ThreadError
import socket
import time

class ClientHandler:
    def doCommand(self, command):
        try:
            if 'IP' == command:
                print 'Command Valid: IP'
                self.mSocket.send(self.mAddress[0])
            elif 'TIME' == command:
                print 'Command Valid: TIME'
                self.mSocket.send(time.ctime())
            elif 'EXIT' == command:
                print 'Command Valid: EXIT'
                self.mSocket.send("Exiting...")
                return True
            else:
                print 'Command Invalid: ' + command
                self.mSocket.send("Invalid Command.")

        except socket.error as msg:
            return False

        return False

    def checkBuffer(self):
        if '\r\n' in self.mBuffer:
            list = self.mBuffer.split('\r\n')
            command = list[0]
            shouldStop = self.doCommand(command)
            self.mBuffer = self.mBuffer[len(command) + 2:]
            if shouldStop:
                return ('', True)
            else:
                return self.checkBuffer()

        elif '\n' in self.mBuffer:
            list = self.mBuffer.split('\n')
            command = list[0]
            shouldStop = self.doCommand(command)
            self.mBuffer = self.mBuffer[len(command) + 1:]
            if shouldStop:
                return ('', True)
            else:
                return self.checkBuffer()
        else:
            return (self.mBuffer, False)

    def removeUntilNewline(self, buffer):
        if '\n' in buffer:
            list = buffer.split('\n')
            command = list[0]
            buffer = buffer[len(command) + 1:]
            return (buffer, True)
        else:
            return ('', False)

    def runLoop(self):
        self.mSocket.settimeout(30)
        self.mBuffer = ''

        try:
            while not self.getStop():
                data = self.mSocket.recv(1024)
                if not data:
                    break

                else:
                    if len(self.mBuffer) > 6:
                        returntupple = self.removeUntilNewline(data)
                        reset = returntupple[1]
                        data = ''
                        if reset:
                            self.mSocket.send("Invalid Command.")
                            self.mBuffer = returntupple[0]

                    self.mBuffer += data
                    returntupple = self.checkBuffer()

                    self.mBuffer = returntupple[0]

                    if returntupple[1]:
                        return True

            return False

        except socket.error as msg:
            print 'Exception in commando loop'
            return False

    def doInBackground(self):
        stop = self.runLoop()
        self.mSocket.close()
        #We must let the server know we're finished so he can remove us from the list and we can (if we need to) stop the server.
        self.mServer.onClientExit(self, stop)

    def __init__(self, comNeServer, clientSocket, clientAddress):
        self.mSocket = clientSocket
        self.mAddress = clientAddress
        self.mServer = comNeServer
        self.mStop = False
        self.mStopLock = Lock()
        self.mThread = Thread(target=self.doInBackground)

    def getStop(self):
        self.mStopLock.acquire()
        retVal = self.mStop
        self.mStopLock.release()
        return retVal

    def setStop(self, value):
        self.mStopLock.acquire()
        self.mStop = value
        self.mStopLock.release()

    def execute(self):
        self.mThread.start()

    def join(self):
        self.mThread.join()

class ComNeServer:
    def stopServer(self):
        print 'Stopping server.'
        self.mSocket.close()

        stop = False
        print 'Closing clients.'
        self.mOpenClientsLock.acquire()
        #Clients will stop in their next interation (maximum wait time = timeout time.)
        for handler in self.mOpenClients:
            handler.setStop(True)
        self.mOpenClientsLock.release()

        print 'Waiting for clients to finish.'
        while not stop:
            empty = False
            self.mOpenClientsLock.acquire()
            empty = not self.mOpenClients
            self.mOpenClientsLock.release()

            if empty:
                stop = True
            else:
                self.mOpenClientsLock.acquire()
                clientList = list(self.mOpenClients)
                first = clientList[0]
                self.mOpenClientsLock.release()

                try:
                    first.join()
                except ThreadError as msg:
                    print "Thread error, but it's no problem."

        #If we're here all clients should have been handled.
        print 'All clients have been closed.'
        #Dummy connection if server is stil waiting on an accept
        self.makeDummyConnection()

    #Sometimes the server is still waiting for an accept, we use a dummy connection to bypass this
    def makeDummyConnection(self):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s.connect(('localhost', 2000))
            s.close()

        except socket.error as msg:
            print "Server is already closed, dummy connection wasn't needed"

    def addOpenClient(self, client):
        self.mOpenClientsLock.acquire()
        self.mOpenClients.add(client)
        self.mOpenClientsLock.release()

    def removeOpenClient(self, client):
        self.mOpenClientsLock.acquire()
        self.mOpenClients.remove(client)
        self.mOpenClientsLock.release()

    def setStop(self, value):
        self.mStopLock.acquire()
        self.mStop = value
        self.mStopLock.release()

    def onClientExit(self, client, shouldStop):
        self.removeOpenClient(client)
        self.setStop(shouldStop)
        if shouldStop:
            self.stopServer()

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
            self.mStop = False

            while not self.mStop:
                self.mSocket.listen(1)
                #Accept client
                clientSocket, clientAddress = self.mSocket.accept()
                #Make a clienthandler
                client = ClientHandler(self, clientSocket, clientAddress)
                #Add it to the open list
                self.addOpenClient(client)
                print 'Going to launch new thread.'
                #Execute in new thread
                client.execute()

                print 'Thread Launched'

        except socket.error as msg:
            print "Exception occured in listen loop."


    def __init__(self, ip, port):
        self.mIp = ip
        self.mPort = port
        self.mSocketReady = False
        self.mStop = False
        #List of clientHandlers still open.
        self.mOpenClients = set()
        self.mOpenClientsLock = Lock()
        self.mStopLock = Lock()
        self.prepareSocket()


server = ComNeServer("localhost", 2000)
if server.isReady():
    server.startListenServer()
