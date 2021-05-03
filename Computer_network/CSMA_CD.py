import random, time

class Sender:
    def __init__(self, recv):
        self.recv = recv
    
    def simulate(self, tfr, mt):
        k = 0
        print("*** Attempt 1 ***")
        while not self.attempt():
            k += 1
            if k >= mt:
                print("<< result: Abort >>")
                return False
            r = random.randint(0, 2**k)
            print("wait (", tfr, "*", r, ") seconds")
            time.sleep(tfr * r)
            print("\n*** Attempt", k+1, "***")
        print("<< result: Success >>")
        return True
            

    def attempt(self):
        print("Start attempt")
        while self.recv.isBusy():
            print("Receiver is busy")
        print("Receiver is idle")
        print("Sending..")
        time.sleep(1)
        if self.recv.collisionDetection():
            print("Receive jamming signal")
            print("Collision detected.")
            return False
        else:
            print("Complete")
            return True


class Receiver:
    def isBusy():
        time.sleep(0.3)
        return random.random() < 0.5

    def collisionDetection():  # jamming signal
        return random.random() < 0.8


if __name__ == "__main__":
    r = Receiver
    s = Sender(r)

    s.simulate(0.1, 10)
