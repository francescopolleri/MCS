#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TH1D.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TF1.h>

using namespace std;

int main(){
TApplication app("app",NULL,NULL);

TH1D *h=new TH1D("h","",30,0.55,0.6);
TH1D *k=new TH1D("k","",30,0.,0.);

TCanvas *c1=new TCanvas("c1");
TCanvas *c2=new TCanvas("c2");

ifstream file("Dati_spettrometro.txt");
double x;
vector<double> xi;
while(file>>x){
    xi.push_back(x);
    h->Fill(x);   
}
file.close();
c1->cd();
h->Draw();

double area=500*h->GetBinWidth(2);
ifstream ifile("Dati_spettrometro.txt");
double y;
while(ifile>>y){
    k->Fill(y/area);
}
c2->cd();
//k->Draw();

TF1 *f=new TF1("f","TMath::Gaus(x,[0],[1],1)+(1-[0])*(TMath::Gaus(x,[2],[3],1))");

f->SetParameter(1,0.681);
f->SetParameter(3,0.702);
f->SetParameter(2,0.005);
f->SetParameter(4,0.001);

k->Fit("f","MULTI");
k->Draw();

app.Run(true);

}