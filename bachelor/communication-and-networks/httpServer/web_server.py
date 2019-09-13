import socket
import re
from threading import Thread
from threading import Lock
import os
from mimetypes import MimeTypes
import Queue

class ClientHandler:
    def __init__(self, clientSocket, clientAddress):
        print "New thread."
        self.mSocket = clientSocket
        self.mSocket.settimeout(15)
        self.mAddress = clientAddress
        self.mRequestQueue = Queue.Queue()
        self.mStop = False
        self.mStopLock = Lock()
        self.mThread = Thread(target=self.doInBackground)
        self.mRequestRe = re.compile("^(.|\r\n)*?(GET (.)* HTTP\\/1\\.(1|0)\r\n(.|\r\n)+?\r\n\r\n)")
        self.mGetCounter = 0
        self.mShouldStop = False

    def runLoop(self):
        self.mBuffer = ''

        try:
            while not self.mShouldStop:
                self.mSocket.settimeout(30)
                data = self.mSocket.recv(1024)
                if not data:
                    break

                self.mBuffer = self.mBuffer + data
                #Check if the buffer contains requests
                self.parseReceive()
                #Send requested files if we have them
                self.sendFile()


            print "Thread handled: " + str(self.mGetCounter) + " gets."
        except socket.timeout:
            if len(self.mBuffer.strip()) != 0:
                self.sendBadRequest()
            else:
                self.sendTimeout()
        except socket.error:
            try:
                self.mSocket.close()
            #Dont know how to do a "NOP" in python
            except socket.error:
                x = 10


    def parseReceive(self):
        while True:
            #Check if the regex matches
            matches = self.mRequestRe.match(self.mBuffer)
            if not matches:
                break

            #This one is the part of the string we need
            match = matches.groups()[1]
            if not match:
                break
            else:
                #Make a request based on string
                request = HttpRequest(match)
                if not request.mInvalid:
                    self.mGetCounter = self.mGetCounter + 1

                    #Get path and make it safe
                    path = str(request.mPath)
                    if path.startswith("/"):
                        path = "." + path
                    #Respond with index if they enter a directory
                    if path.endswith("/"):
                        path = path + "index.html"

                    request.mPath = path
                    self.mRequestQueue.put(request)
                    #Remove this match from buffer
                    self.mBuffer = self.mBuffer[len(match):]

    def sendFile(self):
        #If we don't need to send files, return
        if self.mRequestQueue.empty():
            return

        #Get some values
        request = self.mRequestQueue.get()
        filepath = request.getURL()
        connection = "close"
        if request.containsKey("Connection"):
            connection = request.getParam("Connection")

        #Check if file exists
        if not os.path.isfile(filepath):
            print filepath
            self.sendNotFound()
            if connection.lower() == "close":
                self.mShouldStop = True
            return

        try:
            #Open file
            file = open(filepath, "rb")
            size = os.path.getsize(filepath)
            #Get mime type
            mime = MimeTypes()
            mime_type = mime.guess_type(filepath)

            if file.closed:
                self.sendNotFound()
                if connection.lower() == "close":
                    self.mShouldStop = True
                    return

            #Send header
            self.mSocket.send("HTTP/1.1 200 OK\r\nContent-Length: " + str(size) + "\r\nContent-Type: " + str(mime_type[0]) + "\r\n" + "Connection: " + connection + "\r\n\r\n")

            #Init
            bufferData = file.read(5024)
            self.mSocket.send(bufferData)
            #Keep sending as long as we have data
            while bufferData:
                bufferData = file.read(5024)
                if not bufferData:
                    break

                self.mSocket.send(bufferData)
                #Do a non blocking read to support more than one get request per socket
                self.mSocket.setblocking(0)
                try:
                    data = self.mSocket.recv(1024)
                    #If we have data, try to parse requests
                    if data:
                        self.mBuffer = self.mBuffer + data
                        self.parseReceive()
                except:
                    data = False

                #Enable blocking again
                self.mSocket.setblocking(1)

            file.close()
            if connection.lower() == "close":
                print "Shutting down connection because of connection: close"
                self.mSocket.close()
                self.mShouldStop = True
        except:
            self.sendBadRequest()
            print "Exception in send."

        #Work off the files recursive because we check for more requests in the send loop
        self.sendFile()


    def sendNotFound(self):
        self.mSocket.send("HTTP/1.1 404 Not Found\r\n\r\n<html><body>404 File not found.</body></html>")

    def sendBadRequest(self):
        try:
            self.mSocket.send("HTTP/1.1 400 Bad Request\r\n\r\n<html><body>400 Bad Request.</body></html>")
            self.mSocket.close()
            self.mShouldStop = True
        except:
            print "Exception occurred when sending 400 Bad request."

    def sendTimeout(self):
        try:
            self.mSocket.send("HTTP/1.1 408 Request Timeout\r\n\r\n<html><body>408 Request Timeout.</body></html>")
            self.mSocket.close()
            self.mShouldStop = True
        except:
            print "Exception occurred when sending 408 Request Timeout."

    def doInBackground(self):
        stop = self.runLoop()
        self.mSocket.close()

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

