#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <Math/Factory.h>

using namespace std;

namespace data{
  int n;
  vector<double> x1,t1,et1;
  vector<double> x2,t2,et2;
}

TF1 *f1;
TF1 *f2;

void chi2(int &npar, double *gin, double &f, double *par, int iflag){
  f=0;
  f1->SetParameters(par[0],par[1],par[2],par[3]);
  f2->SetParameters(par[0],par[1],par[4],par[5]);
  for(int i=0;i<data::n;i++){   //Questo è un caso particolare perchè ho lo stesso numero di dati per entrambi i fit
    f += pow( (data::t1[i]-f1->Eval(data::x1[i]))/data::et1[i] ,2);
    f += pow( (data::t2[i]-f2->Eval(data::x2[i]))/data::et2[i] ,2);
  }
}


int main(){

  TApplication app("app",0,NULL);

  ifstream fp1("perno1.dat");
  ifstream fp2("perno2.dat");
  double tx1,tt1,tex1,tet1;
  double tx2,tt2,tex2,tet2;


  TGraphErrors gr1;
  while (fp1 >> tx1 >> tt1 >> tex1 >> tet1){
    data::x1.push_back(tx1);
    data::t1.push_back(tt1);
    data::et1.push_back(tet1);
    gr1.SetPoint(gr1.GetN(),tx1,tt1);
    gr1.SetPointError(gr1.GetN()-1,tex1,tet1);
  }

  TGraphErrors gr2;
  while (fp2 >> tx2 >> tt2 >> tex2 >> tet2){
    data::x2.push_back(tx2);
    data::t2.push_back(tt2);
    data::et2.push_back(tet2);
    gr2.SetPoint(gr2.GetN(),tx2,tt2);
    gr2.SetPointError(gr2.GetN()-1,tex2,tet2);
  }
  data::n=data::x1.size();

  f1 = new TF1("f1","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n-1]);
  f2 = new TF1("f2","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n-1]);

  gr1.Fit("f1");
  gr2.Fit("f2");
  f1->SetLineColor(kRed);
  f2->SetLineColor(kBlue);
  gr1.Draw("AP");
  gr2.Draw("P");
  //app.Run(true);

  // Minuit
  TMinuit minuit(6);
  minuit.SetFCN(chi2);

  minuit.DefineParameter(0,"x0",36,0.01,0.,0.);
  minuit.DefineParameter(1,"T0",4,0.01,0.,0.);
  minuit.DefineParameter(2,"a1",f1->GetParameter(2),0.01,0.,0.);
  minuit.DefineParameter(3,"b1",f1->GetParameter(3),0.01,0.,0.);
  minuit.DefineParameter(4,"a2",f1->GetParameter(2),0.01,0.,0.);
  minuit.DefineParameter(5,"b2",f1->GetParameter(3),0.01,0.,0.);

  minuit.Command("MIGRAD");

  app.Run(true);

  return 0;

}
