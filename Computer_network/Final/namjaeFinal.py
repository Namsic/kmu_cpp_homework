import socket, time
from threading import Thread
from multiprocessing import Process

class MyHost:
    layers = []
    procs = []
    oppo = None
    def __init__(self, hostid, host_name='undefined'):
        port_base = 10000 + hostid * 10

        self.layers = [
            Physical_layer(port_base+1, host_name),
            Datalink_layer(port_base+2, host_name), 
            Network_layer(port_base+3, host_name),
            Transport_layer(port_base+4, host_name),
            Application_layer(port_base+5, host_name)
        ]
        for i in range(1, len(self.layers)):
            self.layers[i-1].connectLayer(self.layers[i])
    
    def open_server(self):
        tmp_socket = socket.socket()
        tmp_socket.bind(('127.0.0.1', self.layers[0].port))
        tmp_socket.listen()
        self.layers[0].below, _ = tmp_socket.accept()
    def connect_server(self, oppo_hostID):
        self.layers[0].below = socket.socket()
        self.layers[0].below.connect(('127.0.0.1', 10001 + oppo_hostID * 10))
        
    
    def run(self):
        for each_layer in self.layers:
            proc = Process(target=each_layer.run)
            self.procs.append(proc)
            proc.start()
    
    def send2oppo(self, data):
        self.layers[-1].sendData(data)

class MyLayer:
    layer_name = 'undefined'
    port = None
    above = None
    below = None
    ERROR = 'ERR_SIGNAL'

    def __init__(self, port, host='undefined'):
        self.port = port
        self.host_name = host
    
    def run(self):
        self.thrd_recvFromAbove = Thread(target=self.receiveFromAbove)
        self.thrd_recvFromBelow = Thread(target=self.receiveFromBelow)
        self.thrd_recvFromAbove.start()
        self.thrd_recvFromBelow.start()
    
    def connectLayer(self, aboveLayer):
        tmp_socket = socket.socket()
        tmp_socket.bind(('127.0.0.1', self.port))
        tmp_socket.listen()
        thrd_accept = Thread(target=self.acceptSocket, args=(tmp_socket,))
        thrd_accept.start()
        aboveLayer.below = socket.socket()
        aboveLayer.below.connect(('127.0.0.1', self.port))
    def acceptSocket(self, tmp_socket):
        self.above, _ = tmp_socket.accept()

    def receive(self, from_, to_, proc_func):
        while from_:
            d_len = int(from_.recv(2).decode())
            input_data = from_.recv(d_len).decode()
            print('['+self.host_name+'] '+self.layer_name+' layer: receive "'+input_data+'"')
            output_data = proc_func(input_data)
            if output_data == self.ERROR:
                print("Err")
                continue
            if to_:
                print('['+self.host_name+'] '+self.layer_name+' layer: send "'+output_data+'"')
                output_data = str(len(output_data)).zfill(2) + output_data
                to_.sendall(output_data.encode())
    def receiveFromAbove(self):
        self.receive(self.above, self.below, self.process_send)
    def receiveFromBelow(self):
        self.receive(self.below, self.above, self.process_recv)
    
    def process_send(self, data):
        return data
    def process_recv(self, data):
        return data


class Physical_layer(MyLayer):
    layer_name = 'Physical'
    out = ['-', '0', '+']

    def process_send(self, data):
        signal = map(int, data)    
        res = ''    
        cur, direction = 0, 1
        for s in signal:
            cur += direction * s
            if s and cur:
                direction *= -1
            res += self.out[cur+1]
        return res

    def process_recv(self, data):
        before = '0'
        res = ''
        for bit in data:
            res += '0' if before == bit else '1'
            before = bit
        return res

