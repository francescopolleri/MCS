from   sys   import *
from   math  import *
from   ROOT  import *
import numpy as np
from   scipy import stats

file1 = open("s1.dat")
file2 = open("s2.dat")

h1 = TH1D("h1","",12,0,0.5)
h2 = TH1D("h2","",12,0,0.5)

x1 = np.array([])
for line in file1:
    val = line.split()
    x1 = np.append(x1,float(val[0]))
    h1.Fill(float(val[0]))

x2 = np.array([])
for line in file2:
    val = line.split()
    x2 = np.append(x2,float(val[0]))
    h2.Fill(float(val[0]))

h1.SetLineColor(kRed)    
h1.Draw("E")

h2.Draw("ESAME")


# test del chi2
print('Test Chi2')      #Se aumento troppo il numero di bin il test del chi2 perde di validita' perche' 
print(h1.Chi2Test(h2))  #potrei avere troppi pochi ingressi in certi bin
print(h2.Chi2Test(h1))

# test unbinned KS 2 campioni
print('Test KS2')
t_ks, p_ks =stats.ks_2samp(x1,x2)
print(p_ks)

# test unbinned KS 1 pdf
test = stats.expon(loc=0,scale=0.1)  #expon mi gnere una esponenziale
t_ks1,p_ks1 = stats.kstest(x1,test.cdf) #il test di kolmogorov richiede una CDF
print('Test KS1 dat1')
print(p_ks1)
t_ks2,p_ks2 = stats.kstest(x2,test.cdf)
print('Test KS1 dat2')
print(p_ks2)

# test su esponenziale ignoto (con fit)
f = TF1("exp","[0]/[1]*exp(-x/[1])",0,0.5);
f.SetParameter(1,1)

h1.Fit('exp')
print('p-value=',f.GetProb())   #il metodo GetProb() resituisce il p-value

h2.Fit('exp')
print('p-value=',f.GetProb())


gApplication.Run(True)
