#include "poligono.h"
#include "punto.h"
#include "triangolo.h"

#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<TGraphErrors.h>
#include<TGraph.h>
#include<TCanvas.h>
#include<TApplication.h>

using namespace std;

int main(){
TApplication app("app",0,NULL);

TGraph* g = new TGraph;
TGraph* g2 = new TGraph;
TCanvas* c1 = new TCanvas("c1","",500,700);
c1->Divide(1,2);

punto p0(0.,0.);
punto p1(2.,0.);
punto p2(2.,2.);
punto p3(0.,2.);

vector<punto> plg;
plg.push_back(p0);
plg.push_back(p1);
plg.push_back(p2);
plg.push_back(p3);

poligono pol1(plg);

double perQ=pol1.perimetro();

cout<<"perimetro quadrato = "<<perQ<<endl;

triangolo trn(1,1,M_PI/4);

double aT=trn.area();
double perT=trn.perimetro();

cout<<"perimetro triangolo = "<<perT<<endl;
cout<<"area triangolo = "<<aT<<endl;


for (int j=0;j<plg.size();j++){
    g2->SetPoint(j,plg[j].X(),plg[j].Y());
    g2->SetMarkerStyle(20);
    g2->SetMarkerSize(1);
    g2->SetMarkerColor(kBlue);
    g2->SetLineColor(kBlue);
}

ifstream file ("esagono.txt");
vector<punto> esg;
double x,y;
int i=0;
while(file>>x>>y){
    esg.push_back(punto(x,y));
    g->SetPoint(i,x,y);
    g->SetMarkerStyle(20);
    g->SetMarkerSize(1);
    g->SetMarkerColor(kGreen);
    g->SetLineColor(kGreen);
    i++;
}
poligono esagono(esg);
double per_esg=esagono.perimetro();
cout<<"perimetro esagono = "<<per_esg<<endl;

c1->cd(1);
g->Draw("al");
c1->cd(2);
g2->Draw("al");

app.Run(true);
}