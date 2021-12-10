import socket

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', 10000)
print('starting up on {} port {}'.format(*server_address))
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

ipv4_data = "FC E9 98 97 EC EA 44 D9 E7 00 40 01 08 00 45 00 00 38 00 00 00 00 F1 01 8C 2B 3E 9A 59 2E AC 13 F9 BD 0B 00 BF 50 00 00 00 00 45 00 00 3C 15 B2 00 00 01 11 EA 81 AC 13 F9 BD 81 BB 91 F1 D4 0F 82 BE 00 28 DE B8"
ipv4_data_bytearray = bytearray.fromhex(ipv4_data)

while True:
    # Wait for a connection
    print('waiting for a connection')
    connection, client_address = sock.accept()
    try:
        print('connection from', client_address)

        # transmit data to client
        #while True:
        connection.send(ipv4_data_bytearray)
    finally:
        print("Connection close")
        # Clean up the connection
        connection.close()