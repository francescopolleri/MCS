import numpy as np
import matplotlib.pyplot as plt
from ROOT import *

rnd=TRandom3()
rnd.SetSeed(123456789)

a=0
x=2
N=1000

def f(x):
    return 1/x
 
def efp(x,eps):
    return np.abs(f(x+eps)-f(x))

def efn(x,eps):
    return np.abs(f(x-eps)-f(x))

def find_eps(eps):
    sig=0
    for i in range (0,N):
        if (np.abs(efp(x,eps[i])-efn(x,eps[i]))>0.0001*f(x)):
            sig=eps[i]
            break
    return sig


eps=np.linspace(0,1,N)
a=find_eps(eps)
print(a)

h=TH1D("h","",70,0.,0.)
Nev=11000
for i in range(0,Nev):
    x=rnd.Gaus(1,2*a)
    y=f(x)
    h.Fill(y)

f=TF1("f","gaus")
f.SetParameters(h.GetEntries()*h.GetBinWidth(1),1,0.02)
h.Fit("f")
h.Draw()

p=f.GetProb()
print(p)

gApplication.Run(True)

