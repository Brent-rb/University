__author__ = 'gebruiker'

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.connect((str("127.0.0.1"), 8080))
sock.send("GET / HTTP/1.1\r\nHost: google.com\r\nConnection: close\r\n\r\n")
data = "a"
while data:
    data = sock.recv(1024)
    print data

sock.close()