import numpy as np
import math as m
import matplotlib.pyplot as plt

rho=np.linspace(0,1,100)

x1=1
x2=2
sig1=0.1
sig2=0.1

r=1

sig=sig1**2+sig2**2-2*r*sig1*sig2  #x2-x1 è combinazione lineare di x1 e x2

d=x2-x1

print('x2-x1 = ',d,'+/-',sig)

def sigma(a,b,r):
    return a**2+b**2-2*r*a*b

err=np.array([])
for i in range(0,100):
    err=np.append(err,sigma(sig1,sig2,rho[i]))
    
delta=np.array([])
for i in range(0,100):
    delta=np.append(delta,d)

plt.errorbar(rho,delta,err,0,ecolor='k')
plt.show()