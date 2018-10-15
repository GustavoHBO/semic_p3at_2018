import socket
import rospy
import subprocess as system
from std_msgs.msg import Int16
from std_msgs.msg import String 

class Cliente:
    def __init__(self, ip, porta):
        self.porta = porta
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
        self.socket.connect((ip, porta))
    def enviarMensagem(self, msg):
        self.socket.send(msg+'\n')
    def fechar(self):
        self.socket.close()

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
        rospy.init_node('raspberry_p3at_listener', anonymous=True)
        rospy.Subscriber('/semic/p3at/status', String, callback)
        rospy.spin()

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)

#cliente = Cliente('127.0.0.1', 3333)
publicar = ROS_Listener(callback)
r = 'a'
#while(r != 'q'):
#    r = raw_input('Mensagem: ')
#    cliente.enviarMensagem("Ola mundo")
#cliente.fechar()