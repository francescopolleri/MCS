
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


#include "OdeSolver.h"
#include "Vector.h"
#include "MatPoint.h"

using namespace std;

Vector fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){
  //STEP 2 definizione forza interna
  Vector F_int(p[i].Mass()*p[j].GravField(p[i].R()));
  return F_int;
}

Vector fExternal(unsigned int i, double t, vector<MatPoint> p){
  //STEP 2 definizione forza esterna
  Vector F_ext(0,0,0);
  return F_ext;
}

int main(){ 
  
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  string method_name1,method_name2;
  method_name1="VerletV";
  method_name2="RK2";

  //Lettura dei dati dal file
  vector<MatPoint> V;
  Particle p;
  Vector r;
  Vector v;
  double mass;
  double x,y,z,vx,vy,vz;
  ifstream f("fileInput");

  OdeSolver ode1;
  ode1.SetMethod(method_name1);
  OdeSolver ode2;
  ode2.SetMethod(method_name2);
  
  while (f >> mass >> vx >> x >> vy >> y >> vz >> z){
    MatPoint MP(mass,0,Vector(x,y,z),Vector(vx,vy,vz));
    ode1.SetMatPoint(MP);
  }

  while (f >> mass >> vx >> x >> vy >> y >> vz >> z){
    MatPoint MP(mass,0,Vector(x,y,z),Vector(vx,vy,vz));
    ode2.SetMatPoint(MP);
  }
  // STEP 1 creazione dell'oggetto della classe OdeSolver
  //   - creazione oggetto OdeSolver vuoto, assegnazione con il metodo Punto
  //   - creazione di vector<MatPoint> e poi creazione di OdelSover

  // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)
  ode1.fInternal = fInternal;
  ode1.fExternal = fExternal;
  ode1.Step(0.5);

  ode2.fInternal = fInternal;
  ode2.fExternal = fExternal;
  ode2.Step(0.5);
  
  //Creazione dei grafici (uno per pianeta)
  vector<TGraph> gr1(ode1.N());
  TCanvas c1("c1","",10,10,500,500);
  
  //Preparazione grafico delle coordinate dei pianeti
  double size=10; // 5 unita' astronimiche
  gPad->DrawFrame(-size,-size,size,size);
  auto legend1 = new TLegend(0.1,0.7,0.2,0.9);
  legend1->AddEntry(&gr1[0],"Sun","l");
  legend1->AddEntry(&gr1[1],"Mercury","l");
  legend1->AddEntry(&gr1[2],"Venus","l");
  legend1->AddEntry(&gr1[3],"Earth","l");
  legend1->AddEntry(&gr1[4],"Moon","l");
  legend1->AddEntry(&gr1[5],"Mars","l");
  legend1->AddEntry(&gr1[6],"Jupiter","l");
  legend1->AddEntry(&gr1[7],"Saturn","l");
  legend1->AddEntry(&gr1[8],"Uranus","l");
  legend1->AddEntry(&gr1[9],"Neptune","l");
  legend1->AddEntry(&gr1[10],"Pluto","l");
  legend1->Draw();
  int color[11]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2,kGray};
  for (unsigned int i=0;i<ode1.N();i++){
    gr1[i].SetPoint(0,ode1.GetMatPoint(i).R().X(),ode1.GetMatPoint(i).R().Y());
    gr1[i].SetMarkerColor(color[i]); gr1[i].SetMarkerStyle(20); gr1[i].SetLineColor(color[i]);
    if (i==0) gr1[i].SetMarkerSize(1);
    else gr1[i].SetMarkerSize(0.2);
    gr1[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();

  //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
  vector<double> L1(ode1.N());
  vector<double> w1(ode1.N());
  vector<double> b1(ode1.N());
  vector<double> a1(ode1.N());

  double S=100;
  while (ode1.T()<S){
    ode1.Solve();
    for (unsigned int i=0;i<ode1.N();i++){
      //STEP 4 riempimento del grafico gr[i] con le coordinate aggiornate dei pianeti
      gr1[i].SetPoint(gr1[i].GetN(),ode1.GetMatPoint(i).R().X(),ode1.GetMatPoint(i).R().Y());
      L1[i]=ode1.GetMomentum(i);
    }
    if(ode1.T()==0.5){
    w1=L1;
    }
    if(ode1.T()==S-0.5){
    b1=L1;
    }
  gPad->Modified(); gPad->Update();
  }

    for (unsigned int i=0;i<ode1.N();i++){
    a1[i]=abs(b1[i]/w1[i]-1)*100;
    cout<<a1[i]<<endl;
    }

  vector<TGraph> gr(ode2.N());
  TCanvas c1("c1","",10,10,500,500);


  gPad->DrawFrame(-size,-size,size,size);
  auto legend2 = new TLegend(0.1,0.7,0.2,0.9);
  legend2->AddEntry(&gr[0],"Sun","l");
  legend2->AddEntry(&gr[1],"Mercury","l");
  legend2->AddEntry(&gr[2],"Venus","l");
  legend2->AddEntry(&gr[3],"Earth","l");
  legend2->AddEntry(&gr[4],"Moon","l");
  legend2->AddEntry(&gr[5],"Mars","l");
  legend2->AddEntry(&gr[6],"Jupiter","l");
  legend2->AddEntry(&gr[7],"Saturn","l");
  legend2->AddEntry(&gr[8],"Uranus","l");
  legend2->AddEntry(&gr[9],"Neptune","l");
  legend2->AddEntry(&gr[10],"Pluto","l");
  legend2->Draw();
  for (unsigned int i=0;i<ode2.N();i++){
    gr[i].SetPoint(0,ode2.GetMatPoint(i).R().X(),ode2.GetMatPoint(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetLineColor(color[i]);
    if (i==0) gr[i].SetMarkerSize(1);
    else gr[i].SetMarkerSize(0.2);
    gr[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();

  //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
  vector<double> L2(ode2.N());
  vector<double> w2(ode2.N());
  vector<double> b2(ode2.N());
  vector<double> a2(ode2.N());

  while (ode2.T()<S){
    ode2.Solve();
    for (unsigned int i=0;i<ode2.N();i++){
      //STEP 4 riempimento del grafico gr[i] con le coordinate aggiornate dei pianeti
      gr[i].SetPoint(gr[i].GetN(),ode1.GetMatPoint(i).R().X(),ode1.GetMatPoint(i).R().Y());
      L2[i]=ode2.GetMomentum(i);
    }
    if(ode2.T()==0.5){
    w2=L2;
    }
    if(ode2.T()==S-0.5){
    b2=L2;
    }
  gPad->Modified(); gPad->Update();
  }

    for (unsigned int i=0;i<ode2.N();i++){
    a2[i]=abs(b2[i]/w2[i]-1)*100;
    cout<<a2[i]<<endl;
    }

  app.Run(true);
  return 0;
  
}
