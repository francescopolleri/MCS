import matplotlib.pyplot as plt
import math 
import numpy as np
from ROOT import *

rnd=TRandom3()
rnd.SetSeed(123456789)

def fun(x):
    return 3*x**2+4*x**3

def fInt(x):
    return x**3+x**4

Nev=1000000

b=5; a=3

l=np.linspace(a,b,100)

y=np.array([])
for i in range (0,100):
    y=np.append(y,fun(l[i]))
   
ymin=np.min(y)
ymax=np.max(y)

n_in=0
for i in range (0,Nev):
    x=(b-a)*rnd.Rndm()+a
    y=rnd.Rndm()*ymax
    if(y<=fun(x)):
        n_in=n_in+1

p=n_in/Nev

I=fInt(b)-fInt(a)

I_MC=p*ymax*(b-a)   #Devo considerare tutta l'area sottostante f(x) quindi y corre tra 0 e ymax
e_I_MC=np.sqrt(p*(1-p)/Nev)

print('I analitico =',I)
print('I_MC = ',I_MC,' +/- ',e_I_MC)
