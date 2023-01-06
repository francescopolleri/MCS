import numpy as np
import matplotlib.pyplot as plt

def RK4(f,x,y,z,t,dt):
    
    kx1=dt*f(x,y,z,t)[0]
    ky1=dt*f(x,y,z,t)[1]
    kz1=dt*f(x,y,z,t)[2]
    
    kx2=dt*f(x+kx1/2,y+ky1/2,z+kz1/2,t+dt/2)[0]
    ky2=dt*f(x+kx1/2,y+ky1/2,z+kz1/2,t+dt/2)[1]
    kz2=dt*f(x+kx1/2,y+ky1/2,z+kz1/2,t+dt/2)[2]

    kx3=dt*f(x+kx2/2,y+ky2/2,z+kz2/2,t+dt/2)[0]
    ky3=dt*f(x+kx2/2,y+ky2/2,z+kz2/2,t+dt/2)[1]
    kz3=dt*f(x+kx2/2,y+ky2/2,z+kz2/2,t+dt/2)[2]

    kx4=dt*f(x+kx3,y+ky3,z+kz3,t+dt)[0]
    ky4=dt*f(x+kx3,y+ky3,z+kz3,t+dt)[1]
    kz4=dt*f(x+kx3,y+ky3,z+kz3,t+dt)[2]

    x = x + kx1/6 + kx2/3 + kx3/3 + kx4/6
    y = y + ky1/6 + ky2/3 + ky3/3 + ky4/6
    z = z + kz1/6 + kz2/3 + kz3/3 + kz4/6
    '''
    k1 = dt * f(x,y,z,t)
    k2 = dt * f(x + k1[0]/2, y + k1[1]/2, z + k1[2]/2, t + dt/2)
    k3 = dt * f(x + k2[0]/2, y + k2[1]/2, z + k2[2]/2, t + dt/2)
    k4 = dt * f(x + k3[0], y + k3[1], z + k3[2], t + dt)

    x = x+ k1[0]/6 + k2[0]/3 + k3[0]/3 + k4[0]/6
    y = y+ k1[1]/6 + k2[1]/3 + k3[1]/3 + k4[1]/6
    z = z+ k1[2]/6 + k2[2]/3 + k3[2]/3 + k4[2]/6
    '''
    return x, y, z

def fun(x,y,z,t):
    sigma=10
    beta=8./3
    rho=28
    vx=sigma*(y-x)
    vy=rho*x-x*z-y
    vz=x*y-beta*z
    return vx, vy ,vz
    #return np.array([vx, vy, vz])

n=1000000
x=np.ones(n)
y=np.ones(n)
z=np.ones(n)
t=np.zeros(n)
dt=0.0001

for i in range (0,n-1):
    x[i+1],y[i+1],z[i+1]=RK4(fun,x[i],y[i],z[i],t[i],dt)

plt.plot(x,y)
plt.show()







