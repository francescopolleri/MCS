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

Vector Gravity(Vector r){
    double M=1000000;
    double gx=r.X();
    double gy=r.Y();
    double gz=r.Z();
    double mod=r.Mod();

    Vector g(gx,gy,gz);

    return g*(-1/pow(mod,3));
}

Vector fExternal(unsigned int i, double t, vector<MatPoint> p){
    return Gravity(p[i].R())*p[i].Mass();
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

double m,x,vy;
cout<<"Inserire valori di m,x e vy"<<endl;
cin>>m;
cin>>x;
cin>>vy;

Particle prt(m,0);
Vector s(x,0,0);
Vector v(0,vy,0);
ode.SetMatPoint(MatPoint(prt,s,v));

ode.fInternal = fInternal;
ode.fExternal = fExternal; 

double t=0.5;
ode.Step(t);

TGraph g;
TCanvas c1("c1","",500,500);
c1.cd();
double size=10;
gPad->DrawFrame(-size,-size,size,size);

g.SetPoint(0,ode.GetMatPoint(0).R().X(),ode.GetMatPoint(0).R().Y());
g.Draw("P");

gPad->Modified(); gPad->Update();
app.Run(true);

double S=1000*t;

while(ode.T()<S){
    ode.Solve();
    g.SetPoint(g.GetN(),ode.GetMatPoint(0).R().X(),ode.GetMatPoint(0).R().Y());

    gPad->Modified(); gPad->Update();

    cout<<ode.GetMatPoint(0).R().X()<<endl;
}

app.Run(true);

return 0;

}