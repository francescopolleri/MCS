#RUNGE-KUTTA 2
'''
import math as m
import numpy as np
import matplotlib.pyplot as plt

rho=500; rho0=8000; mu=0.001; r=0.01; g=9.81
def Cd(v):
    vmod=abs(v)
    Re=2*rho*r/mu
    return 24*vmod/Re + 4**(3/2.)/m.sqrt(Re)+0.4*vmod**2

def acc(x,v):
    M=4/3.*m.pi*r**3*rho0
    if abs(v)!=0:
        F=-1/2.*Cd(v)*rho*r**2*v/abs(v) -M*g
    else:
        F= -M*g
    return F/M

def acc_a(x,v):
    M=4/3.*m.pi*r**3*rho0
    m0 =4/3.*m.pi*r**3*rho
    F=acc(x,v)*M + m0*g
    return F/M

n=1000
y=np.zeros(n)    #Calcolo senza Archimede
t=np.zeros(n)
v=np.zeros(n)

t[0]=0
y[0]=100
v[0]=0
dt=0.05
for i in range (0,n-1):
    k1=dt*v[i]
    w1=dt*acc(y[i],v[i])

    k2=dt*(v[i]+w1/2)
    w2=dt*acc(y[i]+k1/2,v[i]+w1/2)

    y[i+1]=y[i]+k2
    v[i+1]=v[i]+w2
    t[i+1]=t[i]+dt

plt.plot(t,v)

y=np.zeros(n)    #Calcolo con Archimede
t=np.zeros(n)
v=np.zeros(n)

t[0]=0
y[0]=100
v[0]=0
dt=0.05
for i in range (0,n-1):
    k1=dt*v[i]
    w1=dt*acc_a(y[i],v[i])

    k2=dt*(v[i]+w1/2)
    w2=dt*acc_a(y[i]+k1/2,v[i]+w1/2)

    y[i+1]=y[i]+k2
    v[i+1]=v[i]+w2
    t[i+1]=t[i]+dt

plt.plot(t,v)
plt.show()

'''
'''
#VERLET-VELOCITY

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

'''


#NUMEROV

import matplotlib.pyplot as plt
import numpy as np
import math

N=100000

def kappa(x):
    return x**2

def b(x):
    return (h**2/12)*kappa(x)

def numerov(x):
    for i in range (1,N):
        x[i] = (2*x[i-1]*(1-5*b(x[i-1]))-x[i-2]*(1+b(x[i-2])))/(1+b(x[i]))
    return x

h=0.1

x=np.ones(N)*0.01
t=np.linspace(0,100,N)

x=numerov(x)

plt.plot(t,x)
plt.show()





    