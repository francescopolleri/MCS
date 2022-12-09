import numpy as np
from ROOT import *
import math as m

rnd=TRandom3()
rnd.SetSeed(123456789)

N=1000

x0=10
sigma=2
delta=2

h=TH1D("h","",100,0.,0.)

for i in range(0,N):
    x1=rnd.Gaus(x0,sigma)

    b=x1+delta
    a=x1-delta

    s=rnd.Rndm()*(b-a)+a

    h.Fill(s)

mu=h.GetMean()
sig=h.GetRMS()
norm=h.GetBinWidth(1)*h.GetEntries()

f=TF1("f","gaus")
f.SetParameters(norm,mu,sig)

gStyle.SetOptFit();

h.Fit("f")
h.Draw()

print('mu = ',mu)
print('sig =',sig)
print('norm = ',norm)

print('mu_fit = ',f.GetParameter(1),'+/-',f.GetParError(1))
print('sig_fit =',f.GetParameter(2),'+/-',f.GetParError(2))
print('norm_fit = ',f.GetParameter(0),'+/-',f.GetParError(0))

gApplication.Run(True)

