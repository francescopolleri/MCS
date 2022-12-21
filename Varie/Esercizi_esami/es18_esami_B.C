using namespace std;

void es18_esami_B(){

ifstream file("File.txt");
double x;
TH1D *h = new TH1D("h","",80,0.,0.);
while (file >> x){
  h->Fill(x);
}

TTree *t =new TTree();
t->ReadFile("File.txt","t/D");   

TF1 *f=new TF1("f","[0]*[1]*pow(x,[1]-1)");
f->FixParameter(0,1);
f->SetParameter(1,3);

t->UnbinnedFit("f","t");

h->Draw();

f->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
f->Draw("SAME");


}