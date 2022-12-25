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

TCanvas *c1=new TCanvas("c1");

ifstream file("Dati_spettrometro.txt");
double x;
vector<double> xi;
while(file>>x){
    xi.push_back(x);
    h->Fill(x);   
}
file.close();
h->Draw();

double area=500*h->GetBinWidth(2);



app.Run(true);

}