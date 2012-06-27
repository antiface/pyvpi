import socket

port = 9999
host = ""

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind((host,port))
s.listen(1)
while True :    
    cli_sock,cli_addr = s.accept()
    while True :
        try :
            buf = cli_sock.recv(8196)
            if not buf :
                break
            print buf,
            cli_sock.send("ok")
        except :
            break
    cli_sock.close()

