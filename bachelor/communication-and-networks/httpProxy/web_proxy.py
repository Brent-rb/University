__author__ = 'Brent Berghmans 1334252'

import hashlib
import socket
import re
from threading import Thread
from threading import Lock
import Queue
import os
import sys
import time
from email.utils import formatdate

class HostReplacer:
    def __init__(self, file = False):
        self.mDict = dict()
        if not file:
            return

        self.readFile(file)

    def readFile(self, filename):
        try:
            with open(filename, 'r') as f:
                for line in f:
                    line = line.strip()
                    if not line.startswith("#"):
                        splits = line.split(" ")
                        if len(splits) == 2:
                            self.mDict[splits[0]] = splits[1]
                        else:
                            print("Error, line contains 3 parameters: " + line + ", skipping this line.")
        except:
            print("Exception occurred with file.")

    def replace(self, string):
        if string in self.mDict:
            return self.mDict[string]
        else:
            return string

    def substringReplace(self, string):
        for key, value in self.mDict.iteritems():
            if key.lower() in string.lower() or key.lower() == string.lower():
                replaced = string.lower().replace(key, value)
                print string + " -> " + replaced
                return replaced

        return string

class HTTPCache:
    def __init__(self):
        self.mMD5 = hashlib.md5()
        self.mDict = dict()
        self.mValues = self.mDict.values()

    def generateHash(self, string):
        hash = self.generateUniqueHash(string)
        self.mDict[string] = hash
        self.mValues = self.mDict.values()
        return hash

    def generateUniqueHash(self, string):
        hash = ""

        self.mMD5.update(string)
        hash = self.mMD5.hexdigest()
        self.mMD5 = hashlib.md5()
        baseHash = hash

        return baseHash

    def getHash(self, key):
        if key in self.mDict:
            return self.mDict[key]
        elif key + "/" in self.mDict:
            return self.mDict[key + "/"]
        else:
            return False

    def containsKey(self, key):
        return key in self.mDict or key + "/" in self.mDict

    def containsValue(self, value):
        return value in self.mValues

    def remove(self, key):
        if self.containsKey(key):
            self.mDict.pop(key)
        elif self.containsKey(key + "/"):
            self.mDict.pop(key + "/")

    def insert(self, key, value):
        self.mDict[key] = value
        self.mValues = self.mDict.values()

class HTTPFileCache:
    def __init__(self):
        self.mCache = HTTPCache()
        self.mLock = Lock()

    def checkCacheDir(self):
        if not os.path.isdir('./cache'):
            os.makedirs('./cache')

    def fileIsCached(self, url):
        #Check if in our memory cache
        self.mLock.acquire()
        outcome = self.mCache.containsKey(url)
        self.mLock.release()
        #If not in our memory cache, check file system
        if not outcome:
            #print "Checking files;"
            hash1 = self.mCache.generateUniqueHash(url)
            hash2 = self.mCache.generateUniqueHash(url + "/")
            print
            if os.path.isfile("./cache/" + hash1 + ".tmp"):
                #print "Hash1 exists"
                self.mCache.insert(url, hash1)
                outcome = True
            elif os.path.isfile("./cache/" + hash2 + ".tmp"):
                #print "Hash2 exists"
                self.mCache.insert(url + "/", hash2)
                outcome = True
        return outcome

    def getReadFilePointer(self, url):
        #Get hashed name from cache
        self.mLock.acquire()
        hash = self.mCache.getHash(url)
        self.mLock.release()
        #open file pointer
        f = open('cache/' + hash + ".tmp", 'rb')
        return f

    def getWriteFilePointer(self, url):
        self.checkCacheDir()
        hash = ""
        #Check if file is cached
        test = self.fileIsCached(url)
        self.mLock.acquire()
        #If cached, get the hash
        if test:
            hash = self.mCache.getHash(url)
        #If not, generate a hash and put in cache
        else:
            hash = self.mCache.generateHash(url)
        self.mLock.release()

        #If file exists, we delete it
        if not os.path.exists('cache/' + str(hash) + ".tmp"):
            f = False
        else:
            os.remove('cache/' + str(hash) + ".tmp")

        #Open write file pointer
        f = open('cache/' + str(hash) + ".tmp", 'w+b')
        return f

    def removeFile(self, url):
        test = self.fileIsCached(url)
        self.mLock.acquire()
        try:
            if test:
                hash = self.mCache.getHash(url)
                if os.path.exists('cache/' + str(hash) + '.tmp'):
                    os.remove('cache/' + str(hash) + '.tmp')
                    self.mCache.remove(url)
        except:
            print "Error occured when deleting file."
        self.mLock.release()




