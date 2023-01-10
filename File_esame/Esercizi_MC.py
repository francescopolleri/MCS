#ESERCIZIO INERZIA 1

import numpy as np 
import matplotlib.pyplot as plt
from ROOT import *

rnd=TRandom3()
rnd.SetSeed(123456789)

R=6
r=1
rho=1.3

d2=0; d2r=0

n_in=0; n_in_r=0
Nev=10000000

for i in range (0,Nev):
    x=2*R*rnd.Rndm()-R
    y=2*R*rnd.Rndm()-R
    z=2*R*rnd.Rndm()-R
    xs=2*r*rnd.Rndm()-r
    ys=2*r*rnd.Rndm()-r
    zs=2*r*rnd.Rndm()-r
    if(x**2+y**2+z**2<R**2):
        d2+=(x**2+y**2)
        n_in=n_in+1
    if(xs**2+ys**2+zs**2<r**2):     #in questo caso ho potuto fare i questo modo perche la sfera piccola è
        d2r+=((xs+2)**2+(ys+2)**2)  #dentro quella grande
        n_in_r=n_in_r+1
        
V=4/3*np.pi*R**3
Vr=4/3*np.pi*r**3

pR=n_in/Nev; pr=n_in_r/Nev

print('Vsfera_R=',(2*R)**3*pR)
print('VsferaR con buco=',(2*R)**3*pR-pr*(2*r)**3)

I=rho*V*d2/n_in
I_r=rho*Vr*d2r/n_in_r

print(I-I_r)

#ESERCIZIO INERZIA 2
import numpy as np 
import matplotlib.pyplot as plt
from ROOT import *

rnd=TRandom3()
rnd.SetSeed(123456789)

Nev=1000000
n_in=0
n_in_s=0
rho=1
Rc=1
Rs=1
H=2

d2=0; n_in=0

ymax=np.max([Rs,Rc])
zmax=np.max([Rs,H/2])
Vint=(2*ymax)*(2*zmax)*(2*Rc+2*Rs)

for i in range(0,Nev):
    x=(2*Rc+2*Rs)*rnd.Rndm()
    y=(2*ymax)*rnd.Rndm()-ymax
    z=2*zmax*rnd.Rndm()-zmax
    if ((x-Rc)**2+(y)**2<Rc**2 or (x-2*Rc-Rs)**2+(y)**2+z**2<Rs**2):
        n_in=n_in+1
        d2+=((x-Rc)**2+(y)**2)

p=n_in/Nev
ep=np.sqrt(p*(1-p)/Nev)
print(p)

Vc=np.pi*Rc**2*H
Vs=4/3*np.pi*Rs**3

V_tot=np.pi*Rc**2*H+4/3*np.pi*Rs**3
V_tot_MC=Vint*p
eV_MC=V_tot*ep

print('V_tot analitico = ',V_tot)
print('V_tot_MC = ',V_tot_MC,'+/-',eV_MC)

I_MC=rho*V_tot_MC*d2/n_in
I_A=1/2*rho*Vc*Rc**2 + 2/5*rho*Vs*Rs**2 + rho*Vs*(Rc+Rs)**2

eI_MC=ep*rho*Vint*d2/n_in

print('I_A = ',I_A)
print('I_MC = ',I_MC,'+/-',eI_MC)

#ESERCIZIO BINOMIALE E DECADIMENTI
import numpy as np 
import matplotlib.pyplot as plt
from ROOT import *

tau1=0.1; tau2=1; tau_acc=0.1
f=0.3

rnd=TRandom3()
rnd.SetSeed(123456789)

c1=TCanvas("c1","",400,400)
h=TH1D("h","",100,0,5)
k=TH1D("k","",100,0,5)

Nev=10000
for i in range (0,Nev):
    if (rnd.Rndm()<f):
        t=-tau1*np.log(1-rnd.Rndm())
    else:
        t=-tau2*np.log(1-rnd.Rndm())
    h.Fill(t)
    if(rnd.Rndm()<(1-np.exp(-t/tau_acc))):
        k.Fill(t)


c1.Draw()
h.Draw()
k.Draw('SAME')
h.SetLineColor(kBlue)
k.SetLineColor(kRed)


