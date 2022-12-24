import numpy as np
import math
from ROOT import *
from scipy import stats


B=0.1
V=1000
q=1.6e-19
u=1.66e-27

h=TH1D("h","",30,0.,0.)
k=TH1D("k","",30,0.,0.)

x=np.array([])
for line in open("Dati_spettrometro.dat"):
    h.Fill(float(line))
    x=np.append(x, float(line))

area=h.GetEntries()*h.GetBinWidth(1)

for i in range(0,len(x)):
    k.Fill(x/area)

f1=TF1("f1","[2]*TMath::Gaus(x,[0],[1],1)")
f1.SetParameters(0.57,0.003,h.GetEntries()*h.GetBinWidth(1))


h.Fit("f1")
#h.Draw()

p_value=f1.GetProb()
print('p-value = ',f1.GetProb())
if(p_value>0.05):
    print('Ipotesi accettata')
else:
    print('Ipotesi rigettata')



f2 = TF1("f2","[0]*TMath::Gaus(x,[1],[2],1)+[3]*TMath::Gaus(x,[4],[5],1)")
f2.SetParameter(1,0.568)
f2.SetParameter(2,0.001)
f2.SetParameter(4,0.5853)
f2.SetParameter(5,0.0005)
#f2.SetParameter(3,0.005)
f2.FixParameter(0,1)
f2.FixParameter(3,1)  

h.Fit("f2","0MULTI","",0.556,0.589)
f2.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))
f2.SetParameter(3,0.005)

h.Draw()

def A(d1,d2):
    A1=(d1/2)**2*B**2*q/(2*V*u)
    A2=(d2/2)**2*B**2*q/(2*V*u)
    return A1,A2

A1,A2=A(f2.GetParameter(1),f2.GetParameter(4))

print(A1,' ',A2)

gApplication.Run(True)