#!/usr/bin/env python

#import cv2
import rospy
import subprocess as system
from std_msgs.msg import Int16
from std_msgs.msg import String 
import sys
import math
import logging as log
import datetime as dt
import numpy as np
from time import sleep
import socket

class FaceDetection:
    def __init__(self, cascPath):
        self.cascPath = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"
        self.faceCascade = cv2.CascadeClassifier(cascPath)
        log.basicConfig(filename='webcam.log',level=log.INFO)
        self.video_capture = cv2.VideoCapture(0)
        self.anterior = 0
        self.abertHor = 62.2
        self.col = [0,0,0,0,0]

        self.height=0
        self.width=0
        self.divCol=5
        self.propPixel = 1

    def identificarColuna(self, x):
        escop = self.width/self.divCol
        if(x <= escop):
            self.col[0]+=1
        elif(x <= escop*2):
            self.col[1]+=1
        elif(x <= escop*3):
            self.col[2]+=1
        elif(x <= escop*4):
            self.col[3]+=1
        elif(x <= escop*5):
            self.col[4]+=1

    def exibi(self):
        print("COL1: "+str(self.col[0])+"\nCOL2: "+str(self.col[1])+"\nCOL3: "+str(self.col[2])+"\nCOL4: "+str(self.col[3])+"\nCOL5: "+str(self.col[4]))

    def obterAngulo(self, c):
        if c == 1:
            return (self.abertHor/2)*-1
        elif c == 2:
            return (self.abertHor/4)*-1
        elif c == 3:
            return 0
        elif c == 4:
            return self.abertHor/4
        elif c == 5:
            return self.abertHor/2
    

    def colunaMaisFaces(self):
        indexValorMax = - 1
        valorMax = -1
        for i in range(len(self.col)):
            if self.col[i] >= valorMax:
                valorMax = self.col[i]
                indexValorMax = i
                if valorMax == 0 and indexValorMax == self.divCol-1:
                    return int(self.divCol/2)
        return indexValorMax+1

    def capturar(self):
        if not self.video_capture.isOpened():
            print('Ative a camera')
            sleep(5)
            pass

        # Capture frame-by-frame
        ret, frame = self.video_capture.read()

        #frame = cv2.imread('img.jpg')

        self.height, self.width = frame.shape[:2]
        print("Lagura: " + str(self.width) + " Altura: "+ str(self.height))
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        faces = self.faceCascade.detectMultiScale(
            gray,
            scaleFactor=1.1,
            minNeighbors=5,
            minSize=(30, 30)
        )
        # Desenha um retangulo em volta do rosto
        for (x, y, w, h) in faces:
            self.identificarColuna(x)
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        if self.anterior != len(faces):
            self.anterior = len(faces)
            log.info("faces: "+str(len(faces))+" at "+str(dt.datetime.now()))
        
        self.exibi()
        c = self.colunaMaisFaces()
        print "Coluna mais face: " + str(c)
        print(self.obterAngulo(c))
        #server.enviarMensagem(obterAngulo(c))
        cv2.imwrite("img_detect.jpg", frame)

        # Libera a camera
        self.video_capture.release()
        cv2.destroyAllWindows()

        


class Cliente:
    def __init__(self, ip, porta):
        self.porta = porta
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
        self.socket.connect((ip, porta))

    def enviarMensagem(self, msg):
        self.socket.send(msg+'\n')
class ROS_Publisher:
    def __init__(self):
        self.pub = rospy.Publisher('/semic/p3at/rotate', Int16, queue_size=1)
        rospy.init_node('raspberry_p3at_publish', anonymous=True)
        self.rate = rospy.Rate(10) # 10hz
    def publisher(self, valor):
        rospy.loginfo('Publicando')
        angulo = Int16(valor)
        self.pub.publish(angulo)
class ROS_Listener:
    def __init__(self, callback):
        rospy.init_node('raspberry_p3at_publish', anonymous=True)
        rospy.Subscriber('/semic/p3at/status', String, callback)
        rospy.spin()

# Mostra resultado na tela
#cv2.imshow('Video', frame)

# Display the resulting frame
#cv2.imshow('Video', frame)

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)
    server.enviarMensagem(str(data.data))

def main(): 
    pub = ROS_Publisher()
    sub = ROS_Listener(callback)
    server = Cliente('127.0.0.1', 3333)
    print('Main')

if __name__ == '__main__':
    main()


