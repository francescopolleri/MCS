import numpy as np 
import matplotlib.pyplot as plt
import math

'''
e0=8.854e-12   #EQUAZIONE DI LAPLACE
e_r=0.0001
e_a=e_r
q=1e6

N=100
x=np.linspace (-5,5,N)
y=np.linspace(-5,5,N)
delta=x[1]-x[0]

V=np.zeros((N,N))
rho=np.zeros((N,N))
rho[25,25]=-q
rho[25,75]=q
rho[75,25]=q
rho[75,75]=-q

V[0,0:N-1]=0
V[N-1,0:N-1]=0
V[0:N-1,0]=0
V[0:N-1,N-1]=0
Vold=np.zeros((N,N))

K=1000
w=1.8
for k in range (0,K):
    Vold[:,:]=V[:,:]
    for i in range (1,N-1):
        for j in range (1,N-1):
            add=1/4*( Vold[i+1,j] + V[i-1,j] + Vold[i,j+1] + V[i,j-1] ) - Vold[i,j] + delta**2/(4*e0)*rho[i,j]
            V[i,j]=Vold[i,j]+w*add
    dV=np.abs(Vold-V)
    max_dV=dV.max()
    max_V=V.max()
    if(max_dV<e_r*max_V+e_a):
       break

print (k)

x_mesh,y_mesh=np.meshgrid(x,y)
plt.contourf(x_mesh,y_mesh,V,levels=50,cmap='bwr')
plt.colorbar()

Ey,Ex=np.gradient(V)
plt.streamplot(x_mesh,y_mesh,Ex,Ey,color='k')
plt.show()
'''

'''
N=100                  #EQUAZIONE DEL CALORE
x=np.linspace(0,10,N)
eta = 0.2; L = 0.5; kappa = 5
dx=(x[1]-x[0])/10
dt = (eta*dx**2)/kappa

T0=20; DT=100
T=np.ones(N)*T0

T[0:1]=T0+DT
t=0
t_end=10
dt=0.01
time=np.array([])
T_n=np.array([])
while (t<t_end):
    for i in range (0,N-1):
        T[N-1]=T0
        T[0]=T[0]+eta*(T[1]-T[0])
        T[i]=T[i]+eta*( T[i+1] + T[i-1] -2*T[i] )
        time=np.append(time,t)
        T_n=np.append(T_n,T[10])
    t=t+dt

plt.figure(1)
plt.plot(x,T)
plt.xlabel('x')
plt.ylabel('T')

plt.figure(2)
plt.plot(time,T_n)
plt.xlabel('time')
plt.ylabel('T(N=10)')
plt.show()
'''


v=1; L=10        #EQUAZIONE ONDE
N=100
x=np.linspace(0,L,N)
dx=x[2]-x[1]
u=2

dt=dx/u
t=0;t_end=50

U=np.zeros(N)
U=np.sin(math.pi*x/L)
U[0]=0
U[N-1]=0

U1=np.zeros_like(U)
U2=np.zeros_like(U)
U1[:]=U[:]

U[1:N-1]=U[1:N-1]+(1/2)*(v/u)**2*(U[2:N]+U[0:N-2]-2*U[1:N-1])

time=np.array([])
y=np.array([])

while(t<t_end):
    U2[:]=U[:]
    U[1:N-1]=2*U[1:N-1]-U1[1:N-1]+(v/u)**2*(U[2:N]+U[0:N-2]-2*U[1:N-1])
    U1[:]=U2[:]

    for i in range (0,N):
        time=np.append(time,t)
        y=np.append(y,U[50])

    t=t+dt

plt.plot(time,y)
plt.show()








