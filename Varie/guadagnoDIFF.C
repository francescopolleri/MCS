#include<vector>
#include<cmath>
#include<iostream>
#include<fstream>
#include<string>

#include<TCanvas.h>
#include<TGraphErrors.h>
#include<TF1.h>
#include<TStyle.h>
#include<TAxis.h>
#include<TMath.h>
#include<TLatex.h>
#include<TLegend.h>

double get_VRangeErr(double errPercent, int partitions, double range1){ 
  return errPercent * partitions *  range1;
}

void guadagnoDIFF(){

std::ifstream file("guadagnoDIFF.txt");

double Vin,fsVin,Vout,fsVout;
TGraphErrors* g1 = new TGraphErrors;
TF1* f = new TF1("f","[0]+x*[1]");

vector<double> vi;
vector<double> vo;
for(int i=0; file>>Vin>>fsVin>>Vout>>fsVout; i++){
    vi.push_back(Vin);
    vo.push_back(Vout);
 double eVin, eVout;
    if (fsVin<0.01){
        eVin=get_VRangeErr(0.04,8,fsVin)/sqrt(3);
        }
    else{
        eVin=get_VRangeErr(0.03,8,fsVin)/sqrt(3);
        }
    if(fsVout<0.01){
        eVout=get_VRangeErr(0.04,8,fsVout)/sqrt(3);
    }
    else{
        eVout=get_VRangeErr(0.03,8,fsVout)/sqrt(3);
    }
g1->SetPoint(i,Vin,Vout);
g1->SetPointError(i,eVin,eVout);

}

TCanvas* c1 = new TCanvas("","",800,600);
//c.Divide(2,1,0.01,0.01,0);
c1->cd();

g1->Fit("f");
g1->Draw("ap");
g1->SetTitle("Fit G_DIFF;V_in[V];V_out[V]");
gStyle->SetOptFit();


double q = f->GetParameter(0);
double G = f->GetParameter(1);

double eq = f->GetParError(0);
double eG = f->GetParError(1);

TCanvas* c3 = new TCanvas("","",800,600);
c3->cd();
TGraphErrors *g3 = new TGraphErrors;
TF1 *h = new TF1("h","sin(x)",0,10);
h->Draw();

vector<double> fv; 
for(int i=0;i<vi.size();i++){
   //fv.push_back(f.Eval(v[i]));
   g3->SetPoint(i,vi[i],f->Eval(vi[i])-vo[i]);
   g3->SetPointError(i,0.001,0,001)
   g3->SetMarkerSize(100);
}

g3->Draw("ap");

std::cout<<"quota = "<<q<<" +/- "<<eq<<std::endl;
std::cout<<"G_DIFF = "<<G<<" +/- "<<eG<<std::endl;

}

