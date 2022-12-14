using namespace std;

void fitexpTTree(){

  ifstream file("exp.txt");
  double x;
  TH1D *h = new TH1D("h","",40,0,10);
  while (file >> x){
    h->Fill(x);
  }

  TTree *t = new TTree();
  t->ReadFile("exp.txt","t/D");

  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);
  fe->FixParameter(0,1.);
  fe->SetParameter(1,2.);

  t->UnbinnedFit("fe","t");
  
  h->SetMarkerStyle(20);
  h->Draw("E");

  fe->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
  fe->Draw("same");
}
