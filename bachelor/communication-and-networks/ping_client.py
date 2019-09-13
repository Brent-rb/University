__author__ = 'Brent Berghmans 1334252'

import socket
import time
import sys

class PingClient:
    def __init__(self, ip, port, pings):
        self.mIp = ip
        self.mPort = port
        self.prepareSocket()
        self.mPings = int(pings)
        #Clamp pings
        if pings < 1:
            self.mPings = 4
        elif pings > 999:
            self.mPings = 999

    def prepareSocket(self):
        self.mSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.mSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.mSocket.settimeout(5.0)

    def start(self):
        i = 0
        totalMillis = 0
        timeOuts = 0
        try:
            #make connection
            self.mSocket.connect((self.mIp, self.mPort))
            resp = ""

            while i < self.mPings:
                #Base timeout
                self.mSocket.settimeout(5.0)
                #Send ping
                self.mSocket.send("PING-" + str(i) + "!")
                try:
                    #Reset millis
                    millis = 0
                    #Keep trying to receive data until we time out or receive a valid response
                    while resp != str("PONG-" + str(i) + "!"):
                        time1 = time.time()
                        resp, addr = self.mSocket.recvfrom(32)
                        time2 = time.time()
                        #Calculate time since send and receive
                        #Add to millis
                        millis += (time2 - time1) * 1000.0
                        totalMillis += millis

                        #If this message is nog correct, we should try again but with less timeout
                        if resp != str("PONG-" + str(i) + "!"):
                            self.mSocket.settimeout(5.0 - (millis / 1000.0))

                    #If we are here we got a response
                    print str(i) + ": %dms" % int(millis)

                #On timeout
                except socket.timeout as msg:
                    timeOuts = timeOuts + 1
                    print str(i) + ": timeout"

                i = i + 1

            noemer = i - timeOuts
            if noemer == 0:
                noemer = 1
            print "AVG=%dms TIMEOUTS=%d" % (int(totalMillis / float(noemer)), timeOuts)

        except socket.error as msg:
            noemer = i - timeOuts
            if noemer == 0:
                noemer = 1
            print "AVG=%dms TIMEOUTS=%d" % (int(totalMillis / float(noemer)), timeOuts)


if len(sys.argv) == 2:
    client = PingClient(sys.argv[1], 2000, 4)
elif len(sys.argv) == 3:
    client = PingClient(sys.argv[1], 2000, int(sys.argv[2]))
else:
    exit()
client.start()