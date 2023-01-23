import numpy as np
import matplotlib.pyplot as plt
import ROOT 
import scipy.stats as sts

def find_p(bkg,obs):
    p=0
    for j in range (0,int(obs)):
        p += ROOT.TMath.PoissonI(j,bkg)
    return 1-p

Nev=10000
_lambda=0.01
mu=150
sig=10

f=0.98

Nbins=100

rnd=ROOT.TRandom3()
rnd.SetSeed(123456789)

h=ROOT.TH1D("h","",Nbins,0,600)
h_gaus=ROOT.TH1D("h_gaus","",9,125,175)
h_exp=ROOT.TH1D("h_exp","",100,0,600)

n_bkg=0
n_obs=0

for i in range(0,Nev):
    p=rnd.Rndm()
    if(p<f):
        x=-1/_lambda*np.log(1-rnd.Rndm())
        h_exp.Fill(x)
        if(x>125 and x<175):
            n_bkg=n_bkg+1
    else:
        x=rnd.Gaus(mu,sig)
        if(x>125 and x<175):
            h_gaus.Fill(x)
    h.Fill(x)
    if(x>125 and x<175):
        n_obs=n_obs+1

area=h.GetEntries()*h.GetBinWidth(1)

f_exp=ROOT.TF1("f_exp","[0]*(1-[1])*[2]*exp(-x*[2])")
f_exp.SetParameters(area,f,_lambda)
h_exp.Fit("f_exp","0 L")
Int=np.array([])
N_bkg=np.array([])
for i in range (1,Nbins):
    Int=np.append(Int,f_exp.Integral(h_exp.GetBinLowEdge(i),h_exp.GetBinLowEdge(i)+h_exp.GetBinWidth(i)))
N_bkg=Int/h_exp.GetBinWidth(1)

N_obs=np.array([])
for i in range(1,Nbins):
    N_obs=np.append(N_obs,h.GetBinContent(i))

c1=ROOT.TCanvas("c1","",600,600)
c1.Divide(1,2)
c1.cd(1)
f=ROOT.TF1("f","[0]*( (1-[1])*[2]*exp(-[2]*x) + [1]*TMath::Gaus(x,[3],[4],1) )",0,600)
f.SetParameters(area,0.2,0.01,150,10)
h.Draw(); h.SetTitle(" ;DATA;# ENTRIES")
h_gaus.SetFillColor(3)
h_exp.SetFillColor(41)
h_exp.Draw("SAME")
h_gaus.Draw("SAME")
f.Draw("SAME")
h.Fit("f","0 L")

c1.cd(2)
g=ROOT.TGraph()
for i in range (0,Nbins-1):
    g.SetPoint(i,h.GetBinCenter(i+1),find_p(N_bkg[i],N_obs[i]))

g.SetTitle(" ;DATA;p_value")
ROOT.gPad.SetLogy()
g.Draw("AL")

l1=ROOT.TLine(0,1-ROOT.TMath.Freq(1),600,1-ROOT.TMath.Freq(1))
l2=ROOT.TLine(0,1-ROOT.TMath.Freq(2),600,1-ROOT.TMath.Freq(2))
l3=ROOT.TLine(0,1-ROOT.TMath.Freq(3),600,1-ROOT.TMath.Freq(3))
l4=ROOT.TLine(0,1-ROOT.TMath.Freq(4),600,1-ROOT.TMath.Freq(4))
l5=ROOT.TLine(0,1-ROOT.TMath.Freq(5),600,1-ROOT.TMath.Freq(5))
l1.SetLineColor(2); l1.SetLineStyle(7)
l2.SetLineColor(2); l2.SetLineStyle(7)
l3.SetLineColor(2); l3.SetLineStyle(7)
l4.SetLineColor(2); l4.SetLineStyle(7)
l5.SetLineColor(2); l5.SetLineStyle(7)
l1.Draw("SAME")
l2.Draw("SAME")
l3.Draw("SAME")
l4.Draw("SAME")
l5.Draw("SAME")

latex=ROOT.TLatex()
latex.SetTextAlign(12)
latex.SetTextSize(0.05)
latex.SetTextColor(2)
latex.DrawLatex(620,1-ROOT.TMath.Freq(1),"#sigma")
latex.DrawLatex(620,1-ROOT.TMath.Freq(2),"2#sigma")
latex.DrawLatex(620,1-ROOT.TMath.Freq(3),"3#sigma")
latex.DrawLatex(620,1-ROOT.TMath.Freq(4),"4#sigma")
latex.DrawLatex(620,1-ROOT.TMath.Freq(5),"5#sigma")


ROOT.gApplication.Run(True)