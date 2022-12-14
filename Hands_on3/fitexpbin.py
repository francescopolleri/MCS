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

