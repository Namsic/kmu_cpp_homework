from multiprocessing import shared_memory
import time

class mySharedMemory:
    def __init__(self, m_name, m_size=200):
        try:
            self.shm = shared_memory.SharedMemory(name=m_name)
        except FileNotFoundError:
            self.shm = shared_memory.SharedMemory(create=True, name=m_name, size=m_size+3)
            self.shm.buf[0] = 3
            self.shm.buf[1] = 3
            self.shm.buf[2] = m_size+3
            for i in range(3, self.shm.size):
                self.shm.buf[i] = 255
    def receive(self):
        if self.shm.buf[self.shm.buf[0]] == 255:
            return -1
        res = self.shm.buf[self.shm.buf[0]]
        self.shm.buf[self.shm.buf[0]] = 255
        print('Receive:', res)
        self.shm.buf[0] += 1
        if self.shm.buf[0] >= self.shm.buf[2]:
            self.shm.buf[0] = 3
        return res
    
    def send(self, data):
        if self.shm.buf[self.shm.buf[1]] != 255:
            return False
        self.shm.buf[self.shm.buf[1]] = data
        print('Send:', data)
        self.shm.buf[1] += 1
        if self.shm.buf[1] >= self.shm.buf[2]:
            self.shm.buf[1] = 3
        return True
    
recv = mySharedMemory('receiver')
send = mySharedMemory('sender')

while True:
    tmp = recv.receive()
    if tmp != -1:
        send.send(tmp)
