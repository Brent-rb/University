__author__ = 'Brent Berghmans'

import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.connect(('localhost', 2000))

s.send("\n")
msg = s.recv(60)
print msg
s.send("IP\n")
msg = s.recv(60)
print msg
s.send("\n")
msg = s.recv(60)
print msg
s.send("TIME\n")
msg = s.recv(60)
print msg

s.close()
