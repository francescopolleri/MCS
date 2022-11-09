from ROOT import *
import math
import time

rnd=TRandom3()
rnd.SetSeed(int(time.time()))

ntot=100000
nacc1=0.0
nacc2=0.0
nacc3=0.0
p1=0.3
p2=0.2

for i in range(0,ntot):
    xx=rnd.Rndm()
    if xx<p1:
        nacc1=nacc1+1
    elif xx>p1 and xx<p1+p2:
        nacc2=nacc2+1
    elif xx>p1+p2:
        nacc3=nacc3+1

print(nacc1/ntot)
print(nacc2/ntot)    
print(nacc3/ntot)