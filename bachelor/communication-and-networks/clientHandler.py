__author__ = 'Brent Berghmans 1334252'

from threading import Thread
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

    def removeUntilNewline(buffer):
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
            while True:
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
        self.mServer.onClientExit(self, stop)

    def __init__(self, comNeServer, clientSocket, clientAddress):
        self.mSocket = clientSocket
        self.mAddress = clientAddress
        self.mServer = comNeServer
        self.mThread = Thread(target=self.doInBackground)

    def execute(self):
        self.mThread.start()

    def join(self):
        self.mThread.join()