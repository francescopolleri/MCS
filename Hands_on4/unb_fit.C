using namespace std;

void unb_fit(){

TTree *tree=new TTree();
TH1D *h=new TH1D("h","",50,0,58);

tree->ReadFile("dati_highstat.dat","t/D");

TF1 *f=new TF1("f","[0]*( [1]*TMath::Gaus(x,[2],[3]) + ((1-[1])/[4])*exp(-x/[4]))",0,80);
f->FixParameter(0,1);
f->SetParameter(1,0.0001);
f->SetParameter(2,15);
f->SetParameter(4,10);
f->SetParameter(3,0.8);


f->SetParLimits(2,14,16);
f->SetParLimits(4,8,12);
f->SetParLimits(1,0,0.99);
f->SetParLimits(3,0.1,1);

ifstream file("dati_highstat.dat");
double y;
while(file>>y){
    h->Fill(y);
}

tree->UnbinnedFit("f","t");
//h->Fit("f","L");

f->SetParameter(0,h->GetEntries()*h->GetBinWidth(2));

h->Draw();
f->Draw("same");

}