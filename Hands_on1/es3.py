from ROOT import *
import math as m

'''
CALCOLO VOLUME USANDO METODO DI REIEZIONE
'''
rnd=TRandom3()

rnd.SetSeed(123456789)
R=1
n=10000
nsph=0.
ni=0.
r=0
for i in range (0,n):
    x=2*R*rnd.Rndm()-R
    y=2*R*rnd.Rndm()-R
    z=2*R*rnd.Rndm()-R
    if x*x+y*y+z*z<R*R:
        nsph=nsph+1
        if x**2+y**2>(R**2/4):
            ni=ni+1

p=nsph/n
ep=m.sqrt(p*(1-p)/n)

p1=ni/n
ep1=m.sqrt(p1*(1-p1)/n)

print('Volume sfera (MC)=',p*(2*R)**3,'+/-',ep*(2*R)**3) #ho preso come contenitore della sfera un cubo di lato 2R 
print('Volume sfera=',4/3*R**3*m.pi)
print('Volume sfera bucata (MC)',p1*(2*R)**3,'+/-',ep1*(2*R)**3)