class HttpRequest:
    def __init__(self, text):
        self.mInvalid = True
        self.mParams = dict()
        self.mPath = False
        self.parse(text)

    def init(self, method, url, http1_1):
        self.mHeaders = dict()
        #If the url is empty, we need to add a / for root
        if not url[2]:
            self.setUrl("/")
        else:
            self.setUrl(url[2])
        self.setHost(url[1])
        self.setMethod(str(method).strip())
        self.setHttp1_1(http1_1)

    def setHeader(self, headerName, headerValue):
        self.mHeaders[headerName] = headerValue

    def clearHeaders(self):
        self.mHeaders.clear()

    def setHost(self, host):
        self.setHeader("Host", host)

    def setUrl(self, url):
        self.mUrl = url

    def setMethod(self, method):
        self.mMethod = method

    def setHttp1_1(self, http1_1):
        if http1_1:
            self.mVersion = "1.1"
        else:
            self.mVersion = "1.0"

    def containsKey(self, key):
        return (key in self.mParams)

    def getParam(self, key):
        return self.mParams[key]

    def getHeaderQuery(self):
        toRet = ""

        for key, value in self.mHeaders.iteritems():
            toRet = toRet + str(key) + ": " + str(value) + "\r\n"

        #self.printResponse(oRet
        return toRet

    def getIdentifierQuery(self):
        toRet = ""

        toRet = toRet + str(self.mMethod) + " " + self.mUrl + " HTTP/" + self.mVersion + "\r\n"
        #self.printResponse(oRet
        return toRet

    def getHttpRequest(self):
        toRet = self.getIdentifierQuery()
        toRet = toRet + self.getHeaderQuery()
        toRet = toRet + "\r\n\r\n"
        #self.printResponse(oRet
        return toRet

    def getURL(self):
        return self.mPath

    def parse(self, text):
        self.mInvalid = False

        #Split on \r\n
        splits = re.split("\r\n", text)
        httpFound = False

        for split in splits:
            #If we have not found the first line
            if not httpFound:
                #Check if the line matches the first line of an HTTP request
                if re.match("GET .* HTTP\\/1\\.(1|0)", split):
                    httpFound = True
                    url = split[4:].strip()
                    versNo = url[len(url) - 9:]
                    url = url[0: len(url) - len(versNo)].strip()
                    versNo = versNo[6:].strip()

                    self.mPath = url

                    if versNo == "1.0":
                        self.mHttpVersion = 10
                    elif versNo == "1.1":
                        self.mHttpVersion = 11
                    elif versNo == "2.0":
                        self.mHttpVersion = 20
                else:
                    continue
            #If we have found the first line
            else:
                #We should be able to split on ":"
                if re.match(".*:.*", split):
                    headerSplit = re.split(":", split)
                    left = headerSplit[0].strip()
                    right = ""
                    #There might be more than one ":", just concatenate
                    for i in range(1, len(headerSplit)):
                        if i == 1:
                            right = headerSplit[i]
                        else:
                            right = right + ":" + headerSplit[i]
                    right = right.strip()
                    self.mParams[left] = right



class HttpServer:
    def __init__(self):
        self.mInvalid = False
        self.mPort = 8080

    def open(self):
        self.mSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.mSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.mSocket.bind(("localhost", self.mPort))
        self.mSocket.listen(1)
        self.mStop = False

    def close(self):
        self.mSocket.close()

    def runServer(self):
        self.open()
        counter = 0
        while True:
            clientSocket, clientAddress = self.mSocket.accept()
            #Make new handler
            clientHandler = ClientHandler(clientSocket, clientAddress)
            #Start it
            clientHandler.execute()
            counter = counter + 1
            print "Sockets opened: " + str(counter)

server = HttpServer()
server.runServer()
