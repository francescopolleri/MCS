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
