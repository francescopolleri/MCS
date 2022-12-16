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

Vector Gravity(Vector r){
    double g=9.8056;
    double beta=1;
    double gx=0;
    double gy=0;
    double gz= -g ;

    Vector gr(gx,gy,gz);

    return gr;
}

Vector Visc(Vector v,double M){
    double beta=5;
    double v1=0;
    double v2=0;
    double v3=beta*v.Z();
    Vector visc(v1,v2,v3);
    return visc*(1/M);
}

Vector fExternal(unsigned int i, double t, vector<MatPoint> p){
    return (Gravity(p[i].R()) - Visc(p[i].V(),p[i].Mass()))*p[i].Mass();
}

int main(){ 
  
TApplication app("app",0,NULL);
gStyle->SetOptStat(0);

/*
string method_name;
cout<<"What method do you want to use?"<<endl;
cout<<"(Enter 'ELR' for Eulero,'RK2' for Runge-Kutta2,'RK4' for Runge-Kutta4 and 'VV' for Verltet velocity)"<<endl;
cin>>method_name;
*/
OdeSolver ode;
ode.SetMethod("RK2");

double m,z,vx,vz;
cout<<"Inserire valori di m, z_0 e v_0z"<<endl;
cin>>m;
cin>>z;
cin>>vz;

double g_const=9.8056;
double beta=5;

Particle prt(m,0);
Vector s(0,0,z);
Vector v(0,0,vz);
ode.SetMatPoint(MatPoint(prt,s,v));

ode.fInternal = fInternal;
ode.fExternal = fExternal; 

double t=0.1;
ode.Step(t);

TGraph g;
TGraph g2;
TCanvas c1("c1","",900,700);
c1.Divide(2,1);

c1.cd(1);
gPad->DrawFrame(0,-10,20,500);     //Grafico z(t)
TF1* f = new TF1("f","0*x",0,100);
f->SetLineColor(kRed-5);
TF1* h = new TF1("h","[0]*pow(x,2)+[1]*x+[2]",0,100);
h->SetLineColor(kRed);
h->FixParameter(0,-g_const/2);
h->FixParameter(1,vz);
h->FixParameter(2,z);
auto legend = new TLegend(0.5,0.7,0.9,0.9);
legend->AddEntry("g","z(t)","p");
legend->AddEntry("h","z(t) nel vuoto","l");
legend->AddEntry("f","Suolo","l");
legend->Draw();
f->Draw("SAME");
h->Draw("SAME");
g.SetPoint(0,0,ode.GetMatPoint(0).R().Z());
g.SetMarkerStyle(20);
g.Draw("P");

c1.cd(2);                        //Grafico v_z(t)
gPad->DrawFrame(0,-50,50,50);
g2.SetPoint(0,0,vz);
g2.SetMarkerColor(kBlue);
g2.SetMarkerStyle(20);
TF1* fun = new TF1("fun","[0]",0,1000);
fun->FixParameter(0,-m*g_const/beta);
auto legend1 = new TLegend(0.7,0.8,0.9,0.9);
legend1->AddEntry("g","v_{z}(t)","p");
g2.Draw("P");
fun->Draw("SAME");
legend1->Draw("SAME");

gPad->Modified(); gPad->Update();
app.Run(true);

double S=10000*t;

while(ode.T()<S){
    ode.Solve();
    g.SetPoint(g.GetN(),ode.T(),ode.GetMatPoint(0).R().Z());
    g2.SetPoint(g2.GetN(),ode.T(),ode.GetMatPoint(0).V().Z());
    c1.cd(1);
    gPad->Modified(); gPad->Update();
    c1.cd(2);
    gPad->Modified(); gPad->Update();
    cout<<ode.GetMatPoint(0).R().Z()<<" "<<ode.T()<<endl;
    if(ode.GetMatPoint(0).R().Z()<=0){
        break;
    }
}
cout<<"Tempo di volo = "<<ode.T()<<endl;
//gPad->Modified(); gPad->Update();

app.Run(true);

return 0;
}