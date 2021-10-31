'''
MQTT CONNECTION RASPBERRY PI

Subscribing to 'my_topic2' and 'my_topic3'
Publishing to 'my_topic'
'''

import paho.mqtt.client as mqtt
from time import time, sleep, time_ns

mqtt_address = '192.168.0.138'

def on_connect(client,userdata,flags,rc):
	print('Connected with result code '+str(rc))
	client.subscribe('my_topic2')

def on_message(client,userdata,msg):
	global start
	print('Message received from '+ msg.topic + ' : ' + str(msg.payload))
	print(time()-start)

def on_publish(client,userdata,mid):
	print('data published')
	
def main():
	global start, mqtt_client
	
	mqtt_client.loop_start()
	start = time()
	timeout = time() + 1
	while time() < timeout : pass
	mqtt_client.publish('my_topic','r')
	
if __name__ == '__main__':
	mqtt_client = mqtt.Client()
	mqtt_client.on_connect = on_connect
	mqtt_client.on_message = on_message
	mqtt_client.on_publish = on_publish
	mqtt_client.connect(mqtt_address, 1883)
	
	while True:
		main()


