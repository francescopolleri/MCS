using namespace std;

void Distrib_and_TTree(){

TRandom3 rnd;
rnd.SetSeed(123456789);

int Nev=10000;

double th=3;
double x;

TH1D *h=new TH1D("h","",100,0.,0.);
TTree *t=new TTree();
t->Branch("t",&x,"t/D");
for(int i=0;i<Nev;i++){
    x=pow(rnd.Rndm(),1/th);
    t->Fill();
}

TF1 *f=new TF1("f","[0]*[1]*pow(x,[1]-1)");
f->FixParameter(0,1);
f->SetParameter(1,3);

t->UnbinnedFit("f","t");
t->Draw("t>>h");

f->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
f->Draw("SAME");

}