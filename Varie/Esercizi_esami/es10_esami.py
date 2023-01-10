import numpy as np
import matplotlib.pyplot as plt

def Gravity(x,y):
    MT=6e24
    G=6.67e-11
    Gx=-G*MT*x/((x**2+y**2)**(3/2))
    Gy=-G*MT*y/((x**2+y**2)**(3/2))
    return Gx, Gy

def ELR(vx,vy,x,y,dt):
    x=x+vx*dt
    y=y+vy*dt
    vx=vx+dt*Gravity(x,y)[0]
    vy=vy+dt*Gravity(x,y)[1]
    return x, y, vx, vy

def RK4(vx,vy,x,y,dt):
    kx1=dt*vx
    ky1=dt*vy
    wx1=dt*Gravity(x,y)[0]
    wy1=dt*Gravity(x,y)[1]

    kx2=dt*(vx+wx1/2)
    ky2=dt*(vy+wy1/2)
    wx2=dt*Gravity(x+kx1/2,y+ky1/2)[0]
    wy2=dt*Gravity(x+kx1/2,y+ky1/2)[1]

    kx3=dt*(vx+wx2/2)
    ky3=dt*(vy+wy2/2)
    wx3=dt*Gravity(x+kx2/2,y+ky2/2)[0]
    wy3=dt*Gravity(x+kx2/2,y+ky2/2)[1]
    
    kx4=dt*(vx+kx3)
    ky4=dt*(vy+ky3)
    wx4=dt*Gravity(x+kx3,y+ky3)[0]
    wy4=dt*Gravity(x+kx3,y+ky3)[1]

    x = x + kx1/6 + kx2/3 +kx3/3 +kx4/6
    y = y + ky1/6 + ky2/3 +ky3/3 + ky4/6
    vx = vx + wx1/6 + wx2/3 + wx3/3 + wx4/6
    vy = vy + wy1/6 + wy2/3 + wy3/3 + wy4/6
    return x, y, vx , vy

N=10000
dt=0.01
x=np.zeros(N)
y=np.zeros(N)
vx=np.zeros(N)
vy=np.zeros(N)
x[0]=4e5
vy[0]=3e4

for i in range (0,N-1):
    x[i+1]=ELR(vx[i],vy[i],x[i],y[i],0.01)[0]
    y[i+1]=ELR(vx[i],vy[i],x[i],y[i],0.01)[1]
    vx[i+1]=ELR(vx[i],vy[i],x[i],y[i],0.01)[2]
    vy[i+1]=ELR(vx[i],vy[i],x[i],y[i],0.01)[3]

''' VERLET VELOCITY
for i in range(0,N-1):
    x[i+1]=x[i]+dt*vx[i]+1/2*dt**2*Gravity(x[i],y[i])[0]
    y[i+1]=y[i]+dt*vy[i]+1/2*dt**2*Gravity(x[i],y[i])[1]
    vx[i+1]=vx[i]+1/2*dt*(Gravity(x[i+1],y[i+1])[0]+Gravity(x[i],y[i])[0])
    vy[i+1]=vy[i]+1/2*dt*(Gravity(x[i+1],y[i+1])[1]+Gravity(x[i],y[i])[1])
'''

plt.plot(x,y)
plt.show()