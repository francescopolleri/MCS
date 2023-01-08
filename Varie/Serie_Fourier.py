import matplotlib.pyplot as plt
import numpy as np

N_points=1000
N=100
x=np.linspace(-10,10,N_points)

def fun(x):
    return 1/(5-4*np.cos(x))

plt.plot(x,fun(x),color='r')

def c_n(n):
    return 1/((2**2-1)*2**n)
c_0=c_n(0)

a_0=c_0
def a_n(n):
    return c_n(n)+c_n(-n)

def b_n(n):
    return (c_n(n)-c_n(-n))*(1j)

def ff_real(x,L):
    s=a_0/2
    for n in range (1,N):
        s += a_n(n)*np.cos(2*np.pi*n*x/L) + b_n(n)*np.sin(2*np.pi*n*x/L)
    return s

def ff_imag(x,L):
    s=c_0
    for n in range (1,N):
        s += 2*c_n(n)*np.cos(n*2*np.pi*x/L)  
    return s


yi=np.array([])
for i in range (0,N_points):
    yi=np.append(yi,ff_imag(x[i],2*np.pi))  #Ricordarsi di impostare L

plt.plot(x,yi,':',color='k')
plt.show()



