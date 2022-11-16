import math as m
import numpy as np
import matplotlib.pyplot as plt
from ROOT import *

a=1

xmin=0
xmax=3

def f1(x):
    return np.exp(-x)*(1+a*np.cos(x))

def f2(x):
    return np.exp(-x)*(1+a) 

def fInt(x):
    return -(1/2.)*exp(-x)*(-a*sin(x)+a*cos(x)+2)

x=np.linspace(xmin,xmax,100)

fig, ax=plt.subplots()
ax.plot(x,f1(x),color='r',label='$e^{-x}(1+cos(x))$')
ax.plot(x,f2(x),color='b',label='$2e^{-x}$')
ax.legend()
plt.show()

rnd=TRandom3()
rnd.SetSeed(123456789)
N=10000

'''
CAMPIONAMENTO SEMPLICE
'''
tcs=TStopwatch()

fm=0.
fm2=0.
for i in range(0,N):
    x=rnd.Rndm()*(xmax-xmin)+xmin
    y=f1(x)
    fm=fm+y
    fm2=fm2+y*y

fm=fm/N
fm2=fm2/N

I=fm*(xmax-xmin)
eI=(xmax-xmin)*np.sqrt((fm2-fm*fm)/(N-1))

print('CAMPIONAMENTO SEMPLICE')
print('I con camp.semplice =',I,"+/-",eI)
print('I nominale =',fInt(xmax)-fInt(xmin))
print('CPU time used =',tcs.CpuTime())

'''
CAMPIONAMENTO D'IMPORTANZA
'''
tci=TStopwatch()

#applico inversione a g(x)=exp(-x)/(exp(-xmin)-exp(-xmax))

sm=0.
sm2=0.
for i in range(0,N):
    x=-np.log(1.0-(rnd.Rndm()*(np.exp(-xmin)-np.exp(-xmax))))
    y=f1(x)/(np.exp(-x)/(np.exp(-xmin)-np.exp(-xmax)))
    sm=sm+y
    sm2=sm2+y*y

sm=sm/N
sm2=sm2/N

I=sm
eI=np.sqrt((sm2-sm*sm)/(N-1))

print('CAMPIONAMENTO IMPORTANZA')
print('I con comp.imp =',I,'+/-',eI)
print('I nominale =',fInt(xmax)-fInt(xmin))
print('CPU time used =',tci.CpuTime())


