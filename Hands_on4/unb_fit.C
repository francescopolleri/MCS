using namespace std;

void unb_fit(){

TTree *tree=new TTree();
TH1D *h=new TH1D("h","",50,0,58);

tree->ReadFile("dati_highstat.dat","t/D");

TF1 *f=new TF1("f","[0]*((1-[1])*TMath::Gaus(x,[2],[3]) + [1]*exp(-x/[4])/[4])");
f->FixParameter(0,1);
f->SetParameter(1,h->GetEntries()*h->GetBinWidth(2));
f->SetParameter(2,15);
f->SetParameter(4,10);

ifstream file("dati_highstat.dat");
double y;
while(file>>y){
    h->Fill(y);
}
h->Draw();

tree->UnbinnedFit("f","t");


}