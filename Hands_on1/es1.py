from ROOT import *
import math as m

rnd=TRandom3()
rnd.SetSeed(123456789)

tau1=0.1
tau2=1
tauacc=0.1
ris=0.1 #risoluzione temporale
f=0.3
nev=10000
h=TH1D("h","",100,0,5)
hm=TH1D("hm","",100,0,5)
hr=TH1D("hr","",100,0,5)

for i in range(0,nev):
    if rnd.Rndm()<f:
        t=-tau1*m.log(1-rnd.Rndm())
    else:
        t=-tau2*m.log(1-rnd.Rndm())
    h.Fill(t)
    if rnd.Rndm()<(1-exp(-t/tauacc)):
        hm.Fill(t)
        tr=rnd.Gaus(t,ris)
        hr.Fill(tr)


h.Draw()
hm.Draw("SAME")
hr.Draw("SAME")
hm.SetLineColor(kRed)
hr.SetLineColor(kGreen)
gApplication.Run(True)