#ESERCIZIO FASCIO FOTONI ISOTROPO
{
double L=0.01;
double d=0.20;

TRandom3 rnd;
rnd.SetSeed(123456789);

int ntot=100000;
int n1=0;
int n2=0;
for(int i=0;i<ntot;i++){
  double phi=2*TMath::Pi()*rnd.Rndm();
  double costheta=2*rnd.Rndm()-1;  //mi serve un intervallo tra -1 e 1
  double theta=acos(costheta);
  double alpha=d/costheta;
  if (theta>TMath::Pi()/2) continue;  //accetto solo il caso in cui theta<pi/2 cioè tolgo i fotoni che vanno all'indietro
  double x=alpha*sin(theta)*cos(phi);
  double y=alpha*sin(theta)*sin(phi);
  if(abs(x)<L/2 && abs(y)<L/2){  //mi sposto di L/2 in alto e in basso per far passare la direzione 
    n1++;                        //radiale per uno spigolo del quadrato
  }
  if(x>-L && x<0 && y>0 && y<L){
    n2++;
  }
}

double p=(double)n1/ntot;
double ep=sqrt(p*(1-p)/ntot);
cout<<"p="<<p<<"+/-"<<ep<<endl;
double p2=(double)n2/ntot;
double ep2=sqrt(p2*(1-p2)/ntot);
cout<<"p2="<<p2<<"+/-"<<ep2<<endl;
cout<<"approx d>>L: "<<L*L/(4*TMath::Pi()*d*d)  //ris analitico d>>L
}

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#ESERCIZI INTEGRALI

import math as m
import numpy as np
import matplotlib.pyplot as plt
from ROOT import *

a=1

xmin=0
xmax=3

def f1(x):
    return np.exp(-x)*(1+a*np.cos(x))

def f2(x):
    return np.exp(-x)*(1+a) 

def fInt(x):
    return -(1/2.)*exp(-x)*(-a*sin(x)+a*cos(x)+2)

x=np.linspace(xmin,xmax,100)

fig, ax=plt.subplots()
ax.plot(x,f1(x),color='r',label='$e^{-x}(1+cos(x))$')
ax.plot(x,f2(x),color='b',label='$2e^{-x}$')
ax.legend()
plt.show()

rnd=TRandom3()
rnd.SetSeed(123456789)
N=10000

'''
CAMPIONAMENTO SEMPLICE
'''
tcs=TStopwatch()

fm=0.
fm2=0.
for i in range(0,N):
    x=rnd.Rndm()*(xmax-xmin)+xmin
    y=f1(x)
    fm=fm+y
    fm2=fm2+y*y

fm=fm/N
fm2=fm2/N

I=fm*(xmax-xmin)
eI=(xmax-xmin)*np.sqrt((fm2-fm*fm)/(N-1))

print('CAMPIONAMENTO SEMPLICE')
print('I con camp.semplice =',I,"+/-",eI)
print('I nominale =',fInt(xmax)-fInt(xmin))
print('CPU time used =',tcs.CpuTime())

'''
CAMPIONAMENTO D'IMPORTANZA
'''
tci=TStopwatch()

#applico inversione a g(x)=exp(-x)/(exp(-xmin)-exp(-xmax))

sm=0.
sm2=0.
for i in range(0,N):
    x=-np.log(1.0-(rnd.Rndm()*(np.exp(-xmin)-np.exp(-xmax))))
    y=f1(x)/(np.exp(-x)/(np.exp(-xmin)-np.exp(-xmax)))
    sm=sm+y
    sm2=sm2+y*y

sm=sm/N
sm2=sm2/N

I=sm
eI=np.sqrt((sm2-sm*sm)/(N-1))

print('CAMPIONAMENTO IMPORTANZA')
print('I con comp.imp =',I,'+/-',eI)
print('I nominale =',fInt(xmax)-fInt(xmin))
print('CPU time used =',tci.CpuTime())


'''
REIEZIONE
'''
import matplotlib.pyplot as plt
import math 
import numpy as np
from ROOT import *

rnd=TRandom3()
rnd.SetSeed(123456789)

def fun(x):
    return 3*x**2+4*x**3

def fInt(x):
    return x**3+x**4

Nev=1000000

b=5; a=3

l=np.linspace(a,b,100)

y=np.array([])
for i in range (0,100):
    y=np.append(y,fun(l[i]))
   
ymin=np.min(y)
ymax=np.max(y)

n_in=0
for i in range (0,Nev):
    x=(b-a)*rnd.Rndm()+a
    y=rnd.Rndm()*ymax
    if(y<=fun(x)):
        n_in=n_in+1

p=n_in/Nev

I=fInt(b)-fInt(a)

I_MC=p*ymax*(b-a)   #Devo considerare tutta l'area sottostante f(x) quindi y corre tra 0 e ymax
e_I_MC=np.sqrt(p*(1-p)/Nev)

print('I analitico =',I)
print('I_MC = ',I_MC,' +/- ',e_I_MC)