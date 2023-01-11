import numpy as np
import matplotlib.pyplot as plt
import ROOT 
import scipy.stats as sts

rnd=ROOT.TRandom3()
rnd.SetSeed(123456789)

Nev=10000
_lambda=0.01
mu=150
sig=10

f=0.99

h=ROOT.TH1D("h","",100,0,600)
h_gaus=ROOT.TH1D("h_gaus","",9,125,175)
h_exp=ROOT.TH1D("h_exp","",100,0,600)

n_bkg=0
n_obs=0

for i in range(0,Nev):
    p=rnd.Rndm()
    if(p<f):
        x=-1/_lambda*np.log(1-rnd.Rndm())
        h_exp.Fill(x)
        if(x>125 and x<175):
            n_bkg=n_bkg+1
    else:
        x=rnd.Gaus(mu,sig)
        if(x>125 and x<175):
            h_gaus.Fill(x)
    h.Fill(x)
    if(x>125 and x<175):
        n_obs=n_obs+1

area=h.GetEntries()*h.GetBinWidth(1)

f_exp=ROOT.TF1("f_exp","[0]*(1-[1])*[2]*exp(-x*[2])")  #RICERCA DI n_bkg_true
f_exp.SetParameters(area,f,_lambda)
h_exp.Fit("f_exp","0 L")
Int=f_exp.Integral(125,175)
n_bkg_true=Int/h_exp.GetBinWidth(1)
print('# bkg_true',n_bkg_true)

print('# bkg=',n_bkg)
print('# obs= ',n_obs)

p=0
for i in range (0,n_obs):
    p += ROOT.TMath.PoissonI(i,n_bkg_true)

n_sig=sts.norm.ppf(p)
print('# sigma da ipotesi nulla = ',n_sig)

print('p-value = ',1-p)
if(1-p>0.05):
    print('Al 5{%} di significanza non possiamo rigettare ipotesi nulla')
else:
    print('Al 5{%} di significanza possiamo rigettare ipotesi nulla')
    for ns in range (0,100000): #RICORDARSI DI CONTROLLARE IL VALORE MASSIMO DEL RANGE DI ns !!!
        prob=0
        for j in range(0,n_obs):
            prob += ROOT.TMath.PoissonI(j,ns+n_bkg_true)
        if(prob<0.05):
            print('UL(95% CL)= ',ns+n_bkg_true)
            break
    for ns in range (0,100000):
        prob=0
        for j in range (0,n_obs):
            prob += ROOT.TMath.PoissonI(j,ns+n_bkg_true)
        if(1-prob>0.05):
            print('LL (95% CL)= ',ns+n_bkg_true)
            break

f=ROOT.TF1("f","[0]*( (1-[1])*[2]*exp(-[2]*x) + [1]*TMath::Gaus(x,[3],[4],1) )",0,600)
f.SetParameters(area,0.2,0.01,150,10)


h.Draw()
h_gaus.SetFillColor(3)
h_exp.SetFillColor(41)
h_exp.Draw("SAME")
h_gaus.Draw("SAME")
f.Draw("SAME")
h.Fit("f","0 L")
print(f.GetProb())

ROOT.gApplication.Run(True)


''''
#ESERCIZIO CON POISSONIANA 
using namespace std;

void Hyp_test_Poisson(){

int nobs=30;
int n_att=15;

double p=0;
for (int i=0;i<nobs;i++){
    p += TMath::PoissonI(i,n_att);
}

cout<<"p-value = "<<1-p<<endl;
if(1-p<0.05){
    cout<<"Al 5{%} possiamo rigettare l'ipotesi nulla"<<endl;
}
else{
    cout<<"Al 5{%} di significanza non possiamo rigettare l'ipotesi nulla"<<endl;
}

for (int ns=0;ns<1000;ns++){
    double prob=0;
    for(int j=0;j<=nobs;j++){
	    prob+= TMath::PoissonI(j,ns+n_att);
    }
    if(1-prob>0.05){   //Per avere UL devo mettere prob<0.05
      cout<<"LL (95% CL)= "<<ns<<endl;  
    break;
    }
  }

for (int ns=0;ns<1000;ns++){
    double prob=0;
    for(int j=0;j<=nobs;j++){
	    prob+= TMath::PoissonI(j,ns+n_att);
    }
    if(prob<0.05){   //Per avere UL devo mettere prob<0.05
      cout<<"UL (95% CL)= "<<ns<<endl;  
    break;
    }
  } 

}
'''