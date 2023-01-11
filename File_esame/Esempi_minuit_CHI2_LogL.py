'''
CHI2
'''
#FIT CON COSTRUZIONE DEL CHI2

#ESEMPIO 1

from   iminuit import Minuit
import numpy as np

def f(x,a,b):
    return a*x+b
def chi2(a,b):
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],a,b))/ey[i])**2
    return val
x  = np.array([]); y  = np.array([]); ex = np.array([]); ey = np.array([])
for line in open("pendolo.dat"):
    dt  = line.split() #mi ritorna in quanti spazi è divisa la riga
    if len(dt)!=4:
        continue
    x   = np.append(x,  float(dt[0])); y   = np.append(y,  float(dt[1]))
    ex  = np.append(ex, float(dt[2])); ey  = np.append(ey, float(dt[3]))

m=Minuit(chi2, a=4, b=0)
m.print_level=3
m.migrad()

print(m.values)
print(m.errors)


#ESEMPIO 2

from   iminuit import Minuit
import numpy as np

def f(x,a,b):
    return a*x+b

def chi2(par):  #la differenza rispetto all'altro programma è che passiamo un vettore
    val = 0     #di paramtri e questo è comodo quanto abbiamo un fit che dipende da molti parametri
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],par[0],par[1]))/ey[i])**2
    return val

x  = np.array([]); y  = np.array([]); ex = np.array([]); ey = np.array([])
for line in open("pendolo.dat"):
    dt  = line.split() 
    if len(dt)!=4:
        continue
    x   = np.append(x,  float(dt[0])); y   = np.append(y,  float(dt[1]))
    ex  = np.append(ex, float(dt[2])); ey  = np.append(ey, float(dt[3]))

par= np.array([4.0,0.0])

m= Minuit(chi2,par)

m.migrad()

print(m.values)
print(m.errors)


#ESEMPIO 3

from   ROOT    import *
import numpy   as np
import ctypes  as ct

def func(x,a,b):
    return a*x+b

def fcn(npar, gin, f, par,iflag):
    chi2 = 0.0
    for i in range(0,len(x)):
        chi2 += ((y[i]-func(x[i],par[0],par[1]))/ey[i])**2
    f.value = chi2

x  = np.array([]); y  = np.array([]); ex = np.array([]); ey = np.array([])
for line in open("pendolo.dat"):
    dt  = line.split()
    if len(dt)!=4:
        continue
    x   = np.append(x,  float(dt[0])); y   = np.append(y,  float(dt[1]))
    ex  = np.append(ex, float(dt[2])); ey  = np.append(ey, float(dt[3]))

minuit = TMinuit(2)
minuit.SetFCN(fcn);
minuit.DefineParameter(0,'par0',4,0.01,0.,0.)
minuit.DefineParameter(1,'par1',0,0.01,0.,0.)
minuit.Command("MIGRAD")
a  = ct.c_double(0.0); b  = ct.c_double(0.0)
ea = ct.c_double(0.0); eb = ct.c_double(0.0)
minuit.GetParameter(0,a,ea);
minuit.GetParameter(1,b,eb);

print("a = %f +- %f, b = %f +- %f"%(a.value,ea.value,b.value,eb.value))


'''
FIT COMBINATO
'''

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <Math/Factory.h>

using namespace std;

namespace data{
  int n;
  vector<double> x1,t1,et1;
  vector<double> x2,t2,et2;
}

TF1 *f1;
TF1 *f2;

void chi2(int &npar, double *gin, double &f, double *par, int iflag){
  f=0;
  f1->SetParameters(par[0],par[1],par[2],par[3]);
  f2->SetParameters(par[0],par[1],par[4],par[5]);
  for(int i=0;i<data::n;i++){   //Questo è un caso particolare perchè ho lo stesso numero di dati per entrambi i fit
    f += pow( (data::t1[i]-f1->Eval(data::x1[i]))/data::et1[i] ,2);
    f += pow( (data::t2[i]-f2->Eval(data::x2[i]))/data::et2[i] ,2);
  }
}


