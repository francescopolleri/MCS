import numpy as np
import matplotlib.pyplot as plt
import math

k=0.25
w0=0.25
m=1
A=0.1

n=1000

def acc(x,t):
    if abs(x)!=0:
        return (-k*x/abs(x)+A*math.sin(w0*t))/m
    else:
        return A*math.sin(w0*t)/m

x=np.zeros(n)
x[0]=1
t=np.zeros(n)
v=np.zeros(n)
h=0.1

for i in range (0,n-1):
    v[i+1]=v[i] + h/2*(acc(x[i],t[i])+acc(x[i],t[i+1]))
    x[i+1]=x[i] + h*v[i] + 1/2.*h**2*acc(x[i],t[i])
    t[i+1]=t[i] + h

plt.plot(t,x)
plt.show()
