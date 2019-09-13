__author__ = 'Brent Berghmans'
import socket
from threading import Thread

def printDebug(string):
    if True:
        print(string)

class FTPClient:
    def __init__(self, port):
        self._init(port)

    def _init(self, port):
        self._mPort = port
        self._mCommandSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._mCommandSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        self._mDataSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._mDataSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._mDataSocket.bind(("localhost", self._mPort))
        self._mDataSocket.listen(1)

    def connect(self, hostname, username, password):
        printDebug("Connecting to host command socket.")
        ip = socket.gethostbyname(hostname)
        self._mCommandSocket.connect((str(ip), 21))
        printDebug("Connected!\nTelling FTP my PORT.")
        print self._mCommandSocket.recv(128)

        if username:
            print self.sendCommand("USER", username)
        if password:
            print self.sendCommand("PASS", password)
        print self.sendCommand("PORT", "127,0,0,1," + str(self._mPort / 256) + "," + str(self._mPort % 256))

    def sendCommand(self, command, param):
        self._mCommandSocket.send(command + " " + str(param) + "\r\n")
        return self._mCommandSocket.recv(128)

    def acceptData(self):
        hostSocket, clientAddress = self._mDataSocket.accept()
        self._mHostDataSocket = hostSocket
        printDebug("Got connection")

    def close(self):
        try:
            self._mCommandSocket.close()
            self._mHostDataSocket.close()
            self._mDataSocket.close()
        except socket.error:
            x = 10

client = FTPClient(8300)
client.connect("127.0.0.1", False, False)
print client.sendCommand("NLST", ".Desktop")
client.acceptData()

data = "x"

while True:
    data = client._mHostDataSocket.recv(1024)
    if not data:
        break
    print data

client.close()