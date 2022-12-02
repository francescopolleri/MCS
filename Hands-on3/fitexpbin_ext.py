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
        pi = exp(-xmin/tau)-exp(-xmax/tau)
        mui=norm*pi
        val = val-ni*log(mui)-mui

    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

#m = Minuit(flogl,tau=2,norm=1000,errordef=0.5,print_level=3) #OLTRE A TAU VOGLIAMO FITTARE ANCHE IL NUMERO DI ENTRATE

m = Minuit(flogl,tau=2,norm=1000)
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
f.Setparameter(0,norm*h.GetBinWidth(1))

f.Draw("SAME")

h.Fit("f","L") #non dobbiamo fissare par0 a 1 perche` L non e` una pdf

gApplication.Run(True)

