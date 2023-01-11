import numpy as np
import math
from ROOT import *
from scipy import stats

B=0.1
V=1000
q=1.6e-19
u=1.66e-27

nbins=input('nbins: ')

c1 = TCanvas("c1","",800,500)
c1.Divide(2,1)

h=TH1D("h","",int(nbins),0.55,0.6)

for line in open("Dati_spettrometro.txt"):
    h.Fill(float(line))

area=h.GetEntries()*h.GetBinWidth(1)

f1=TF1("f1","[2]*TMath::Gaus(x,[0],[1],1)")
f1.SetParameters(0.57,0.003,500*0.05/h.GetNbinsX())

c1.cd(1)
h.Fit("f1","L")
h.Draw()

p_value=f1.GetProb()
print('p-value = ',f1.GetProb())
if(p_value>0.05):
    print('Ipotesi accettata')
else:
    print('Ipotesi rigettata')

c1.cd(2)
k=TH1D("k","",int(nbins),0.55,0.6)

for line in open("Dati_spettrometro.txt"):
    k.Fill(float(line))

f2=TF1("f2","[0]*( [1]*TMath::Gaus(x,[2],[3],1) + (1-[1])*TMath::Gaus(x,[4],[5],1) )",0.55,0.6)
f3=TF1("f3","[0]*TMath::Gaus(x,[1],[2],1)")
f4=TF1("f4","[0]*TMath::Gaus(x,[1],[2],1)")
f3.SetLineColor(kGreen)
f4.SetLineColor(kYellow)


f2.FixParameter(0,1)
f2.SetParameter(1,0.5)
f2.SetParameter(2,0.567)
f2.SetParameter(3,0.002)
f2.SetParameter(4,0.585)
f2.SetParameter(5,0.005)

f2.SetParLimits(1,0,0.99)

k.Fit("f2","0 MULTI","",0.556,0.589)
f2.SetParameter(0,500*0.05/k.GetNbinsX())

f3.SetParameter(0,f2.GetParameter(0)*f2.GetParameter(1))
f3.SetParameter(1,f2.GetParameter(2))
f3.SetParameter(2,f2.GetParameter(3))
f4.SetParameter(0,f2.GetParameter(0)*(1-f2.GetParameter(1)))
f4.SetParameter(1,f2.GetParameter(4))
f4.SetParameter(2,f2.GetParameter(5))

k.Draw()
f2.Draw('SAME')
f3.Draw('SAME')
f4.Draw('SAME')

c1.SaveAs("es3_esami.pdf")

print(f2.GetProb())
p_value=f2.GetProb()
if(p_value>0.05):
    print('Ipotesi accettata')
else:
    print('Ipotesi rigettata')

print('Le componenti delle due gaussiane sono: ',f2.GetParameter(1),' ',1-f2.GetParameter(1))

def A(d1,d2):
    A1=(d1/2)**2*B**2*q/(2*V*u)
    A2=(d2/2)**2*B**2*q/(2*V*u)
    return A1,A2

A1,A2=A(f2.GetParameter(2),f2.GetParameter(4))

print('I numeri atomici degli ioni sono: ',A1,' ',A2)

gApplication.Run(True)