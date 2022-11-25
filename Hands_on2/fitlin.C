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

}
