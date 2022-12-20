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
  Vector V(0,0,0);
  return V;
}

Vector Visc(Vector v){
    double rho=1;
    double rho0=8000;
    double mu=0.001;
    double r=0.01;

    double Re=2*rho*r/mu;
    
    double Cd=24*v.Mod()/Re + 4*pow(v.Mod(),3/2) + 0.4*pow(v.Mod(),2);

    double f1=0;
    double f2=0;
    double f3=M_PI*Cd*rho*r*r/2;

    Vector F(f1,f2,f3);
    return F;
}

Vector Gravity(Vector r){
    double g=9.8056;
    double gx=0;
    double gy=0;
    double gz= g ;

    Vector gr(gx,gy,gz);

    return gr;
}

Vector Archimede(){
   double r=0.01;
   double g=9.8056;
   double rho=10;
   double a1=0;
   double a2=0;
   double a3= 4/3.*M_PI*pow(r,3)*rho*g;

   Vector a(a1,a2,a3);
   return a;
}

Vector fExternal(unsigned int i, double t, vector<MatPoint> p){
    return - Visc(p[i].V()) + Gravity(p[i].R())*p[i].Mass();
}


int main(){ 
  
TApplication app("app",0,NULL);
gStyle->SetOptStat(0);

OdeSolver ode;
ode.SetMethod("RK2");

double z0=100;
double raggio=0.01;
double rho0=8000;
double M=4/3*M_PI*pow(raggio,3)*rho0;

Particle prt(M,0);
Vector s=(0,0,z0);
Vector v=(0,0,0);

ode.SetMatPoint(MatPoint(prt,s,v));

ode.fInternal = fInternal;
ode.fExternal = fExternal; 

double t=0.1;
ode.Step(t);

TCanvas c1("c1","",600,600);
gPad->DrawFrame(0,-10,200,100); 
TGraph *g=new TGraph;

g->SetPoint(0,0,ode.GetMatPoint(0).V().Z());
g->SetMarkerStyle(20);
g->Draw("P");

gPad->Modified(); gPad->Update();

app.Run(true);

double S=1000*t;

while(ode.T()<S){
    ode.Solve();
    g->SetPoint(g->GetN(),ode.T(),ode.GetMatPoint(0).V().Z());
    gPad->Modified(); gPad->Update();

    cout<<ode.GetMatPoint(0).V().Z()<<endl;
}

c1.SaveAs("No_Archimede.pdf");

app.Run(true);

return 0;


}