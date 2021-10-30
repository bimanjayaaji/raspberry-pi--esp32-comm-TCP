import socket
from time import time,time_ns

#s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('0.0.0.0', 8090 ))

s.listen(0)

def main():
	while True:
		client, addr = s.accept()    
		
		while True:
			start = time_ns()
			content = client.recv(32)

			if len(content) ==0:
				break
			else:
				print(content.decode(),type(content))
				client.send("Hello from PC".encode())
				print(time_ns()-start)

		print("Closing connection")
		client.close()

if __name__ == '__main__':
	main()
