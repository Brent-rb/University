__author__ = 'Brent Berghmans 1334252'

import socket
import re
import time
from threading import Thread
from threading import Lock
import random
import math

#Shitty Timer class but it does the job
class Timer:
    def __init__(self, object, function, millis, parameters):
        self.mObject = object
        self.mFunction = function
        self.mMillis = millis
        self.mOriginalMillis = millis
        self.mParams = parameters
        self.mParams.append(self)
        self.mMillisLock = Lock()
        self.mThread = Thread(target=self.doInBackground)

    def start(self):
        self.mThread.start()

    def reset(self):
        self.mMillisLock.acquire()
        self.mMillis = self.mOriginalMillis
        self.mMillisLock.release()

    def doInBackground(self):
        while True:
            self.mMillisLock.acquire()
            self.mMillis -= 1
            shouldStop = self.mMillis < 0
            self.mMillisLock.release()

            if shouldStop:
                break
            else:
                time.sleep(0.001)

        try:
            function = getattr(self.mObject, self.mFunction)
            function(self.mParams)
        except AttributeError:
            print "Could not find function"
            return

class PongServer:
    def __init__(self, ip, port):
        self.mIp = ip
        self.mPort = port
        self.mPattern = re.compile("PING\-([0-9]){1,3}\!")
        self.mTimers = dict()
        self.mClientSettings = dict()
        self.mResponseTimers = list()
        self.mClientSettingsLock = Lock()
        self.mResponseTimersLock = Lock()
        self.prepareSocket()

    def prepareSocket(self):
        self.mSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.mSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.mSocket.bind((self.mIp, self.mPort))

    def start(self):
        while True:
            try:
                data, client = self.mSocket.recvfrom(1024)
                #returns -1 if it's incorrect
                number = self.parseData(data)

                #Only valid numbers (which means a valid message) will get a response
                if number >= 0 and number <= 999:
                    #Client iden is ip:port
                    clientIden = (str(client[0]) + ":" + str(client[1]))

                    #If this client is not known generate settings for him etc
                    if not self.clientIn(clientIden):
                        self.addClient(clientIden)
                    #Else reset his clear timer
                    else:
                        self.resetTimer(clientIden)

                    settings = self.getClientSettings(clientIden)
                    waitTime = self.generateWaitTime(settings)

                    if waitTime > 5000:
                        print 'Timeout for: ' + clientIden

                    self.makeResponse(client[0], client[1], number, waitTime)

            except socket.error:
                print "Exception"


    def stopServer(self):
        self.mSocket.shutdown()

    #Generate a random delay based on the RTT and variance e calculated
    def generateWaitTime(self, settings):
        base = settings[0]
        variance = settings[1]

        """
        TIMEOUT GENERATING CODE
        rand = random.randint(0, 100)
        if rand > 99:
            return 100000
        else:
            return base + random.random() * variance
        """

        return base + random.random() * variance


    def parseData(self, data):
        if self.mPattern.match(data):
            number = data.split("-")[1]
            number = number[:len(number) - 1]
            return int(number)
        else:
            return -1

    def getClientSettings(self, clientIden):
        self.mClientSettingsLock.acquire()
        result = self.mClientSettings[clientIden]
        self.mClientSettingsLock.release()
        return result

    def clientIn(self, clientIden):
        self.mClientSettingsLock.acquire()
        result = clientIden in self.mClientSettings
        self.mClientSettingsLock.release()
        return result

    def resetTimer(self, clientIden):
        self.mClientSettingsLock.acquire()
        self.mTimers[clientIden].reset()
        self.mClientSettingsLock.release()

    def addClient(self, clientIden):
        #Every client gets a random RTT and a variance on top of this RTT
        #Just a random algorithm I made up on the spot
        rand = random.randint(1, 4)
        maxMillis = rand * 50
        minMillis = int(math.floor(float(rand) / 2.0)) * 50

        baseMillis = (random.random() * (maxMillis - minMillis)) + minMillis
        if baseMillis < 15:
            baseMillis = baseMillis + 1
        variance = (random.random() * math.sqrt(baseMillis)) + (baseMillis * 0.10)
        baseMillis /= 3.0
        if baseMillis < 10:
            baseMillis = baseMillis + 10
        variance /= 3.0

        print "Added settings for " + clientIden + " base RTT: %.3fms, variane: %.3fms" % (baseMillis * 2.0, variance * 2.0)

        #Make a tupple for these settings
        clientSettings = (baseMillis, variance)
        #We need to make a list like this otherwise it's not a list but a tupple, this is for the param of the timer
        tempList = list()
        tempList.append(clientIden)
        #After this timer has passed we should remove this client
        timer = Timer(self, "clearClient", 10000, tempList)
        #Add this client's settings  and timers
        self.mClientSettingsLock.acquire()
        self.mClientSettings[clientIden] = clientSettings
        self.mTimers[clientIden] = timer
        self.mClientSettingsLock.release()

        timer.start()


    #clear a client from the settings, so we can generate a new one when he comes back
    def clearClient(self, params):
        clientIden = params[0]
        self.mClientSettingsLock.acquire()
        self.mClientSettings.pop(clientIden)
        self.mClientSettingsLock.release()

    def makeResponse(self, clientIp, clientPort, clientNumber, waitTime):
        #Send a response after the waittime has passed
        timer = Timer(self, "sendResponse", waitTime, list((clientIp, clientPort, clientNumber)))
        self.mResponseTimersLock.acquire()
        self.mResponseTimers.append(timer)
        self.mResponseTimersLock.release()

        timer.start()

    #params are like this because of the timer class
    def sendResponse(self, params):
        clientIp = params[0]
        clientPort = params[1]
        clientNumber = params[2]
        timer = params[3]

        #try to send a response
        try:
            toSend = "PONG-" + str(clientNumber) + "!"
            self.mSocket.sendto(toSend, (clientIp, clientPort))
        except socket.error as msg:
            print 'Exception, could not send data back to client.'

        #remove this delay timer from the list
        self.mResponseTimersLock.acquire()
        self.mResponseTimers.remove(timer)
        self.mResponseTimersLock.release()


pongServer = PongServer("localhost", 2000)
pongServer.start()