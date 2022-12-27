using namespace std;

void binned_fit_MULTI(){

TH1D *h=new TH1D("h","",80,0,80);

TF1 *f=new TF1("f","[0]*([1]*TMath::Gaus(x,[2],[3]) + ((1-[1])/[4])*exp(-x/[4]))",0,80);

f->FixParameter(0,1);
f->SetParameter(1,0.5);
f->SetParameter(2,15);
f->SetParameter(4,10);
f->SetParameter(3,1);

f->SetParLimits(1,0,1);
f->SetParLimits(2,14,16);
f->SetParLimits(3,0,0.4);
f->SetParLimits(4,9,11);


ifstream file("dati_highstat.dat");
double y;
while(file>>y){
    h->Fill(y);
}

h->Fit("f","0MULTI");
f->SetParameter(0,1040*100/80);

h->Draw();
f->Draw("same");

}