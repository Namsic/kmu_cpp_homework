import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import time

def rosenbrock(x, y, a=2, b=100):
    v1 = a - x
    v2 = y - (x ** 2)
    return (v1 ** 2) + (b * (v2 ** 2))


def test_f1(x, y):
    return (x-1)**2 + (y-2)**2

def dfunc(func, x, y):
        h = 0.0001
        dv = np.zeros(2)

        tmp_plus = (func(x+h, y) - func(x, y)) / h
        tmp_minus = (func(x, y) - func(x-h, y)) / h
        dv[0] = (tmp_plus + tmp_minus) / 2
        
        tmp_plus = (func(x, y + h) - func(x, y)) / h
        tmp_minus = (func(x, y) - func(x, y - h)) / h
        dv[1] = (tmp_plus + tmp_minus) / 2
        
        return dv

print('* test dfunc *')
x = np.round(np.random.randn() * 3, 2)
y = np.round(np.random.randn() * 3, 2)
print('x:', x, '/ y:', y)
print(dfunc(rosenbrock, x, y))

def gradient_descent(func, v_init=[0, 0], momentum=False, draw=True):
        l_r = 0.0003  # Learning rage
        m_t = 10 ** 6  # Max try
        a_e = 0.001  # Allowable error
        log = np.zeros([m_t, 2])
        m_vec = np.zeros(2)  # Momentum vector

        s_t = time.time()
        v = v_init
        log[0] = v
        for i in range(1, m_t):
            d = dfunc(func, v[0], v[1])
            v -= l_r * d + m_vec
            log[i] = v
            if max(np.absolute(d)) < a_e:
                   break
            if momentum:
                m_vec = l_r * d * 0.5
        c_t = np.round(time.time()-s_t, 2)
        return v, i, c_t, log[:i]

plt.figure(figsize=(8, 4))
print('* test g_d *')
x = np.round(np.random.rand() * 3, 2)
y = np.round(np.random.rand() * 3, 2)
print('init x:', x, '/ init y:', y)
res_xy, try_cnt, calc_time, log = gradient_descent(rosenbrock, [x, y])
print('result:', res_xy)
print('try:', try_cnt)
print('calc_time:', calc_time)
plt.subplot(1, 2, 1)
plt.title('normal g_d')
plt.plot(log[:, 0], log[:, 1])

print('\n* test g_d(momentum) *')
print('init x:', x, '/ init y:', y)
res_xy, try_cnt, calc_time, log = gradient_descent(rosenbrock, [x, y], momentum=True)
print('result:', res_xy)
print('try:', try_cnt)
print('calc_time:', calc_time)
plt.subplot(1, 2, 2)
plt.title('momentum g_d')
plt.plot(log[:, 0], log[:, 1])

plt.show()

class Two_Value_GD:
    def __init__(self, func):
        self.func = func
        self.draw_func()


    def dfunc(self, x, y):
        h = 0.0001
        dv = np.zeros(2)

        tmp_plus = (self.func(x + h, y) - self.func(x, y)) / h
        tmp_minus = (self.func(x, y) - self.func(x - h, y)) / h
        dv[0] = (tmp_plus + tmp_minus) / 2
        
        tmp_plus = (self.func(x, y + h) - self.func(x, y)) / h
        tmp_minus = (self.func(x, y) - self.func(x, y - h)) / h
        dv[1] = (tmp_plus + tmp_minus) / 2
        
        return dv


    def draw_func(self):
        xn = 30
        x0 = np.linspace(-5, 5, xn)  # x
        x1 = np.linspace(-5, 5, xn)  # y
        xx0, xx1 = np.meshgrid(x0, x1)
        y = np.zeros([len(x0), len(x1)])  # func(x, y)
        for i0 in range(len(x0)):
            for i1 in range(len(x1)):
                y[i0, i1] = self.func(x0[i0], x1[i1])
        plt.figure(figsize=(8, 8))
        self.ax = plt.subplot(2, 1, 1, projection='3d')
        self.ax.plot_surface(xx0, xx1, y, alpha=0.5, color='cornflowerblue')
        

    def gradient_descent(self, v_init=[0, 0], momentum=False, draw=True):
        l_r = 0.0003
        m_t = 10 ** 6
        a_e = 0.001
        log = np.zeros([m_t, 2])
        m_vec = np.zeros(2)

        s_t = time.time()
        v = v_init
        log[0] = v
        for i in range(1, m_t):
            d = self.dfunc(v[0], v[1])
            v -= l_r * d + m_vec
            log[i] = v
            if max(np.absolute(d)) < a_e:
                   break
            if momentum:
                m_vec = l_r * d * 0.5
        c_t = np.round(time.time()-s_t, 2)
        if draw:
            if momentum:
                p = 4
            else:
                p = 3
            plt.subplot(2, 2, p)
            plt.plot(log[:i, 0], log[:i, 1])
        return v, i, c_t

        



if __name__ == '__main__':
    t_gd = Two_Value_GD(rosenbrock)
    print('\n* 경사하강법 *')
    x = np.round(np.random.randn() * 3, 2)
    y = np.round(np.random.randn() * 3, 2)
    print('init x:', x, '/ init y:', y)
    v, i, t = t_gd.gradient_descent(v_init=[x, y], momentum=False, draw=True)
    print('x, y:', np.round(v, 2))
    print('move:', i)
    print('time:', np.round(t, 2))

    print('\n* 경사하강법(모멘텀) *')
    print('init x:', x, '/ init y:', y)
    v, i, t = t_gd.gradient_descent(v_init=[x, y], momentum=True, draw=True)
    print('x, y:', np.round(v, 2))
    print('move:', i)
    print('time:', np.round(t, 2))
    plt.show()
    
    
