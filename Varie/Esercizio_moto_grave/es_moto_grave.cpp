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
    double g=10;
    double gx=0;
    double gy=0;
    double gz=-g;

    Vector gr(gx,gy,gz);

    return gr;
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

double m,z,vx,vz;
cout<<"Inserire valori di m, z_0 e v_0z"<<endl;
cin>>m;
cin>>z;
cin>>vz;

Particle prt(m,0);
Vector s(0,0,z);
Vector v(0,0,vz);
ode.SetMatPoint(MatPoint(prt,s,v));

ode.fInternal = fInternal;
ode.fExternal = fExternal; 

double t=0.01;
ode.Step(t);

TGraph g;
TCanvas c1("c1","",500,500);
c1.cd();
double size=100;
gPad->DrawFrame(0,-10000,100,10000);

g.SetPoint(0,0,ode.GetMatPoint(0).R().Z());
g.SetMarkerStyle(20);
g.Draw("P");

gPad->Modified(); gPad->Update();
app.Run(true);

double S=1000*t;

while(ode.T()<S){
    ode.Solve();
    g.SetPoint(g.GetN(),ode.T(),ode.GetMatPoint(0).R().Z());
    gPad->Modified(); gPad->Update();
    cout<<ode.GetMatPoint(0).R().Z()<<" "<<ode.T()<<endl;
    if(ode.GetMatPoint(0).R().Z()<=0){
        break;
    }
}

app.Run(true);

return 0;

}