# FC E9 98 97 EC EA 44 D9 E7 00 40 01 08 00 45 00 00 38 00 00 00 00 F1 01 8C 2B 3E 9A 59 2E AC 13
# F9 BD 0B 00 BF 50 00 00 00 00 45 00 00 3C 15 B2 00 00 01 11 EA 81 AC 13 F9 BD 81 BB 91 F1 D4 0F
# 82 BE 00 28 DE B8

# 33 33 FF D7 6D A0 00 25 90 54 73 9A 86 DD 60 00 00 00 00 20 3A FF FE 80 00 00 00 00 00 00 02 25
# 90 FF FE 54 73 9A FF 02 00 00 00 00 00 00 00 00 00 01 FF D7 6D A0 87 00 19 C9 00 00 00 00 20 01
# 4C A0 20 01 00 11 02 25 90 FF FE D7 6D A0 01 01 00 25 90 54 73 9A

import socket

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('localhost', 10000)

print('connecting to {} port {}'.format(*server_address))
sock.connect(server_address)

ipv4_data = "FC E9 98 97 EC EA 44 D9 E7 00 40 01 08 00 45 00 00 38 00 00 00 00 F1 01 8C 2B 3E 9A 59 2E AC 13 F9 BD 0B 00 BF 50 00 00 00 00 45 00 00 3C 15 B2 00 00 01 11 EA 81 AC 13 F9 BD 81 BB 91 F1 D4 0F 82 BE 00 28 DE B8"
ipv6_data = "33 33 FF D7 6D A0 00 25 90 54 73 9A 86 DD 60 00 00 00 00 20 3A FF FE 80 00 00 00 00 00 00 02 25 90 FF FE 54 73 9A FF 02 00 00 00 00 00 00 00 00 00 01 FF D7 6D A0 87 00 19 C9 00 00 00 00 20 01 4C A0 20 01 00 11 02 25 90 FF FE D7 6D A0 01 01 00 25 90 54 73 9A"

try:
    # transmit data to server
    #ipv4_data_bytearray = bytearray.fromhex(ipv4_data)
    #sock.send(ipv4_data_bytearray)
    #print("sent ipv4")

    ipv6_data_bytearray = bytearray.fromhex(ipv6_data)
    sock.send(ipv6_data_bytearray)
    print("sent ipv6")

    while True:
        data = sock.recv(255)
        if not data:
            break
        print('received {!r}'.format(data))
        print('\n')

finally:
    print('closing socket')
    sock.close()
