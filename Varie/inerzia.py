from ROOT import *
import math as m

rnd=TRandom3()
rnd.SetSeed(123456789)

rho=1.3
R=6
r=1
n=10000000

nsph=0.
d2=0.
n1=0.
s2=0.
g2=0.
for i in range (0,n):
    x=2*R*rnd.Rndm()-R
    y=2*R*rnd.Rndm()-R
    z=2*R*rnd.Rndm()-R
    x1=2*R*rnd.Rndm()-R-2
    y1=2*R*rnd.Rndm()-R-2
    z1=2*R*rnd.Rndm()-R-2
    g2=g2+abs(x)+abs(y)
    if x*x+y*y+z*z<R*R:
        nsph=nsph+1
        d2=d2+(x**2+y**2)
    if x1*x1+y1*y1+z1*z1<r**2:
        n1=n1+1
        s2=s2+((2-x1)**2+(2-y1)**2)
        #s2=s2+(x1**2+y1**2)+


p=nsph/n
p1=n1/n
ep=m.sqrt(p*(1-p)/n)
ep1=m.sqrt(p1*(1-p1)/n)
V=p*(2*R)**3
V1=p1*(2*R)**3
Isfera=rho*V*d2/nsph
Isfera1=rho*V1*s2/n1
H=rho

print('Volume sfera (MC)=',V,'+/-',ep*(2*R)**3)
print('Volume sfera=',4/3*R**3*m.pi)
print('Volume sfera con buco (MC)=',V-V1,'+/-',(ep+ep1)*(2*R)**3)
print('Volume sfera con buco=',4/3*m.pi*(R**3-r**3))

print('I_sfera (MC)=',Isfera,'+/-',ep*(rho/6)*(2*R)**5)
print('I_sfera=',8*rho*R**5*m.pi/15)
print('I sfera con buco (MC)=',Isfera-Isfera1,'+/-',(ep+ep1)*(rho/6)*(2*R)**5)
print('I sfera con buco=',8*rho*R**5*m.pi/15-8*rho*r**5*m.pi/15-rho*(4/3)*m.pi*r**3*4)

