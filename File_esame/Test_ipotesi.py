from   sys   import *
from   math  import *
from   ROOT  import *
import numpy as np
from   scipy import stats
import mplhep as hep
import matplotlib.pyplot as plt

file1 = open("s1.dat")
file2 = open("s2.dat")

h1 = TH1D("h1","",12,0,0.5)
h2 = TH1D("h2","",12,0,0.5)

x1 = np.array([])
for line in file1:
    val = line.split()
    x1 = np.append(x1,float(val[0]))  #val[0] indica che prendo il primo elemento della riga
    h1.Fill(float(val[0]))

x2 = np.array([])
for line in file2:
    val = line.split()
    x2 = np.append(x2,float(val[0]))
    h2.Fill(float(val[0]))

hep.histplot(h1,color='g')
hep.histplot(h2,color='b')

#TEST BINNED  CHI2
print('TEST CHI2')     #Il test Chi2 è un test binned
print(h1.Chi2Test(h2)) #Ritorna il valore del p-value
print(h2.Chi2Test(h1))

#TEST UNBINNED KS A 2 CAMPIONI
print('KS2 TEST')
t_ks,p_ks=stats.ks_2samp(x1,x2) #questo test prende i due array con i dati degli istogrammi
print(p_ks) 

#TEST KS (CONFRONTO ISTOGRAMMA CON DISTRIBUZIONE)
print('KS TEST ')
test = stats.expon(loc=0,scale=0.1) #loc indica di quanto è la traslazione mentre 'scale' è la media 
t_ks,p_ks=stats.kstest(x1,test.cdf) 
print(p_ks)

#TEST FIT SU ESPONENZIALE IGNOTO
f=TF1("f","[0]/[1]*exp(-x/[1])",0,0.5)
f.SetParameter(1,1)
h1.Fit("f")
print(f.GetProb())

area=h1.GetEntries()*h1.GetBinWidth(1)
x1=np.sort()
plt.plot(x1,area*test.pdf(x1),color='r')
plt.show()

'''
Tornando al test ks se la distribuzione da testare è una gaussiana i comandi da usare sono:

test=stats.norm(loc=mu,scale=sigma)
t_ks,p_ks=stats.kstest(x,test.cdf)
Per fare il plot usare area*test.pdf(x)

Se la distribuzione è una poissoniana:
test=stats.poisson(mu)
t_ks,p_ks=stats.kstest(x,test.cdf)
Per fare il plot->area*test.pmf(x)

'''

gApplication.Run(True)