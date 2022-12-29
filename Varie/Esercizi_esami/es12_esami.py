import numpy as np
import matplotlib.pyplot as plt
from ROOT import *
import time as t
from scipy import stats
import mplhep as hep

rnd=TRandom3()
rnd.SetSeed(123456789)

Nev=100000

mu=20
n=0
s=0

h=TH1D("h","",12,0,0)
x=np.array([])
for i in range (0,Nev):
    dt = -np.log(1-rnd.Rndm())
    s += dt
    if(s>mu):          
        h.Fill(i-n-1)
        x=np.append(x,i-n-1)  
        n=i
        s=0
    

area=h.GetEntries()*h.GetBinWidth(1)

x=np.sort(x)

test = stats.poisson(mu)
t_ks,p_ks = stats.kstest(x,test.cdf)

print('p_value = ',p_ks)

hep.histplot(h,color='k')
plt.plot(x,area*test.pmf(x),color='r')
plt.show()

gApplication.Run(True)