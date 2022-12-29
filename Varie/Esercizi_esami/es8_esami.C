using namespace std;

void es8_esami(){

ifstream file("es4_data.dat");

TH1D *h = new TH1D("h","",75,-1,1);  //Bisogna stare attenti al binning!

double dat;
while (file>>dat){
    h->Fill(dat);
}

TF1 *f = new TF1("f","[0]*(1+[1]*x+[2]*x*x)");

f->SetParameters(h->GetEntries()*h->GetBinWidth(1),1,1);
h->Fit("f","L");
double sig0=f->GetParError(0);
double sig1=f->GetParError(1);
double sig2=f->GetParError(2);
double K=f->GetParameter(0);
double alpha=f->GetParameter(1);
double beta=f->GetParameter(2);

double mat[3][3];

gMinuit->mnemat(&mat[0][0],3);

double rho=mat[1][2]/(sig1*sig2);
cout<<"rho = "<<rho<<endl;

double gamma=3*alpha-2*beta;
double e_gamma=9*sig1*sig1+4*sig2*sig2-12*rho*sig1*sig2;

cout<<"gamma = "<<gamma<<" +/- "<<e_gamma<<endl;

h->Draw();

}