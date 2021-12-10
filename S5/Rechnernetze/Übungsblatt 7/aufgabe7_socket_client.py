# https://en.wikipedia.org/wiki/EtherType
# https://de.wikipedia.org/wiki/Datenframe
# https://www.elektronik-kompendium.de/sites/net/2011241.htm

import socket

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('localhost', 10000)

print('connecting to {} port {}'.format(*server_address))
sock.connect(server_address)

try:
    while True:
        data = sock.recv(255)
        print('received {!r}'.format(data))

finally:
    print('closing socket')
    sock.close()