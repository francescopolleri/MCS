import numpy as np
from ROOT import *
import math as m
from scipy import stats
import mplhep as hep
import matplotlib.pyplot as plt

rnd=TRandom3()
rnd.SetSeed(123456789)

N=1000

x0=10
sigma=2
delta=2

h=TH1D("h","",80,0,20)

x=np.array([])

for i in range(0,N):
    x1=rnd.Gaus(x0,sigma)

    b=x1+delta
    a=x1-delta

    s=rnd.Rndm()*(b-a)+a
    
    x=np.append(x,s)
    h.Fill(s)

area=h.GetEntries()*h.GetBinWidth(1)

#Per verificare che la distribuzione sia compatibile con una  
#gaussiana faccio un test di Kolmogorov

test=stats.norm(loc=x0,scale=np.sqrt(sigma**2+(delta**2)/3))  #loc è il valor medio
t_ks,p_ks=stats.kstest(x,test.cdf)                            #scale è la sigma

print(p_ks)

x=np.linspace(h.GetXaxis().GetXmin(),h.GetXaxis().GetXmax(),100)

hep.histplot(h,color='k')
plt.plot(x,area*test.pdf(x),color='r')
plt.show()

gApplication.Run(True)

