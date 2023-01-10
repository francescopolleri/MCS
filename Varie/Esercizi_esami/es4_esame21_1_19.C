using namespace std;

void es4_esame21_1_19(){
    ifstream file("dati_gamma.txt");
    double x;
    TH1D *h = new TH1D("h","",100,0,30);
    while (file>>x){
        h->Fill(x);
    }

    TTree *t = new TTree();
    t->ReadFile("dati_gamma.txt","t/D");

    TF1 *f = new TF1("f","[0]*pow(x,2)*exp(-x/[1])/(2*pow([1],3))",0,20);
    f->FixParameter(0,1.);
    f->SetParameter(1,2.);

    t->UnbinnedFit("f","t");
    
    h->SetMarkerStyle(20);
    h->Draw("E 0");
    f->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));
    f->Draw("SAME");


}


