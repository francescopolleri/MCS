
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

using namespace std;

Vector fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){
  //STEP 2 definizione forza interna
  return Vector(0,0,0);
}

Vector fExternal(unsigned int i, double t, vector<MatPoint> p){
  //STEP 2 definizione forza esterna
  return (0,0,-9.81*p[i].Mass());
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

  ode.SetMatPoint(MatPoint(10,0,Vector(0,0,0),Vector(0,0,-15)));
  
  // STEP 1 creazione dell'oggetto della classe OdeSolver
  //   - creazione oggetto OdeSolver vuoto, assegnazione con il metodo Punto
  //   - creazione di vector<MatPoint> e poi creazione di OdelSover

  // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)
  ode.fInternal = fInternal;
  ode.fExternal = fExternal;
  double t=0.1;
  ode.Step(t);

  //Creazione dei grafici delle traiettorie
  vector<TGraph> gr(ode.N());
  TCanvas c("c","",10,10,500,500);
  c.cd();
  double size=100; // numero unita' astronimiche
  gPad->DrawFrame(-size,-size,size,size);
  int color[11]={kViolet+1,kOrange+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2,kGray};

  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0,0,ode.GetMatPoint(i).R().Z());
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
      gr[i].SetPoint(gr[i].GetN(),ode.T(),ode.GetMatPoint(i).R().Z());
    }
    //cout<<ode.GetMatPoint(0).R().Z();
  

  gPad->Modified(); gPad->Update();
 }
  app.Run(true);

  return 0;
  
}