int main(){

  TApplication app("app",0,NULL);

  ifstream fp1("perno1.dat");
  ifstream fp2("perno2.dat");
  double tx1,tt1,tex1,tet1;
  double tx2,tt2,tex2,tet2;


  TGraphErrors gr1;
  while (fp1 >> tx1 >> tt1 >> tex1 >> tet1){
    data::x1.push_back(tx1);
    data::t1.push_back(tt1);
    data::et1.push_back(tet1);
    gr1.SetPoint(gr1.GetN(),tx1,tt1);
    gr1.SetPointError(gr1.GetN()-1,tex1,tet1);
  }

  TGraphErrors gr2;
  while (fp2 >> tx2 >> tt2 >> tex2 >> tet2){
    data::x2.push_back(tx2);
    data::t2.push_back(tt2);
    data::et2.push_back(tet2);
    gr2.SetPoint(gr2.GetN(),tx2,tt2);
    gr2.SetPointError(gr2.GetN()-1,tex2,tet2);
  }
  data::n=data::x1.size();

  f1 = new TF1("f1","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n-1]);
  f2 = new TF1("f2","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n-1]);

  gr1.Fit("f1");
  gr2.Fit("f2");
  f1->SetLineColor(kRed);
  f2->SetLineColor(kBlue);
  gr1.Draw("AP");
  gr2.Draw("P");
  //app.Run(true);

  // Minuit
  TMinuit minuit(6);
  minuit.SetFCN(chi2);

  minuit.DefineParameter(0,"x0",36,0.01,0.,0.);
  minuit.DefineParameter(1,"T0",4,0.01,0.,0.);
  minuit.DefineParameter(2,"a1",f1->GetParameter(2),0.01,0.,0.);
  minuit.DefineParameter(3,"b1",f1->GetParameter(3),0.01,0.,0.);
  minuit.DefineParameter(4,"a2",f1->GetParameter(2),0.01,0.,0.);
  minuit.DefineParameter(5,"b2",f1->GetParameter(3),0.01,0.,0.);

  minuit.Command("MIGRAD");

  app.Run(true);

  return 0;
}






'''
LIKELIHOOD
'''

#FIT CON LIKELIHOOD STANDARD

using namespace std;

namespace data{
  vector<double>  x;
}

void logl(int &npar, double *gin, double &f, double *par, int iflag){  
  f = 0.0;
  // Definisco la logl
  for (int i=0;i<data::x.size();i++){     //la pdf e` 1/tau*exp(-t/tau)  tau e` il parametro[0]
    f += log(par[0]) + data::x[i]/par[0]; //in realta` stiamo minimizzando -logL
  }
}

void fitexp(){

  ifstream file("exp.txt");
  double x;
  TH1D *h = new TH1D("h","",40,0,10);
  while (file >> x){
    data::x.push_back(x);
    h->Fill(x);
  }
  TMinuit minuit(1);  //1 è il numero di parametri
  minuit.SetFCN(logl);
  minuit.SetErrorDef(0.5); //nel caso usassimo MINOS
  
  // Istruisco di logLikelihood
  minuit.DefineParameter(0,"tau",2,0.01,0.,0.);  //2 e` il valore di partenza e 0.01 lo step iniziale
  
  minuit.Command("MIGRAD");
  double tau, etau;
  minuit.GetParameter(0,tau,etau);

  h->SetMarkerStyle(20);
  h->Draw("E");
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);
  // Disegno della funzione
  fe->SetParameter(1,tau);
  fe->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));//settiamo il parametro [0] all'area dell'istogramma per 
  fe->Draw("same");                                     //normalizzazione

  cout<<"tau="<<tau<<"+-"<<etau<<endl;

}


#FIT BINNATO CON LIKELIHOOD

from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau):
    val = 0
    # Definisco logl
    for i in range (1,h.GetNbinsX()+1):
        ni = h.GetBinContent(i)
        xmin = h.GetBinLowEdge(i)
        xmax = xmin+h.GetBinWidth(i)
        pi = exp(-xmin/tau)-exp(-xmax/tau)
        val = val - ni*log(pi)
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.txt"):
    h.Fill(float(line))

#m = Minuit(flogl,tau=2,errordef=0.5,print_level=3) #COMANDI PER PYTHON2
    
m = Minuit(flogl,tau=2) #COMANDI PER PYTHON3
m.errordef=0.5
m.print_level=2

# Istruisco fir di logl
m.migrad()       

tau = m.values[0]
etau = m.errors[0]

print(tau)
print(etau)

h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)
f.SetParameter(1,tau)
f.SetParameter(0,h.GetBinWidth(1)*h.GetEntries())
f.Draw("SAME")

f.FixParameter(0,1)
h.Fit("f","0MULTI") #MULTI rappresenta la multinomiale;
                    #Lo 0 davanti a MULTI serve per non far disegnare il grafico della funzione normalizzata

f.SetParameter(0,h.GetBinWidth(1)*h.GetEntries())
f.Draw("SAME")

gApplication.Run(True) 



#FIT BINNATO ESTESO CON LIKELIHOOD

from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau,norm):
    val = 0
    # Definisco logl
    for i in range(1,h.GetNbinsX()):
        ni=h.GetBinContent(i)
        xmin=h.GetBinLowEdge(i)
        xmax=h.GetBinLowEdge(i)+h.GetBinWidth(i)
        pi = np.exp(-xmin/tau)-np.exp(-xmax/tau)
        mui=norm*pi
        val = val-ni*np.log(mui)-mui

    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.txt"):
    h.Fill(float(line))

#m = Minuit(flogl,tau=2,norm=1000,errordef=0.5,print_level=3) #OLTRE A TAU VOGLIAMO FITTARE ANCHE IL NUMERO DI ENTRATE

m = Minuit(flogl, tau=2, norm=1000)
m.errordef=0.5
m.print_level=2

# Istruisco fir di logl
m.migrad()
tau=m.values[0]
etau=m.errors[0]
norm=m.values[1]
enorm=m.errors[1]

print(tau)
print(etau)
print(norm)
print(enorm)

# tau = m.values[0]
h.Draw("E")

# Disegno del fit
f = TF1("f","[0]*1/[1]*exp(-x/[1])",0,20)

f.SetParameter(1,tau)
f.SetParameter(0,norm*h.GetBinWidth(1))

f.Draw("SAME")

h.Fit("f","L") #non dobbiamo fissare par0 a 1 perche` L non e` una pdf

gApplication.Run(True)