import socket

def handleIPv4Data(data_list):
    print("ipv4")

def handleIPv6Data(data_list):
    print("ipv6")

def main():
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the port
    server_address = ('localhost', 10000)
    print('starting up on {} port {}'.format(*server_address))
    sock.bind(server_address)

    # Listen for incoming connections
    sock.listen(1)

    while True:
        # Wait for a connection
        print('waiting for a connection')
        connection, client_address = sock.accept()
        try:
            print('connection from', client_address)

            # receive data from client
            while True:
                data = connection.recv(1024)
                if not data:
                    break
                data = data.hex(':')
                print('received {!r}'.format(data))

                data_list = data.split(':')
                ethertype =  data_list[12] + data_list[13]

                print(ethertype)

                if ethertype == "0800":
                    connection.send(str.encode("IS IPv4 with Ethertype: " + ethertype))
                    handleIPv4Data(data_list)
                elif ethertype == "86dd":
                    connection.send(str.encode("IS IPv6 with Ethertype: " + ethertype))
                    handleIPv6Data(data_list)
                else:
                    connection.send(str.encode("UNKNOWN Ethertype"))

                OUI_dest = data_list[0:3]
                OUI_src = data_list[6:9]

                connection.send(str.encode("OUI Destination: " + str(OUI_dest)))
                connection.send(str.encode("OUI Source: " + str(OUI_src)))
        finally:
            print("Connection close")
            # Clean up the connection
            connection.close()


if __name__ == '__main__':
    main()