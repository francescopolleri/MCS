'''
 Schema per lo sviluppo del metodo di Numerov 
'''
import matplotlib.pyplot as plt
import numpy as np
import math
from scipy.integrate import trapz

'''
 La proposta di implementazione e' divisa quattro step
 Step 1 (S1)
 Step 2 (S2)
 Step 3 (S3)
 Step 4 (S4)
 i comandi commentati (con # in prima colonna) indicano un comandi gia' pronti,
 utilizzabile quando le parti precedenti sono completate
'''

'''
  S1: definire il potenziale in funzione della variabile normalizzata xi
'''   
def V(xi,g):
    return xi**2+g*xi**4


'''
  S1: calcolo di b a partire dall'energia normalizzata eps, della coordinata
  normalizzata xi e dallo passo h (variabile globale)
'''
def b(eps,xi,g):
    return (h**2/12)*(2*eps-V(xi,g))


'''
  S1/S2: completare la funzione Numerov che riempe i valori di psi(xi) 
         dall'indice n1 all'indice n2 (entrambi compresi)
         Schema:
           - definisco indice j in modo che 1 se n2>n1, -1 se n2<n1 (vedi sign di numpy)
             in questo modo:
               se j =  1 indice i, i+j,i+2*j -> i, i+1, i+2
               se j = -1 indice i, i+j,i+2*j -> i, i-1, i-2
           - fornisco i primi due valori di psi
           - implemento Numerov (ciclo for)
'''
def numerov(n1,n2,eps,g):
    psi = np.array(xi)*0  # copio xi in psi e lo azzero
    j   = np.sign(n2-n1)
    psi[n1]=0
    psi[n1+j]=1.0e-6

    for i in range(n1+2*j,n2+j,j):
       psi[i] = ( 2*psi[i-j]*(1-5*b(eps,xi[i-j],g)) - psi[i-2*j]*(1+b(eps,xi[i-2*j],g)))/(1+b(eps,xi[i],g))
    return psi



'''
  S3: completare evalDerivative
     - per l'energia eps fornita dall'utente crea soluzione left e right
     - le normalizza a nmatch (si consiglia di normalizzare psir a psil)
     - calcola la differenza (diff) tra le derivate centrate (left e right) in match
'''
def evalDerivative(eps,g):
    global psir,psil,psiTot
    psil = numerov(0,nmatch+1,eps,g)
    psir = numerov(n-1,nmatch-1,eps,g)

    psir = (psil[nmatch]/psir[nmatch])*psir

   
    
    der_r = (psir[nmatch+1]-psir[nmatch-1])/(2*h)
    der_l = (psil[nmatch+1]-psil[nmatch-1])/(2*h)
  
    diff = der_l-der_r

    return diff



''' 
  Metodo di bisezione per trovare l'energia in cui la funzione evalDerivative
  e' nulla. Cioe' l'enegia per cui  la derivata sinistra e destra coincidono 
'''

def findE(emin,emax,g,tol):
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin,g)*evalDerivative(emed,g)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;
 
''' 
  Codice principale: l'esecuzione dello script parte da qui
'''
n       = 14000
nmatch  = 10000
xi      = np.linspace(-7.,7,n)
h       = xi[1]-xi[0]

'''
  S1: verifico Numerov chiamando la funzione da sinistra a destra
  e la disegno
'''
#epsilon = 0.5   # o altra energia di stato definito eps = (n+1/2)
#psi1=numerov(0,n-1,epsilon)
#plt.plot(xi,psi1)
#plt.show()

'''
  S2: come S1 ma verifico che funzioni anche da destra a sinistra
  e la disegno
'''
#epsilon = 0.5   # o altra energia di stato definito eps = (n+1/2)
#psi2=numerov(n-1,0,epsilon)
#plt.plot(xi,psi2)
#plt.show()


#fig,((ax1,ax2))=plt.subplots(1,2)
#ax1.plot(xi,psi1,color='b')
#ax2.plot(xi,psi2,color='r')

#plt.show()

'''
  S3:
   - commentare i punti precedenti (a parte le definizioni iniziali del Main code)
   - completare evalDerivative 
   - chiamare findE 
   - fare grafico delle due funzioni 
'''
e = findE(0.2,0.7,0.05,0.0001)
print "Energy ",2*e

psiTot=np.empty(n)
for i in range(0,nmatch+1):
        psiTot[i]=psil[i]

for i in range(nmatch+1,n):
        psiTot[i]=psir[i]

#plt.plot(xi,psir)
#plt.plot(xi,psil)
plt.plot(xi,psiTot)
plt.show()

'''
  S4:
   - copiare psr nella parte 'vuota' di psil di modo che psil rappresenti tutta psi(x)
     nell'intervallo dato o, alternativamente, copiarle entrambe in una nuova psi
   - disegnare la funzione d'onda trovata
'''
