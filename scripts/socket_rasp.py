#!/usr/bin/python

import socket
ip = '127.0.0.1'
port = 3333 
addr = ((ip,port)) 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.connect(addr) 
s.send('Ola mundo') 
print('mensagem enviada')
raw_input()
s.close()