from ROOT import *
import numpy as np
import matplotlib.pyplot as plt


def f(x):
    return 1/x

rnd=TRandom3()
rnd.SetSeed(123456789)

N=10000

mu=2.0
sig=0.5

h=TH1D("h","",100,0,0)

for i in range(0,N):
    x=rnd.Gaus(mu,sig)
    h.Fill(f(x))

h.Draw()
print(h.GetMean()," ",h.GetStdDev())
gROOT.GetListOfCanvases().Draw()
gApplication.Run(True)