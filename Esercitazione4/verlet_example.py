import matplotlib.pyplot as plt
import numpy as np
import math

def a(sigma,f,x):
    return -f/(sigma**2)+x*x/(sigma**4)*f;

def soleq(n1,n2,sigma):
    #creo f (copia d x)
    f = np.array(x)
    j = np.sign(n2-n1)
    f[n1] = 0
    f[n1+j] = 1e-6
    for i in range(n1+2*j,n2+j,j):
        #f(n+1) = 2*f(n) - f(n-1) + h*h*a(n)
        f[i]   = 2*f[i-j] - f[i-2*j] + h*h*a(sigma,f[i-j],x[i-j])
    return f

# main code
n      = 10000
x      = np.linspace(-5.,5,n)
h      = x[1]-x[0]
f      = soleq(9999,0,1)

plt.plot(x,f,'r.')
plt.show()
