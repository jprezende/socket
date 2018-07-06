#!/usr/bin/env python
#coding: utf-8

import socket
import time
import sys
import select

escolha1=raw_input('Digite 0 para server ou 1 client:\n')
if escolha1=="0":
    print('server selecionado!\n')
elif escolha1=="1":
    print('client selecionado!\n')
else:
    print('Valor invalido!')
escolha2=raw_input('Digite 0 para TCP ou 1 para UDP:\n')
if escolha2=="0":
    print('TCP selecionado!')
elif escolha2=="1":
    print('UDP selecionado!')
else:
    print('Valor invalido')

if (escolha1=="0" and escolha2=="0"):
    print('Server TCP')
    TCP_IP = raw_input('Digite o ip do server:\n')
    TCP_PORT = 8880
    BUFFER_SIZE = 80  # Normally 1024, but we want fast response

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((TCP_IP, TCP_PORT))
    print ('Socket server TCP criado')
    s.listen(1)

    conn, addr = s.accept()
    print 'Endereco utilizado na conexao:', addr
    #print 'Digite a quantidade de mensagens'
    #a = input()
    #for a in range(a, 0, 1):
    while 1:
        data = conn.recv(BUFFER_SIZE)
        if not data: break
        print "Dado recebido:", data
        #if (data=='ping'):
        conn.send('pong')

            # echo
    conn.close()
elif(escolha1=="0" and escolha2=="1"):
    print('Server UDP')
    UDP_IP = raw_input('Digite o ip do server:\n')
    UDP_PORT = 8880
    BUFFER_SIZE = 80

    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP
    sock.bind((UDP_IP, UDP_PORT))

    while(1):
        print "Listening"
        recv_data, addr = sock.recvfrom(80)
        print recv_data
        if recv_data == 'ping' :
            sock.sendto("pong", addr)

elif(escolha1=="1" and escolha2=="0"):
    print('Client TCP')
    TCP_IP = raw_input('Digite o ip do server:\n')
    MENSAGENS = input('Quantas mensagens deseja enviar?\n')
    TCP_PORT = 8880
    BUFFER_SIZE = 80
    MESSAGE = "ping"

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((TCP_IP, TCP_PORT))
    cont=0
    ttotal=0
    tmin=0
    tmax=0

    while (cont<MENSAGENS):
        s.send(MESSAGE)
        t = time.time()
        data = s.recv(BUFFER_SIZE)
        tf = (time.time() - t)*1000000
        if (tmin==0 or tf<tmin):
            tmin=tf
        if (tmax==0 or tf>tmax):
            tmax=tf
        print(int(tf))
        ttotal=(ttotal+tf)
        print("ttotal:", int(ttotal))
        cont=cont+1;
    s.close()
    tmedio=ttotal/MENSAGENS
    print "Resposta:", data
    print "Tempo mínimo (us):", int(tmin)
    print "Tempo médio (us):", int(tmedio)
    print "Tempo máximo (us)", int(tmax)
elif(escolha1=="1" and escolha2=="1"):
    print('Client UDP')
    UDP_IP = raw_input('Digite o ip do server:\n')
    MENSAGENS = input('Quantas mensagens deseja enviar?\n')
    UDP_PORT = 8880
    BUFFER_SIZE = 80
    MESSAGE = "ping"
    print "UDP target IP:", UDP_IP
    print "UDP target port:", UDP_PORT
    cont= 0
    sock = socket.socket(socket.AF_INET, # Internet
    socket.SOCK_DGRAM) # UDP
    tmin=0
    tmax=0
    ttotal=0

    while(cont < MENSAGENS):
        cont = cont + 1
        sock.sendto(MESSAGE,(UDP_IP, UDP_PORT))
        t = time.time()
        recv_data, addr = sock.recvfrom(80)
        tf = (time.time() - t)*1000000
        print "Tempo decorrido (us):", int(tf)
        print recv_data, "!!"
        if (tmin==0 or tf<tmin):
            tmin=tf
        if (tmax==0 or tf>tmax):
            tmax=tf
        print(int(tf))
        ttotal=(ttotal+tf)
    print("ttotal:", int(ttotal))
    tmedio=ttotal/MENSAGENS
    print "Tempo mínimo (us):", int(tmin)
    print "Tempo médio (us):", int(tmedio)
    print "Tempo máximo (us)", int(tmax)

else:
    print('Valor invalido')
