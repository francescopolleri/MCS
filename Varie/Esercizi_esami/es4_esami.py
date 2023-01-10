import numpy as np
import matplotlib.pyplot as plt
from ROOT import *

f=TF1("f","[1]*pow(x,2)*exp(-x/[0])/(2*pow([0],3))",0,20)
h=TH1D("h","",30,0,20)

for line in open("dati_gamma.txt"):
    h.Fill(float(line))

f.SetParameter(1,h.GetEntries()*h.GetBinWidth(1))
f.SetParameter(0,2)
h.Fit("f","L")
h.Draw()

f.Draw("SAME")

gApplication.Run(True)
