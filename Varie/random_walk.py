import numpy as np 
import matplotlib.pyplot as plt
from ROOT import *

rnd=TRandom3()
rnd.SetSeed(1324758609)

Nev=1000

N_urti=20
x=0; d=0; x2=0
s=np.zeros([])
s2=np.zeros([])
n_urti=np.zeros([])
for j in range (0,N_urti):
    n_urti=np.append(n_urti,j)
    for i in range (0,Nev):
        d=2*np.sqrt(3)*rnd.Rndm()-np.sqrt(3)
    x += d
    x2 += d**2
    s=np.append(s,x)
    s2=np.append(s2,x2)
plt.plot(n_urti,s2,"-g",label="#Urti=20")

N_urti=40
x=0; d=0; x2=0
s=np.zeros([])
s2=np.zeros([])
n_urti=np.zeros([])
for j in range (0,N_urti):
    n_urti=np.append(n_urti,j)
    for i in range (0,Nev):
        d=2*np.sqrt(3)*rnd.Rndm()-np.sqrt(3)
    x += d
    x2 += d**2
    s=np.append(s,x)
    s2=np.append(s2,x2)
plt.plot(n_urti,s2,"-b",label="#Urti=40")

N_urti=60
x=0; d=0; x2=0
s=np.zeros([])
s2=np.zeros([])
n_urti=np.zeros([])
for j in range (0,N_urti):
    n_urti=np.append(n_urti,j)
    for i in range (0,Nev):
        d=2*np.sqrt(3)*rnd.Rndm()-np.sqrt(3)
    x += d
    x2 += d**2
    s=np.append(s,x)
    s2=np.append(s2,x2)
plt.plot(n_urti,s2,"-r",label="#Urti=60")


x=0
d=0
h1=TH1D("h","",15,0.,0.)  
N_particles=1000
N_step=100
for k in range (0,N_particles):
    x=0
    for j in range (0,N_step):
        for i in range (0,Nev):
            d=2*np.sqrt(3)*rnd.Rndm()-np.sqrt(3)
        x += d
    h1.Fill(x)

c1=TCanvas("c1","",400,400)
c1.Draw()
h1.Draw()

gApplication.Run(True)


    




    
