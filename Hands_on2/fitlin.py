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
