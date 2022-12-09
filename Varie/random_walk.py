from ROOT import *
import math as m

rnd=TRandom3()
rnd.SetSeed(123456789)

f=0.5
nev=[20, 40, 60]
N=1000

c1=TCanvas("c1","",500,500)
c2=TCanvas("c2","",500,500)
c3=TCanvas("c3","",500,500)
g=TGraph()
h20=TH1D("h20","",100,0.,0.)
h40=TH1D("h40","",100,0.,0.)
h60=TH1D("h60","",100,0.,0.)

s=0
s2=0
for j in range(len(nev)):
    N=nev(j)
    for i in range (0,N):
        if rnd.Rndm()<f:
            d=rnd.Rndm()*m.sqrt(3)
        else:
            d= -rnd.Rndm()*m.sqrt(3)
    
        s = s+d
    

c1.cd()
h1.Draw()
c2.cd()
h2.Draw()
c3.cd()
h3.Draw()
    

    #s2 += pow(s,2)
    #g.SetPoint(i,i,s2)

#c1.cd()
#g.Draw("AP")

gApplication.Run(True)


    




    
