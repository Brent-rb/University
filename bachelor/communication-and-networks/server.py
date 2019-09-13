__author__ = 'Brent Berghmans 1334252'

import socket
import time

def startServer(ip, port):
    #print 'Start'
    #Ask socket
    soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #Request port does not linger on after closing socket
    soc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:
        #print 'Bind'
        #Let socket know what ip/port we want to use

        soc.bind((ip, port))
        startToListen(soc)
        #print 'Close'
        soc.close()

    except socket.error as msg:
        print 'Exception occured on binding socket.'


def startToListen(soc):
    try:
        stop = False

        while not stop:
            #print 'Listen'
            soc.listen(1)
            #print 'Accept'
            clientSocket, clientAddress = soc.accept()
            #print 'Enter'
            stop = readCommands(clientSocket, clientAddress)
            #print 'Close Client'
            clientSocket.close()

    except socket.error as msg:
        print 'Exception occured in listen loop.'

def doCommand(clientSocket, clientAddress, command):
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
        return False

    return False

def checkBuffer(clientSocket, clientAddress, buffer):
    command = ''

    if '\r\n' in buffer:
        list = buffer.split('\r\n')
        command = list[0]
        shouldStop = doCommand(clientSocket, clientAddress, command)
        buffer = buffer[len(command) + 2:]
        if shouldStop:
            return ('', True)
        else:
            return checkBuffer(clientSocket, clientAddress, buffer)
    elif '\n' in buffer:
        list = buffer.split('\n')
        command = list[0]
        shouldStop = doCommand(clientSocket, clientAddress, command)
        buffer = buffer[len(command) + 1:]
        if shouldStop:
            return ('', True)
        else:
            return checkBuffer(clientSocket, clientAddress, buffer)
    else:
        return (buffer, False)

def removeUntilNewline(buffer):
    if '\n' in buffer:
        list = buffer.split('\n')
        command = list[0]
        buffer = buffer[len(command) + 1:]
        return (buffer, True)
    else:
        return ('', False)

def readCommands(clientSocket, clientAddress):
    clientSocket.settimeout(30)
    buffer = ''

    try:
        while True:
            data = clientSocket.recv(1024)
            if not data:
                break
            else:
                if len(buffer) > 6:
                    returntupple = removeUntilNewline(data)
                    reset = returntupple[1]
                    data = ''
                    if reset:
                        buffer = returntupple[0]


                buffer += data
                returntupple = checkBuffer(clientSocket, clientAddress, buffer)

                buffer = returntupple[0]

                if returntupple[1]:
                    return True

        return False

    except socket.error as msg:
        print 'Exception occured in commando loop'
        return False

startServer('localhost', 2000)
