from ROOT import *
from iminuit import Minuit
import numpy as np
from math import *

rnd = TRandom3()
rnd.SetSeed(123456789)

Nev=10000
lamb = 1
kappa = 1.5

xi=np.array([])

h=TH1D("h","",80,0,3.7)

for i in range (0,Nev):
  x=lamb*(-np.log(1-rnd.Rndm()))**(1/kappa)
  h.Fill(x)
  xi=np.append(xi, x)

#OPZIONE MULTI
'''
f=TF1("f","[0]*[1]/pow([2],[1])*pow(x,[1]-1)*exp(-pow(x/[2],[1]))",0,4)
f.FixParameter(0,1)
f.SetParameter(1,kappa)
f.SetParameter(2,lamb)

h.Fit("f","0MULTI")
f.SetParameter(0,h.GetBinWidth(1)*h.GetEntries())
h.Draw()
f.Draw("SAME")
'''


#ALTRIMENTI UN MODO PIU' VELOCE E' USARE OPZIONE L

f=TF1("f","[0]*[1]/pow([2],[1])*pow(x,[1]-1)*exp(-pow(x/[2],[1]))",0,4)
f.SetParameter(0,h.GetBinWidth(1)*h.GetEntries())
f.SetParameter(1,kappa)
f.SetParameter(2,lamb)

h.Fit("f","L")

h.Draw()



gApplication.Run(True)