#################
#    Entry      #
#    Point      #
#################
class ClientHandler:
    def __init__(self, clientSocket, clientAddress, fileCache, hostReplacer):
        self.mSocket = clientSocket
        self.mAddress = clientAddress
        self.mRequestQueue = Queue.Queue()
        self.mThread = Thread(target=self.doInBackground)
        self.mGetRequestRe = re.compile("^(.|\r\n)*?(GET (.)* HTTP\\/1\\.(1|0)\r\n(.|\r\n)+?\r\n\r\n)")
        self.mOtherRequestRe = re.compile("^(.|\r\n)*?([a-zA-Z]+? (.)* HTTP\\/1\\.(1|0)\r\n(.|\r\n)+?\r\n\r\n)")
        self.mResponseRe = re.compile("(^(HTTP\\/1.1)\\s([0-9]{3})\\s.*\r\n(.+?:.+?\r\n)*\r\n)")
        self.mShouldStop = False
        self.mCache = fileCache
        self.mRedirects = hostReplacer
        self.mDebug = False

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
        except:
            x = 10


    def parseReceive(self):
        self.printDebug("In parseReceive")
        while True:
            #Check if the regex matches
            matches = self.mOtherRequestRe.match(self.mBuffer)
            if not matches:
                break

            #This one is the part of the string we need
            match = matches.groups()[1]
            if not match:
                break
            else:
                self.printDebug("Found a match")
                #Make a request based on string
                request = HttpRequest(match)
                #Edit headers
                request.setHeader("User-Agent", "1.1 Brent Proxy")
                request.setHeader("Via", "1.1 Brent Proxy")
                request.setHeader("X-Forwarded-For", self.mAddress[0])
                #If request is valid, add it to list
                if not request.mInvalid:
                    #Try to replace host and request url with hosts file
                    host = self.mRedirects.substringReplace(request.getHeader("Host"))
                    url = self.mRedirects.substringReplace(request.getUrl())
                    request.setHeader("Host", host)
                    request.setUrl(url)
                    self.mRequestQueue.put(request)
                    #Remove this match from buffer, support for more than one request per socket (disabled for safety)
                    self.mBuffer = self.mBuffer[len(match):]

    def sendFile(self):
        self.printDebug("In sendFile")
        #If we don't need to send files, return
        if self.mRequestQueue.empty():
            return

        #Get some values
        request = self.mRequestQueue.get()
        path = request.getUrl()
        host = request.getHeader("Host")

        try:
            #Get ip of host
            ip = socket.gethostbyname(host)

            #Check if file is cached
            if self.mCache.fileIsCached(str(ip) + str(path)):
                #If so, try to send from cached file (can fail because of deletion of file or busy file pointers)
                try:
                    file = self.mCache.getReadFilePointer(str(ip) + str(path))
                    self.sendFromCache(request, file)
                #if it fails, send from host
                except:
                    print "Exception when sending cached file."
                    self.sendFromHost(request, ip, host, path)
            #If not cached, send from host
            else:
                self.sendFromHost(request, ip, host, path)

        except socket.error as msg:
            print msg
            self.sendBadRequest()
            print "Exception in send."


        self.mSocket.close()
        self.mShouldStop = True

    def sendFromCache(self, request, file):
        print "CACHE: " + request.getUrl()
        #Init
        bufferData = file.read(5024)
        self.printDebug(bufferData)
        self.mSocket.send(bufferData)

        #Keep sending as long as we have data
        while bufferData:
            bufferData = file.read(5024)
            if not bufferData:
                break

            self.printDebug(bufferData)
            self.mSocket.send(bufferData)

        file.close()

    def sendFromHost(self, request, ip, host, path):
        print "HOST: " + request.getUrl()
        #Make connection with host
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((ip, 80))
        #Edit request header
        request.setHeader("Connection", "close")
        #We only need to cache get requests
        shouldCache = (request.getMethod().lower() == "get")
        #Send request to host
        query = request.getRequestQuery()
        sock.send(query)

        #If we need to cache, try to get a file write pointer
        file = ""
        if shouldCache:
            try:
                file = self.mCache.getWriteFilePointer(str(ip) + str(path))
            except:
                shouldCache = False

        header = ""
        headerFound = False
        while True:
            #Get data from host
            data = sock.recv(5024)
            if not data:
                break

            #Gepland om hier de header aan te passen, maar dit gaf problemen met chunked data, dus heb ik dit weggelaten
            if not headerFound:
                header = header + data
                matches = self.mResponseRe.match(header)
                if matches:
                    headerCopy = header
                    headerString = matches.groups()[0]
                    leftover = header[len(headerString):].strip()
                    header = HttpResponse(headerString)
                    headerFound = True

                    self.mSocket.send(headerCopy)
                    if shouldCache:
                        file.write(headerCopy)
                continue

            #Send to socket
            self.mSocket.send(data)
            #And write to file if we can/must
            if shouldCache:
                file.write(data)

        if shouldCache:
            file.close()
        try:
            if headerFound and header.getResponseCode() != 200 and shouldCache:
                self.mCache.removeFile(str(ip) + str(path))
        except:
            x = 10


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

    def execute(self):
        self.mThread.start()

    def join(self):
        self.mThread.join()

    def printDebug(self, string):
        if self.mDebug:
            print string


