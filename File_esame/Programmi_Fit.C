using namespace std;

void Programmi_Fit(){
  /*
  ifstream file("exp.txt");    //Fit con TTree (Fit di Likelihood Unbinned)
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
  */



  /*
  TH1D *h=new TH1D("h","",20,0,10);   //Fit opzione MULTI (Binned Likelihood)
  ifstream file("exp.txt");
  double x;
  while(file>>x){
    h->Fill(x);
  }

  TF1 *f=new TF1("f","[0]*1/[1]*exp(-x/[1])",0,20);
  f->SetParameter(1,2);
  f->FixParameter(0,1);

  h->Fit("f","0 MULTI");

  f->SetParameter(0,h->GetBinWidth(2)*h->GetEntries());

  h->Draw("E");
  f->Draw("SAME");
  */



  TH1D *h=new TH1D("h","",20,0,10);   //Fit opzione L (Extended Binned Likelihood)
  ifstream file("exp.txt");
  double x;
  while(file>>x){
    h->Fill(x);
  }

  TF1 *f=new TF1("f","[0]*1/[1]*exp(-x/[1])",0,20);
  f->SetParameter(1,2);
  f->SetParameter(0,h->GetBinWidth(2)*h->GetEntries());

  h->Fit("f","L");

  h->Draw("E");
  f->Draw("SAME");

}