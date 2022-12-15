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
  //Vector F_int(p[i].Mass()*p[j].GravField(p[i].R()));
  Vector V(0,0,0);
  return V;
}

Vector fExternal(unsigned int i, double t, vector<MatPoint> p){
    double k=1;
    double w=0.25;
    double A=0.1;
    double beta=0.03;

    Vector F_el(-(k/p[i].Mass())*p[i].R().X(),0,0);
    Vector F_visc(-2*beta*p[i].V().X()/p[i].Mass());
    Vector F_ext(A*sin(w*t)/p[i].Mass());

    return F_el + F_visc + F_ext;
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

double m=1;
double x=1;

Particle prt(m,0);
Vector s(x,0,0);
Vector v(0,0,0);

ode.SetMatPoint(MatPoint(prt,s,v));

ode.fInternal = fInternal;
ode.fExternal = fExternal; 

double t=0.25;
ode.Step(t);

TGraph g;
TCanvas c1("c1","",500,500);
c1.cd();
gPad->DrawFrame(-1,-2,101,2);
gPad->SetTitle("x(t)");

TLegend legend;
legend.AddEntry("g","x(t)","p");
g.SetPoint(0,0,ode.GetMatPoint(0).R().X());
g.SetTitle("x(t)");
g.Draw("P");

gPad->Modified(); gPad->Update();
app.Run(true);

double S=400*t;

while(ode.T()<S){
    ode.Solve();
    g.SetPoint(g.GetN(),ode.T(),ode.GetMatPoint(0).R().X());
    gPad->Modified(); gPad->Update();
}

c1.SaveAs("oscillatore.pdf");
app.Run(true);

return 0;

}