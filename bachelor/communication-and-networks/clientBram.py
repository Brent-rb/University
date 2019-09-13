__author__ = 'gebruiker'


import socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.connect(('localhost', 2000))

sock.send("UNKNOWN")
try:
    print sock.recv(60).strip('\n')
except socket.timeout:
    print "Timeout"
    # Deze exception wordt gegooid omdat je geen message terugstuurt naar de client, maar da's geen problem
    pass

sock.recv(60)
