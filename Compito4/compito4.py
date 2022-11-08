import matplotlib.pyplot as plt
import numpy as np
import math
from scipy.integrate import trapz

def V(xi):
    return xi**2

def b(eps,xi):
    return (h**2/12)*(2*eps-xi**2)

def numerov(n1,n2,eps):
    psi = np.array(xi)*0  
    j   = np.sign(n2-n1)
    psi[n1]=0
    psi[n1+j]=1.0e-6

    for i in range(n1+2*j,n2+j,j):
       psi[i] = ( 2*psi[i-j]*(1-5*b(eps,xi[i-j])) - psi[i-2*j]*(1+b(eps,xi[i-2*j])))/(1+b(eps,xi[i]))
    return psi

def evalDerivative(eps):
    global psir,psil
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)

    psir = (psil[nmatch]/psir[nmatch])*psir
 
    der_r = (psir[nmatch+1]-psir[nmatch-1])/(2*h)
    der_l = (psil[nmatch+1]-psil[nmatch-1])/(2*h)
  
    diff = der_l-der_r

    return diff

def findE(emin,emax,tol):
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin)*evalDerivative(emed)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;

''' 
  Codice principale: l'esecuzione dello script parte da qui
'''

#PRIMA PARTE

n       = 14000
nmatch  = 10000
xi      = np.linspace(-7.,7,n)
h       = xi[1]-xi[0]

Emin=0
Emax=5
delta_e=0.09
energy=delta_e
Epsilon=[]


while (energy<Emax):
    if(evalDerivative(energy)*evalDerivative(energy+delta_e)<0):
        Epsilon.append(findE(energy,energy+delta_e,0.0001))
        psiTot=np.empty(n)
        for i in range(0,nmatch+1):
            psiTot[i]=psil[i]

        for i in range(nmatch+1,n):
            psiTot[i]=psir[i]

        plt.plot(xi,psiTot)
        plt.xlabel('xi')
        plt.ylabel('psi(xi)')
        plt.title('Funzione d onda non normalizzata')
        plt.show()
    energy+=delta_e
    
print('Per valori di Epsilon compresi tra 0 e 5 quelli che corrispondono a stati fisici sono:')
print(Epsilon[0])
print(Epsilon[1])
print(Epsilon[2])
print(Epsilon[3])
print(Epsilon[4])


#SECONDA PARTE

epsilon=[0.5,1.5,2.5]

f0=numerov(0,n-1,epsilon[0])
f1=numerov(0,n-1,epsilon[1])
f2=numerov(0,n-1,epsilon[2])

g0=abs(f0)**2
g1=abs(f1)**2
g2=abs(f2)**2

I0=trapz(abs(f0)**2,xi)
I1=trapz(abs(f1)**2,xi)
I2=trapz(abs(f2)**2,xi)

f0N=f0/math.sqrt(I0)
f1N=f1/math.sqrt(I1)
f2N=f2/math.sqrt(I2)

g0N=g0/I0
g1N=g1/I1
g2N=g2/I2

fig,((ax0,ax1),(ax2,ax3),(ax4,ax5))=plt.subplots(3,2)
plt.subplots_adjust(bottom=0.1, right=1.8, top=2.5)
ax0.plot(xi,f0N,color='b')
ax0.set_title('psi(xi);Eps=0.5')
ax1.plot(xi,g0N,color='b')
ax1.set_title('|psi(xi)^2|;Eps=0.5')
ax2.plot(xi,f1N,color='g')
ax2.set_title('psi(xi);Eps=1.5')
ax3.plot(xi,g1N,color='g')
ax3.set_title('|psi(xi)^2|;Eps=1.5')
ax4.plot(xi,f2N,color='r')
ax4.set_title('psi(xi);Eps=2.5')
ax5.plot(xi,g2N,color='r')
ax5.set_title('|psi(xi)^2|;Eps=2.5')

H0=trapz(g0N,xi)
H1=trapz(g1N,xi)
H2=trapz(g2N,xi)

print(H0,H1,H2)



