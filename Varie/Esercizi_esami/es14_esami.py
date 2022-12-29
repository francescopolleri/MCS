import numpy as np
import ROOT 

nobs=30
natt=15
p=0.05

for ns in range (0,10000):
    prob=0
    for i in range (0,nobs):
        prob += ROOT.TMath.PoissonI(i,natt+ns)
    if(prob<p):
        print('UL at 95% C.L = ',ns)
        break

for ns in range (0,10000):
    prob=0
    for i in range (0,nobs):
        prob += ROOT.TMath.PoissonI(i,natt+ns)
    if(1-prob>p):
        print('LL at 95% C.L = ',ns)
        break

if(ns<nobs):
    print('Ipotesi nulla rigettata!')