class HttpBase:
    def __init__(self):
        self.mHeaders = dict()
        self.mVersion = ""

    def hasHeader(self, key):
        return key in self.mHeaders

    def getHeader(self, key):
        return self.mHeaders[key.lower()]

    def setHeader(self, key, value):
        self.mHeaders[key.lower()] = value

    def setVersion(self, version):
        self.mVersion = version

    def getVersion(self):
        return self.mVersion

    def parseHeaderLine(self, string):
        #We should be able to split on ":"
        if re.match(".*:.*", string):
            headerSplit = re.split(":", string)
            left = headerSplit[0].strip()
            right = ""
            #There might be more than one ":", just concatenate
            for i in range(1, len(headerSplit)):
                if i == 1:
                    right = headerSplit[i]
                else:
                    right = right + ":" + headerSplit[i]
            right = right.strip()
            self.setHeader(left, right)

    def getHeadersQuery(self):
        keys = self.mHeaders.keys()
        values = self.mHeaders.values()
        toRet = ""

        for i in range(0, len(keys)):
            if i == len(keys) - 1:
                toRet = toRet + keys[i] + ": " + values[i]
            else:
                toRet = toRet + keys[i] + ": " + values[i] + "\r\n"

        return toRet



class HttpResponse(HttpBase):
    def __init__(self, text = False):
        HttpBase.__init__(self)
        self.mBase = HttpBase()
        self.mResponseCode = -1
        self.mResponseName = ""
        self.mInvalid = True

        if not text:
            return

        self.parse(text)

    def getResponse(self):
        return (self.mResponseCode, self.mResponseName)

    def setResponse(self, response):
        self.setResponseName(str(response[2]))
        self.setResponseCode(response[1])

    def getResponseName(self):
        return self.mResponseName

    def setResponseName(self, responseName):
        self.mResponseName = str(responseName)

    def getResponseCode(self):
        return self.mResponseCode

    def setResponseCode(self, code):
        self.mResponseCode = int(code)

    def parse(self, response):
        #Split on \r\n
        splits = re.split("\r\n", response)
        httpFound = False

        for split in splits:
            #If we have not found the first line
            if not httpFound:
                httpFound = self.parseFirstLine(split)
            #If we have found the first line
            else:
                self.parseHeaderLine(split)

        self.mInvalid = not httpFound

    def parseFirstLine(self, line):
        #Check if the line matches the first line of an HTTP request
        if re.match("HTTP\\/1\\.(0|1) [0-9]{1,3} .+", line):
            versNo = line[5:8].strip()
            statusCode = line[9:12].strip()
            statusName = line[13:].strip()

            self.setVersion(versNo.strip())
            self.mResponseCode = int(statusCode)
            self.mResponseName = statusName.strip()
            return True
        else:
            return False

    def getFirstLineQuery(self):
        toRet = ""
        toRet = toRet + "HTTP/" + self.getVersion() + " " + str(self.mResponseCode) + " " + str(self.mResponseName)
        return toRet

    def getResponseQuery(self):
        toRet = self.getFirstLineQuery() + "\r\n"
        toRet = toRet + self.getHeadersQuery() + "\r\n\r\n"
        return toRet


