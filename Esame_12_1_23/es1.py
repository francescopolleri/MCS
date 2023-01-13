import numpy as np
import matplotlib.pyplot as plt

z0=0.01
h=0.1
g=9.81
b=0.25

def acc(vz,z):
    return -1/z*(vz**2 + b*vz + g*(z-h))

N=1000
dt=0.01
z=np.zeros(N)
z[0]=z0
vz=np.zeros(N)
t=np.zeros(N)

#il valore asintotico e' h

a=np.array([])
T=np.array([])
Z=np.array([])
V=np.array([])

for i in range (0,N-1):
    k1=dt*vz[i]
    w1=dt*acc(vz[i],z[i])

    k2=dt*(vz[i]+w1/2)
    w2=dt*acc(vz[i]+w1/2,z[i]+k1/2)

    z[i+1]=z[i]+k2
    vz[i+1]=vz[i]+w2
    t[i+1]=t[i]+dt
    a=np.append(a,acc(vz[i+1],z[i+1]))
    T=np.append(T,t[i+1])
    Z=np.append(Z,z[i+1])
    V=np.append(V,vz[i+1])
    if(np.abs(z[i+1]-h)<0.001*h):  #ho messo una percentuale dello 0.1% per fare in modo di disegnare piu' punti
        break



fig, (ax1,ax2,ax3)=plt.subplots(3)
ax1.plot(T,Z)
ax1.set_title('z(t) vs t')
ax2.plot(T,V)
ax3.plot(T,a)



plt.show()



    
