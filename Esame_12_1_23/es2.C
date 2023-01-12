using namespace std;

void es2(){

  ifstream file("data.txt");
  double k;
  double x;

  TH1D *h=new TH1D("h","",99,1,100);

  int i=0;
  while(file>>k>>x){
    h->SetBinContent(i,x);
    i++;
  }
  
 h->Draw();

 double E0=1;
 
 TF1 *f1 =new TF1("f1","[0]*pow(x,-[1])");
 f1->SetParameter(0,h->GetEntries()*h->GetBinWidth(2));

 h->Fit("f1","0 L");
 cout<<f1->GetProb()<<endl;
 if(f1->GetProb()<0.05){
   cout<<"Al 95% di CL possiamo rigettare l'ipotesi che la distribuzione sia solo legge di potenza"<<endl;
 }
 else{
 cout<<"Al 95% di CL non possiamo rigettare l'ipotesi che la distribuzione sia solo legge di potenza"<<endl;
 }

 TF1*f2=new TF1("f2","[0]*pow(x,[1])*exp(-x/[2])");
 f2->SetParameter(0,h->GetEntries()*h->GetBinWidth(2));
 f2->SetParameter(1,f1->GetParameter(1));
 f2->SetParameter(2,1000000);

 h->Fit("f2","L");

 double Ecut=f2->GetParameter(2);
 double gamma=f2->GetParameter(1);
 double sig1=f2->GetParError(1);
 double sig2=f2->GetParError(2);

 cout<<"Gamma = "<<gamma<<"+/-"<<sig1<<endl;
 cout<<"E cut = "<<Ecut<<"+/-"<<sig2<<endl;
 /*
 double mat[3][3];
 gMinuit->mnemat(&mat[0][0],3);

 double rho=mat[1][2]/(sig1*sig2);
 cout<<"rho = "<<rho<<endl;
 */


}
