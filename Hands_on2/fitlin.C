using namespace std;

namespace data{
  vector<double>  x, y, ex, ey;
}

double fun(const double *x,const double *par){
  return par[0]*(*x)+par[1];
}

void fcn(int &npar, double *gin, double &f, double *par, int iflag){
  f = 0.0;
  for (int i=0;i<data::x.size();i++){
    f += pow((data::y[i]-fun(&data::x[i],par))/data::ey[i],2);
  }
}

void fitlin(){
  ifstream file("pendolo.dat");
  double x,y,ex,ey;
  while (file >> x >> y >> ex >> ey){
    data::x.push_back(x); data::y.push_back(y); data::ex.push_back(ex); data::ey.push_back(ey);
  }

  // Define the minimization problem
TMinuit *minuit = new TMinuit(2);  //2 è il numero di parametri
minuit->SetFCN(fcn);
minuit->DefineParameter(0, "a", 4.0, 0.01, 0. , 0.);
minuit->DefineParameter(1, "b", 0.0, 0.01, 0. , 0.);
  // Minimize
minuit->Command("MIGRAD");
  // Get result
double a,b,ea,eb;
minuit->GetParameter(0,a,ea);
minuit->GetParameter(1,b,eb);

cout<<"a = "<<a<<" +/- "<<ea<<endl;
cout<<"b = "<<b<<" +/- "<<eb<<endl;


gMinuit->SetErrorDef(11.825);                        //SetErrorDef serve per settare il valore di DeltaChi2 relativo ad un 
TGraph *Cont3=(TGraph*)gMinuit->Contour(100,0,1);    //certo numero di sigma. 
Cont3->Draw("SAME");                                   //11.8->3 sigma; 2.3->2 sigma; 1->1 sigma
gMinuit->SetErrorDef(2.3);
TGraph *Cont2=(TGraph*)gMinuit->Contour(100,0,1);
Cont2->Draw("SAME");
gMinuit->SetErrorDef(1);
TGraph *Cont1=(TGraph*)gMinuit->Contour(100,0,1);
Cont1->Draw("SAME");


}
