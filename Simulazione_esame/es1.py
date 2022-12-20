from ROOT import *
import numpy as np
from iminuit import Minuit
import math as m

rnd = TRandom3()
rnd.SetSeed(123456789)

Nev=1000
lam = 1
kappa = 1.5

xi=np.array([])

h=TH1D("h","",80,0.,0.)

for i in range (0,Nev):
  
  x=lam*(-np.log(1-rnd.Rndm()/kappa))**(1/kappa)
  h.Fill(x)
  xi=np.append(xi, x)

#h.Draw()

def flogl(k,lamb):
    val=0
    for i in range (1,h.GetNbinsX()+1):
        ni = h.GetBinContent(i)
        xmin = h.GetBinLowEdge(i)
        xmax = xmin+h.GetBinWidth(1)
        pi= -k*(np.exp(-(xmax/lamb)**k) - np.exp(-(xmin/lamb)**k))
        val = val -ni * np.log(np.abs(pi))
    return val


min = Minuit(flogl,k=1,lamb=10)

min.migrad()
min.errordef=0.5
min.print_level=2

K=min.values[0]
L=min.values[1]

print(K,L)

f=TF1("f","[0]*[1]/pow([2],[1])*pow(x,[1]-1)*exp(-pow(x/[2],[1]))",0,1.1)
f.SetParameter(0,h.GetBinWidth(1)*h.GetEntries())
f.SetParameter(1,1.5)
f.SetParameter(2,1)

h.Fit("f")
h.Draw()

gApplication.Run(True)
