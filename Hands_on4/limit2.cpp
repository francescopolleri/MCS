#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TH1D.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TTree.h>

using namespace std;

int main(){

  double nbkg = 44.7; //bkg sta per background

  TApplication app("app",NULL,NULL);
  TTree t;
  t.ReadFile("dati_highstat.dat","t/D");

  TH1D *h = new TH1D("h","",80,0,40);
  TH1D *hreg = new TH1D("hreg","",4,14,16);

  ifstream ifile("dati_highstat.dat");
  
  double mass;
  int    nobs=0;
  while (ifile >> mass){
    //calcolare nobs
    h->Fill(mass);
    if (mass>14 && mass<16){
      hreg->Fill(mass);
      nobs++;
    }
  }

  double p=0;
  for(int i=0;i<nobs;i++){
    p += TMath::PoissonI(i,nbkg);
  }

  double Z=TMath::NormQuantile(p);
  cout<<"p-value = "<<1-p<<endl;
  cout<<"# sigma = "<<Z<<endl;
  
  cout<<"nobs="<<nobs<<endl;
  
  h->Draw();
  hreg->Draw("SAME");
  hreg->SetFillColor(2);

  //calcolare Upper Limit

  for (int ns=0;ns<1000;ns++){
      double prob=0;
      for(int j=0;j<=nobs;j++){
	    prob+= TMath::PoissonI(j,ns+nbkg);
      }
      if(prob<0.05){   //Per avere UL devo mettere prob<0.05  //Per avere LL devo mettere 1-prob>0.05
      cout<<"UL (95% CL)= "<<ns<<endl;  
      break;
      }
  }

  //calcolare Lower Limit
  for (int ns=0;ns<1000;ns++){
      double prob=0;
      for(int j=0;j<=nobs;j++){
	    prob+= TMath::PoissonI(j,ns+nbkg);
      }
      if(1-prob>0.05){   //Per avere UL devo mettere prob<0.05  //Per avere LL devo mettere 1-prob>0.05
      cout<<"LL (95% CL)= "<<ns<<endl;  
      break;
      }
  }
  app.Run(true);

}
