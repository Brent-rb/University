import socket
from urlparse import urlparse
import re
import sys

class HttpResponse:
    def __init__(self, headerString):
        self.init()
        self.parse(headerString)

    def init(self):
        #Contain the header parameters
        self.mHeaders = dict()
        self.mResponseCode = -1
        self.mResponseMessage = ""
        self.mHttpVersion = 0

    def __contains__(self, item):
        return self.mHeaders.has_key(item)

    def getHeader(self, headerName):
        if self.mHeaders.has_key(headerName):
            return self.mHeaders[headerName]
        else:
            return False

    def getResponse(self):
        return (self.mResponseCode, self.mResponseMessage)

    def getHttpVersion(self):
        return self.mHttpVersion

    def parse(self, response):
        #Split on \r\n
        splits = re.split("\r\n", response)
        httpFound = False

        for split in splits:
            #If we have not found the first line
            if not httpFound:
                #Check if the line matches the first line of an HTTP request
                if re.match("HTTP\\/1\\.(0|1) [0-9]{1,3} .+", split):
                    httpFound = True
                    versNo = split[5:8].strip()
                    statusCode = split[9:12].strip()
                    statusName = split[13:].strip()

                    if versNo == "1.0":
                        self.mHttpVersion = 10
                    elif versNo == "1.1":
                        self.mHttpVersion = 11
                    elif versNo == "2.0":
                        self.mHttpVersion = 20

                    self.mResponseCode = int(statusCode)
                    self.mResponseMessage = statusName
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
                    self.mHeaders[left] = right

class HttpRequest:
    def __init__(self, method, url, http1_1 = False):
        self.init(method, url, http1_1)

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


