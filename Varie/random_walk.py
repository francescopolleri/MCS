from ROOT import *
import math as m

rnd=TRandom3()
rnd.SetSeed(123456789)

d=m.sqrt(3)
f=0.5
N=100000

for i in range (0,N):
    dx=d*rnd.Rndm()
    sx=-d*rnd.Rndm()

    