class HttpRequest(HttpBase):
    def __init__(self, text = False):
        HttpBase.__init__(self)
        self.mBase = HttpBase()
        self.mUrl = ""
        self.mMethod = ""
        self.mInvalid = True

        if not text:
            return
        self.parse(text)

    def getUrl(self):
        return self.mUrl

    def setUrl(self, url):
        self.mUrl = url

    def getMethod(self):
        return self.mMethod

    def setMethod(self, method):
        self.mMethod = method

    def parse(self, text):
        #Split on \r\n
        splits = re.split("\r\n", text)
        httpFound = False

        for split in splits:
            #If we have not found the first line
            if not httpFound:
                httpFound = self.parseFirstLine(split)
            #If we have found the first line
            else:
                self.parseHeaderLine(split)

        self.mInvalid = not httpFound

    def parseFirstLine(self, line):
        #Check if the line matches the first line of an HTTP request
        result = re.match("([a-zA-Z]+) .* HTTP\\/1\\.(1|0)", line)
        if result:
            self.mMethod = result.group(1)
            url = line[len(self.mMethod) + 1:].strip()
            versNo = url[len(url) - 9:]
            url = url[0: len(url) - len(versNo)].strip()
            versNo = versNo[6:].strip()

            self.setUrl(url)
            self.setVersion(versNo)
            return True
        else:
            return False

    def getFirstLineQuery(self):
        toRet = ""
        toRet = toRet + self.getMethod() + " " + self.getUrl() + " HTTP/" + self.getVersion()
        return toRet

    def getRequestQuery(self):
        toRet = self.getFirstLineQuery() + "\r\n"
        toRet = toRet + self.getHeadersQuery()
        toRet = toRet + "\r\n\r\n"
        return toRet

class HttpServer:
    def __init__(self, port, file = False):
        if not file:
            print "Starting server on port " + str(port)
        else:
            print "Starting server on port " + str(port) + " with redirect file: " + str(file)
        self.mInvalid = False
        self.mPort = port
        self.mCache = HTTPFileCache()
        self.mRedirects = HostReplacer(file)

    def open(self):
        self.mSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.mSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.mSocket.bind(("localhost", self.mPort))
        self.mSocket.listen(5)

    def close(self):
        self.mSocket.close()

    def runServer(self):
        self.open()
        counter = 0
        while True:
            clientSocket, clientAddress = self.mSocket.accept()
            #Make new handler
            clientHandler = ClientHandler(clientSocket, clientAddress, self.mCache, self.mRedirects)
            #Start it
            clientHandler.execute()
            counter = counter + 1
            #print "Sockets opened: " + str(counter)

if len(sys.argv) == 3:
    if sys.argv[1] == "-p":
        port = int(sys.argv[2])
        server = HttpServer(port)
        server.runServer()
    else:
        print "Invalid params, aborting."
elif len(sys.argv) == 5:
    if sys.argv[1] == "-p" and sys.argv[3] == "-r":
        server = HttpServer(int(sys.argv[2]), str(sys.argv[4]))
        server.runServer()
    elif sys.argv[1] == "-r" and sys.argv[3] == "-p":
        server = HttpServer(int(sys.argv[4]), str(sys.argv[2]))
        server.runServer()
    else:
        print "Invalid params, aborting."
else:
    print "Invalid params, aborting"