class HttpClient:
    def __init__(self, address, followRedirects):
        if not self.setAddress(address):
            return

        self.mInvalid = False
        self.mSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.mSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.mPort = 80
        self.mRedirectDepth = 0
        self.mHeaderCompleteRe = re.compile('HTTP\\/1\\.(0|1)(.*\\r\\n)(.*:.*\\r\\n)+\\r\\n(\\r\\n|.)*')
        self.mHeaderFilterRe = re.compile('HTTP\\/1\\.(0|1)(.*\\r\\n)(.*:.*\\r\\n)+\\r\\n')
        self.mFollowRedirects = followRedirects

    def setAddress(self, address):
        if not re.match("http(s)?:\\/\\/.*", address):
            #Add http is there is nothing in front of the url
            if not re.match(".+:\\/\\/.*", address):
                address = "http://" + address
            #If something else with an // stands before the URL we need to stop (for instance ftp://johndoe.com)
            else:
                self.mInvalid = True
                self.printResponse("Invalid url, aborting.")
                return False

        self.mAddress = address
        self.mUrl = urlparse(address)
        return True

    def open(self):
        ip = socket.gethostbyname(self.mUrl[1])
        self.mSocket.connect((str(ip), self.mPort))

    def close(self):
        self.mSocket.close()
        self.mSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.mSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    def getResponse(self, http1_1 = True):
        if self.mInvalid:
            return

        try:
            #Open the socket
            self.open()
            #Create the get request
            request = self.createRequest(self.mUrl, http1_1)
            #Get the text form
            request = request.getHttpRequest()
            #Send the request to the socket
            self.mSocket.send(request)
        except:
            print "Exception occured when sending GET request, aborting."
            return

        header = ""
        body = ""
        response = False
        headerComplete = False
        while True:
            try:
                temp = self.mSocket.recv(1024)
            except:
                print "Exception occured when receiving data, output might be incorrect."
                temp = False

            if not temp:
                break

            if headerComplete:
                body = body + str(temp)
                if len(body) >= int(response.getHeader("Content-Length")):
                    break
            else:
                header = header + temp
                if self.mHeaderCompleteRe.match(header):
                    headerComplete = True
                    #For some reason, part of the regex gets returned, so we need index 4 as body
                    body = self.mHeaderFilterRe.split(header)[4]
                    #Header is the whole data - length of body
                    if body:
                        header = header[0:len(header) - len(body)]
                    else:
                        body = ""
                    response = HttpResponse(header)

                else:
                    self.printResponse('Header does not match.')


        print header
        print body

        self.close()
        self.evalResponse(response, http1_1)

    def evalResponse(self, response, http1_1):
        if response:
            if response.getHttpVersion() == 11 and response.getResponse()[0] == 400 and not http1_1:
                self.printResponse("GET Request failed, Error 400, Bad Request, server is using HTTP/1.1, trying HTTP/1.1 request now.")
                self.getResponse(True)
            else:
                responseInfo = response.getResponse()
                responseCode = responseInfo[0]

                if responseCode >= 100 and responseCode < 200:
                    self.parse1XXResponse(response, responseCode)
                elif responseCode >= 200 and responseCode < 300:
                    self.parse2XXResponse(response, responseCode)
                elif responseCode >= 300 and responseCode < 400:
                    self.parse3XXResponse(response, responseCode)
                elif responseCode >= 400 and responseCode < 500:
                    self.parse4XXResponse(response, responseCode)
                elif responseCode >= 500 and responseCode < 600:
                    self.parse5XXResponse(response, responseCode)
                else:
                    self.printResponse("GET Request failed, got back an invalid response.")
                    self.printResponse("No server information was found in the response.")



    def printGETRequestFailed(self, response):
        #I used to print the error code here because of different interpretation of assignment
        #print "GET Request failed Error " + str(response.getResponse()[0]) + ": " + response.getResponse()[1]
        self.printServerResponse(response)

    def printServerResponse(self, response):
        if "Server" in response:
            self.printResponse("Server is using: " + response.getHeader("Server"))
        else:
            self.printResponse("No server information was found in the response.")

    def printResponse(self, message):
        spaces = ""
        for i in range(0, self.mRedirectDepth):
            spaces = spaces + "  "

        print spaces + message

    def parse1XXResponse(self, response, responseCode):
        self.printGETRequestFailed(response)

    def parse2XXResponse(self, response, responseCode):
        if responseCode == 200:
            #Different interpretation of assignment
            #self.printResponse("GET Request was successful, server returned content.")
            self.printServerResponse(response)
        else:
            self.printGETRequestFailed(response)


    def parse3XXResponse(self, response, responseCode):
        if "Location" in response and self.mFollowRedirects:
            location = response.getHeader("Location")
            path = self.mUrl[2]

            if path:
                if location.endswith("/") and path.startswith("/"):
                    location = location + path[1:]
                else:
                    location = location + path

            self.setAddress(location)
            if self.mUrl[0] == "http":
                if self.mRedirectDepth < 5:
                    self.printResponse("Server gave an 3XX response, following redirect to: " + location)
                    self.printServerResponse(response)
                    self.mRedirectDepth = self.mRedirectDepth + 1
                    self.getResponse()
                else:
                    self.printResponse("We have been redirected 5 times, we're probably in a loop, stopped following redirects.")
                    self.printGETRequestFailed(response)
            else:
                self.printResponse("Redirect scheme is invalid (" + self.mUrl[0] + "), aborting.")
                self.printGETRequestFailed(response)
        else:
            self.printGETRequestFailed(response)

    def parse4XXResponse(self, response, responseCode):
        self.printGETRequestFailed(response)

    def parse5XXResponse(self, response, responseCode):
        self.printGETRequestFailed(response)

    def createRequest(self, address, http1_1 = False):
        request = HttpRequest("GET", address, http1_1)
        self.setParameters(request)
        return request

    def setParameters(self, request):
        request.setHeader("Accept", "text/html")
        request.setHeader("Connection", "close")


if len(sys.argv) == 2:
    #Second param indicates if we should follow redirects
    client = HttpClient(sys.argv[1], False)
    client.getResponse()
else:
    exit()

