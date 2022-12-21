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
double get_TRangeErr(double range1, double errPercent = 0.0016, int partition = 10){
    return range1 * errPercent * partition;
}

double getH(double vin, double vout){
    return vout / vin;
}

double get_HErr(double Vin, double Vout, double eVin, double eVout){ 
  return sqrt(pow(eVout / Vin, 2) + pow(eVin * Vout / pow(Vin, 2), 2));
}

double get_phi(double T, double dt){
    return 2 * M_PI * dt / T;
}

double get_phiErr(double T, double dt, double eT, double edt){
    return 2 * M_PI * sqrt(pow(edt/T, 2) + pow(dt * eT/(pow(T, 2)), 2));
}

void filtro_RC(){

std::ifstream file("filtro_RC.txt");

double Vin, Vout, fsVin, fsVout, T, dT, fsT, fsdT;

TCanvas* c1 = new TCanvas("c1", "", 600, 600);
c1->Divide(1,2,0.001,0.001,0);

TCanvas* c2 = new TCanvas("c2", "", 600, 600);
c2->Divide(1,2,0.001,0.001,0);

TCanvas* c3 = new TCanvas("c3", "", 600, 600);

TGraphErrors* g1 = new TGraphErrors;
TGraphErrors* g2 = new TGraphErrors;

TGraphErrors *r1 = new TGraphErrors;
TGraphErrors *r2 = new TGraphErrors;

TGraphErrors *b = new TGraphErrors;

TF1* fit_bode = new TF1("fit_bode","1/sqrt(1+pow([0]/x,2))");   //Controllare formule se il filtro è PASSA BASSO!!!
//fit_bode->SetParameter(0,?); 
TF1* fit_fase = new TF1("fit_fase","atan([0]/x)");
//fit_fase->SetParameter(0,?); 
TF1 *j = new TF1("j","0*x",0,20e5);

vector<double> h,fi,eh,efi,t,et;
for(int i=0; file>>Vin>>fsVin>>Vout>>fsVout>>T>>fsT>>dT>>fsdT; i++){
    double eVin, eVout, eT, edT;
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
    eT=get_TRangeErr(fsT);
    edT=get_TRangeErr(fsT);
    double H=getH(Vin,Vout);
    double eH=get_HErr(Vin,Vout,eVin,eVout);
    double phi=get_phi(T,dT);
    double ephi=get_phiErr(T,dT,eT,edT);
    
    h.push_back(H);
    fi.push_back(phi);
    eh.push_back(eH);
    efi.push_back(ephi);
    t.push_back(T);
    et.push_back(eT);

    g1->SetPoint(i,1/T,H);
    g1->SetPointError(i,eT/(pow(T,2)),eH);

    g2->SetPoint(i, 1 / T, phi);
    g2->SetPointError(i, eT/pow(T, 2), ephi);

}
c1->cd(1);
g1->Draw("ap");
g1->Fit("fit_bode");
g1->SetTitle("Bode |H|;1/T[Hz];|H|");
gStyle->SetOptFit();
double w_0_1=fit_bode->GetParameter(0);
double ew_0_1=fit_bode->GetParError(0);
c1->cd(2);
for(int i=0;i<t.size();i++){
   r1->SetPoint(i,1/t[i],(h[i]-fit_bode->Eval(1/t[i]))/eh[i]);
   r1->SetPointError(i,et[i]/pow(t[i],2), sqrt(pow(t[i],2)+pow(h[i],2)) );  //definire meglio gli errori !!!
}
r1->Draw("ap");
j->Draw("same");

c1->SaveAs("../figure/RC_bode_H.pdf");

c2->cd(1);
g2->Draw("ap");
g2->Fit("fit_fase");
g2->SetTitle("Bode phi;1/T[Hz];phi");
gStyle->SetOptFit();
double w_0_2=fit_fase->GetParameter(0);
double ew_0_2=fit_fase->GetParError(0);

c2->cd(2);
for(int i=0;i<t.size();i++){
   r2->SetPoint(i,1/t[i],(fi[i]-fit_fase->Eval(1/t[i]))/efi[i]);
   r2->SetPointError(i,et[i]/pow(t[i],2), sqrt(pow(t[i],2)+pow(efi[i],2)) );  //definire meglio gli errori !!!
   b->SetPoint(i,(fi[i]-fit_fase->Eval(1/t[i]))/efi[i],1/t[i]);
   b->SetPointError(i,sqrt(pow(t[i],2)+pow(efi[i],2)),et[i]/pow(t[i],2));
}
r2->Draw("ap");
j->Draw("same");
c2->SaveAs("../figure/RC_bode_phi.pdf");

c3->cd();
b->Draw("ap");

double best_value = (w_0_1/pow(ew_0_1,2)+w_0_2/pow(ew_0_2,2))/(1/pow(ew_0_1,2)+1/pow(ew_0_2,2));
double e_b_v = sqrt((pow(ew_0_1,2)*pow(ew_0_2,2))/(pow(ew_0_1,2)+pow(ew_0_2,2)));

if(abs(w_0_1-w_0_2) < 3*sqrt(pow(ew_0_1,2)+pow(ew_0_2,2))){
    std::cout<<"I valori dei parametri sono compatibili e la miglior stima è:"<<best_value<<" +/- "<<e_b_v<<std::endl;
}
else{
    std::cout<<"I due valori non sono compatibili"<<std::endl;
}

}