from ROOT import *
import numpy as np
import matplotlib.pyplot as plt

rn=TRandom3()
rn.SetSeed(123456789)

N=100000
n_in=0.
s=0.

a=np.array([])
dim=np.array([])

for d in range (2,12):
    n_in=0.
    for i in range (0,N):
        b=0.
        for j in range (0,d):
            s=2*rn.Rndm()-1
            b+=s*s
        if(b<1):
             n_in=n_in+1
    a=np.append(a,2**d*n_in/N)
    dim=np.append(dim,d)
    #print('dimension =',d)
    #print('alpha=',2**d*n_in/N)


g=TGraph()
c1=TCanvas("c1","",500,500)
c1.Draw()

for i in range (len(a)):
    g.SetPoint(i,dim[i],a[i])

g.SetMarkerStyle(20)
g.SetMarkerColor(kBlack)
g.SetTitle("Value of #alpha vs Dimension;Dimension;#alpha")
g.Draw("AP")

f=TF1("f","pow(TMath::Pi(),x/2)/TMath::Gamma(x/2+1)",1,15)
f.SetLineColor(kRed)
f.Draw("SAME")

#c1.BuildLegend()

legend = TLegend(0.52,0.65,0.9,0.9)
legend.SetTextSize(0.03)
legend.AddEntry("f","#frac{#pi^{d/2}}{#Gamma(#frac{d}{2}+1)} ","l")
legend.AddEntry("g","Monte Carlo result","p")
legend.Draw()

gApplication.Run(True)