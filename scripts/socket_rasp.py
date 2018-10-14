#!/usr/bin/python

import socket
ip = '192.168.0.103'
port = 3333 
addr = ((ip,port)) 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1) 
s.connect(addr) 
r = raw_input('Digite "q" para sair')
while r != 'q':
    r = raw_input('Digite o texto: ')
    try:
        s.send(r+"\n")
        print('mensagem enviada')
    except:
        print('Mensagem nao foi enviada')

    