class Datalink_layer(MyLayer):
    layer_name = 'Datalink'
    max_try = 15
    time_unit = 0.05

    def bit_stuffing(self, data):
        origin = map(int, data)
        cur = -1
        st = 0
        res = ''
        for i in origin:
            res += str(i)
            if cur == i:
                st += 1
                if st == 5:
                    res += '0' if i else '1'
                    st = 0
            else:
                cur = i
                st = 1
        return res

    def attempt(self):
        print("Start attempt")
        while False:
            print("Receiver is busy")
        print("Receiver is idle")
        print("Sending..")
        if False:
            print("Receive jamming signal")
            print("Collision detected.")
            return False
        return True

    def process_send(self, data):
        k = 0
        print("*** Attempt 1 ***")
        while not self.attempt():
            k += 1
            if k >= self.max_try:
                print("<< result: Abort >>")
                return self.ERROR
            r = random.randint(0, 2**k)
            print("wait (", self.time_unit, "*", r, ") seconds")
            time.sleep(self.time_unit * r)
            print("\n*** Attempt", k+1, "***")
        return self.bit_stuffing(data)
    
    def process_recv(self, data):
        origin = list(map(int, data))
        st = 1
        i = 1
        res = str(origin[0])
        while i < len(origin):
            res += str(origin[i])
            if origin[i] == origin[i-1]:
                st += 1
                if st == 5:
                    i += 1
            else:
                st = 1
            i += 1
        return res

class Network_layer(MyLayer):
    layer_name = 'Network'

class Transport_layer(MyLayer):
    layer_name = 'Transport'
    ack = [bin(ord(x))[2:].zfill(8) for x in ['A', 'C', 'K']]
    wait_ack = False
    wait_ack_idx = 0
    timeout = 1.5

    def receiveFromAbove(self):
        while self.above:
            input_data = self.above.recv(8).decode()
            print('['+self.host_name+'] '+self.layer_name+' layer: receive "'+input_data+'"')
            output_data = input_data
            self.wait_ack = True
            self.wait_ack_idx = 0
            if self.below:
                print('['+self.host_name+'] '+self.layer_name+' layer: send "'+output_data+'"')
                output_data = str(len(output_data)).zfill(2) + output_data
                self.below.sendall(output_data.encode())
                tmp_t = time.time()
                while self.wait_ack:
                    if time.time() - tmp_t > self.timeout:
                        print('Timeout. retry..')
                        self.below.sendall(output_data.encode())
                        tmp_t = time.time()
                print('Receive ACK')

    def receiveFromBelow(self):
        while self.below:
            d_len = int(self.below.recv(2).decode())
            input_data = self.below.recv(d_len).decode()
            if self.wait_ack:
                if input_data == self.ack[self.wait_ack_idx]:
                    self.wait_ack_idx += 1
                    if self.wait_ack_idx == 3:
                        self.wait_ack = False
                else:
                    self.wait_ack_idx = 0
                continue
            print('['+self.host_name+'] '+self.layer_name+' layer: receive "'+input_data+'"')
            output_data = input_data
            print('['+self.host_name+'] '+self.layer_name+' layer: send "'+output_data+'"')
            output_data = str(len(output_data)).zfill(2) + output_data
            self.above.sendall(output_data.encode())
            print('['+self.host_name+'] '+self.layer_name+' layer: send ACK')
            for b in self.ack:
                self.below.sendall(('08' + b).encode())

class Application_layer(MyLayer):
    layer_name = 'Application'

    def receiveFromBelow(self):
        while self.below:
            d_len = int(self.below.recv(2).decode())
            input_data = self.below.recv(d_len).decode()
            receive_data = chr(int(input_data, 2))
            print('['+self.host_name+'] '+self.layer_name+' layer: receive "'+input_data+'('+receive_data+')"')

    def sendData(self, data):
        for ch in data:
            print('['+self.host_name+'] '+self.layer_name+' layer: send "'+bin(ord(ch))+'('+ch+')"')
            tmp = bin(ord(ch))[2:].zfill(8)
            self.below.sendall(tmp.encode())
    
