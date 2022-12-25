using namespace std;

void unb_fit(){

TTree *tree=new TTree();
TH1D *h=new TH1D("h","",50,0,58);

tree->ReadFile("dati_highstat.dat","t/D");

TF1 *f=new TF1("f","[0]*([1]*TMath::Gaus(x,[2],[3]) + (1-[1])*exp(-x/[4])/[4])");
f->FixParameter(0,1040*1.16);
//f->SetParameter(1,h->GetEntries()*h->GetBinWidth(2));
f->SetParameter(2,15);
f->SetParameter(4,10);
f->SetParameter(3,0.5);

f->SetParLimits(2,14,16);
f->SetParLimits(4,8,12);
//f->SetParLimits(1,0,10);
f->SetParLimits(3,0.1,2);

ifstream file("dati_highstat.dat");
double y;
while(file>>y){
    h->Fill(y);
}

tree->UnbinnedFit("f","t");
//h->Fit("f","L");
h->Draw();
f->Draw("same");



}