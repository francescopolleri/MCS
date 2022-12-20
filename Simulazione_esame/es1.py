from ROOT import *
from iminuit import Minuit
import numpy as np
from math import *

def flogl(k,d):
      val=0
      for i in range (1,h.GetNbinsX()+1):
          ni = h.GetBinContent(i)
          xmin = h.GetBinLowEdge(i)
          xmax = xmin+h.GetBinWidth(1)
          pi = (-exp(-(xmax*d)**k) + exp(-(xmin*d)**k))*k
          val = val+ni*log(abs(pi))
      return -val


rnd = TRandom3()
rnd.SetSeed(123456789)

Nev=10000
lam = 1
kappa = 1.5

xi=np.array([])

h=TH1D("h","",80,0.,0.)

for i in range (0,Nev):
  x=lam*(-np.log(1-rnd.Rndm()/kappa))**(1/kappa)
  h.Fill(x)
  xi=np.append(xi, x)


min = Minuit(flogl,k=1.5,d=1)
min.errordef=0.5
min.print_level=2

min.migrad()

K=min.values[0]
d=min.values[1]
eK=min.errors[0]
ed=min.errors[1]
print('/**************/')
print(K,'+/-',eK,'  ',1/d,'+/-',ed/(d**2))
print('/**************/')

f=TF1("f","[0]*[1]/pow([2],[1])*pow(x,[1]-1)*exp(-pow(x/[2],[1]))",0,1.05)
f.SetParameter(0,h.GetBinWidth(1)*h.GetEntries())
f.SetParameter(1,K)
f.SetParameter(2,1/d)

h.Draw("E")
f.Draw("SAME")

f.FixParameter(0,1)
h.Fit("f","0MULTI")

f.SetParameter(0,h.GetBinWidth(1)*h.GetEntries())
f.Draw("SAME")

gApplication.Run(True)
