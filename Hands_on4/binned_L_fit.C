using namespace std;

void binned_L_fit(){

TH1D *h=new TH1D("h","",80,0,100);

TF1 *f=new TF1("f","[0]*( [1]*TMath::Gaus(x,[2],[3]) + ((1-[1])/[4])*exp(-x/[4]))",0,100);
f->SetParameter(0,1040*100/80);
f->SetParameter(1,0.5);
f->SetParameter(2,15);
f->SetParameter(4,10);
f->SetParameter(3,1);

TF1 *bkg=new TF1("bkg","[0]*(1-[1])*[2]*exp(-x*[2])",0,40);
bkg->SetParameter(0,1040*100/80);
bkg->SetParameter(1,0.5);
bkg->SetParameter(2,0.1);


ifstream file("dati_highstat.dat");
double y;
while(file>>y){
    h->Fill(y);
}

h->Fit("bkg");
double Int=bkg->Integral(14,16);
double n_bkg=Int*0.8;
cout<<n_bkg<<endl;
h->Fit("f","L");

h->Draw();
f->Draw("same");

}