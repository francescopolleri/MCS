import math 
import numpy as np
import matplotlib.pyplot as plt
from ROOT import *

alpha = math.pi/3
lambda1=579.1
lambda2=404.7
th0=1.5701
th1=2.6958
th2=2.7904
delta_th     = 0.0005
eth=delta_th/math.sqrt(3)

def computeAB(th0,th1,th2):
    B = (((lambda1*lambda2)**2)/((lambda1**2-lambda2**2)*math.sin(alpha/2)))*(math.sin((th2-th0+alpha)/2)-math.sin((th1-th0+alpha)/2))
    A = math.sin((th1-th0+alpha)/2)/(math.sin(alpha/2))-B/(lambda1**2)
    return A,B

def computeN1N2(A,B):
    return A+B/(lambda1**2),A+B/(lambda2**2)

def computeDT1DT2(A,B):
    dt1=2*math.asin((A+B/lambda1**2)*math.sin(alpha/2))-alpha
    dt2=2*math.asin((A+B/lambda2**2)*math.sin(alpha/2))-alpha
    return dt1,dt2

#CALCOLO ERRORI CON METODO VARIAZIONI

def errAB_pos(th0,th1,th2,eth):

    fda,fdb=computeAB(th0,th1,th2)
    fs0a,fs0b=computeAB(th0+eth,th1,th2)
    
    fs1a,fs1b=computeAB(th0,th1+eth,th2)
    
    fs2a,fs2b=computeAB(th0,th1,th2+eth)
    
    der0a=(fs0a-fda)
    der1a=(fs1a-fda)
    der2a=(fs2a-fda)
    
    der0b=(fs0b-fdb)
    der1b=(fs1b-fdb)
    der2b=(fs2b-fdb)
    
    eA = math.sqrt(der0a**2 + der1a**2+ der2a**2)
    eB = math.sqrt(der0b**2 + der1b**2+ der2b**2)

    return eA,eB

def errAB_neg(th0,th1,th2,eth):

    fda,fdb=computeAB(th0,th1,th2)
    fs0a,fs0b=computeAB(th0-eth,th1,th2)
    
    fs1a,fs1b=computeAB(th0,th1-eth,th2)
    
    fs2a,fs2b=computeAB(th0,th1,th2-eth)
    
    der0a=(fs0a-fda)
    der1a=(fs1a-fda)
    der2a=(fs2a-fda)
    
    der0b=(fs0b-fdb)
    der1b=(fs1b-fdb)
    der2b=(fs2b-fdb)
    
    eA = math.sqrt(der0a**2 + der1a**2 + der2a**2)
    eB = math.sqrt(der0b*der0b + der1b*der1b + der2b*der2b)

    return eA,eB

AB=computeAB(th0,th1,th2)
print('AB',AB)

eABp=errAB_pos(th0,th1,th2,eth)
print('errAB+',eABp)

eABm=errAB_neg(th0,th1,th2,eth)
print('errAB-',eABm)

#CALCOLO ERRORI CON METODO MONTECARLO (DISTRIBUZIONE GAUSSIANA)

rnd=TRandom3()
rnd.SetSeed(123456789)

N=10000
sig=eth

#hA=TH1D("hA","",100,0,0)
#hB=TH1D("hB","",100,0,0)
H=TH2D("H","",100,0,0,100,0,0)

for i in range(0,N):
    theta0=rnd.Gaus(th0,sig)
    theta1=rnd.Gaus(th1,sig)
    theta2=rnd.Gaus(th2,sig)
    
    a,b=computeAB(theta0,theta1,theta2)

    H.Fill(a,b)

hA=H.ProjectionX()
hB=H.ProjectionY()

meanA=hA.GetMean()
sigA=hA.GetStdDev()
meanB=hB.GetMean()
sigB=hB.GetStdDev()

rho=H.GetCorrelationFactor()

c3=TCanvas("c3","",600,600)
c3.Divide(2,2)
c3.cd(1)
hA.SetFillColor(4)
hA.Draw()
c3.cd(4)
hB.SetFillColor(4)
hB.Draw('hbar')
c3.cd(3)
H.Draw('COL')

print('A = ',meanA,'+-',sigA)
print('B = ',meanB,'+-',sigB)
print('rho_AB = ',H.GetCorrelationFactor())

#CALCOLO ERRORI CON METODO MONTECARLO (DISTRIBUZIONE UNIFORME)

Nev=100000

G=TH2D("G","",100,0.,0.,100,0.,0.)
for i in range (0,Nev):
    Th0=2*delta_th*rnd.Rndm()+th0-delta_th
    Th1=2*delta_th*rnd.Rndm()+th1-delta_th
    Th2=2*delta_th*rnd.Rndm()+th2-delta_th
    
    A,B=computeAB(Th0,Th1,Th2)
    G.Fill(A,B)

G_A=G.ProjectionX()
G_B=G.ProjectionY()

meanA=G_A.GetMean()
sigA=G_A.GetStdDev()
meanB=G_B.GetMean()
sigB=G_B.GetStdDev()
rho=G.GetCorrelationFactor()

print('A = ',meanA,'+-',sigA)
print('B = ',meanB,'+-',sigB)
print('rho_AB = ',rho)

c4=TCanvas("c4","",600,600)
c4.Divide(2,2)
c4.cd(3)
G.Draw("COL")
c4.cd(1)
G_A.SetFillColor(4)
G_A.Draw()
c4.cd(4)
G_B.SetFillColor(4)
G_B.Draw('hbar')

K=TH2D("K","",100,0,0,100,0,0)

for i in range(0,N):
    a=rnd.Gaus(meanA,sigA)
    b=rnd.Gaus(meanB,sigB)
    
    n1,n2=computeN1N2(a,b)
    
    K.Fill(n1,n2)
    
can1=TCanvas("can1","",600,600)

can1.Draw()
can1.cd()
K.Draw("COL")
print(K.GetCorrelationFactor())

J=TH2D("J","",100,0,0,100,0,0)

for i in range(0,N):
    a=rnd.Gaus(meanA,sigA)
    b=rnd.Gaus(meanB,sigB)
    
    DT1,DT2=computeDT1DT2(a,b)
    
    J.Fill(DT1,DT2)
    
can2=TCanvas("can2","",600,600)
can2.Draw()
can2.cd()
J.Draw("COL")
print(J.GetCorrelationFactor())

gApplication.Run(True)