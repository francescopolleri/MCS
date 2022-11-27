
#include <cmath>
#include <fstream>
#include <vector>
#include<functional>
#include<iostream>

#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TLegend.h>
#include<TMath.h>


#include "OdeSolver.h"
#include "Vector.h"
#include "MatPoint.h"
#include "Electron.h"

using namespace std;

Vector fB(Vector r){
  double BMin      = 1.4e-5, BMax=7e-5;
  double BottleLen = 10.0;
  double rho       = sqrt(r.X()*r.X()+r.Y()*r.Y());
  double phi       = atan2(r.Y(),r.X());
  double Bz        = BMin+(BMax-BMin)*(1 + 1/2.*(TMath::Erf(r.Z()-BottleLen/2) - TMath::Erf(r.Z()+BottleLen/2)));
  double DerivBZ   = (BMax-BMin)/sqrt(M_PI)*(TMath::Exp(-pow(r.Z()-BottleLen/2,2))-TMath::Exp(-pow(r.Z()+BottleLen/2,2)));
  double Br        = -DerivBZ*rho/2;
  double Bx        = Br*cos(phi);
  double By        = Br*sin(phi);
  return Vector(Bx,By,Bz);
}

Vector fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){
  //STEP 2 definizione forza interna
  return Vector(0,0,0);
}

Vector fExternal(unsigned int i, double t, vector<MatPoint> p){
  //STEP 2 definizione forza esterna
  return (p[i].V().Cross(fB(p[i].R())))*p[i].Charge();
}


int main(){ 
  
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  string method_name;
  cout<<"What method do you want to use?"<<endl;
  cout<<"(Enter 'ELR' for Eulero,'RK2' for Runge-Kutta2,'RK4' for Runge-Kutta4 and 'VV' for Verltet velocity)"<<endl;
  cin>>method_name;

  OdeSolver ode;
  ode.SetMethod(method_name);

  Electron e;
  //double e=-1.6e-19;
  //double m=9.1e-31;
  ode.SetMatPoint(MatPoint(e,Vector(0,0,0),Vector(0,5e6,0.5e6)));
  

  // STEP 1 creazione dell'oggetto della classe OdeSolver
  //   - creazione oggetto OdeSolver vuoto, assegnazione con il metodo Punto
  //   - creazione di vector<MatPoint> e poi creazione di OdelSover

  // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)
  ode.fInternal = fInternal;
  ode.fExternal = fExternal;

  double t = 0.01*abs((2*e.Mass()*TMath::Pi())/(e.Charge()*fB(Vector(0,0,0)).Mod()));
  ode.Step(t);

  //Creazione dei grafici delle traiettorie
  vector<TGraph> gr(ode.N());
  TCanvas c("c","",10,10,500,500);
  c.cd();
  double size=10; // numero unita' astronimiche
  gPad->DrawFrame(-size,-size,size,size);
  int color[11]={kViolet+1,kOrange+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2,kGray};

  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0,ode.GetMatPoint(i).R().Z(),ode.GetMatPoint(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerSize(0.2); gr[i].SetLineColor(color[i]);
    gr[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();

  //app.Run(true);

  //Run del metodo numerico + grafico in tempo reale delle coordinate
  double S=1000*t;
  while (ode.T()<S){
    ode.Solve();
    for (unsigned int i=0;i<ode.N();i++){
      //STEP 4 riempimento del grafico gr[i] con le coordinate aggiornate dei pianeti
      gr[i].SetPoint(gr[i].GetN(),ode.GetMatPoint(i).R().Z(),ode.GetMatPoint(i).R().Y());
    }
    //cout<<ode.GetMatPoint(0).R().Z();
  

  gPad->Modified(); gPad->Update();
 }
  app.Run(true);

  return 0;
  
}
