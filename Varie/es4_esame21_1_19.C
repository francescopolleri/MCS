using namespace std;

void es4_esame21_1_19(){
    ifstream file("dati_gamma.txt");
    double x;
    TH1D *h = new TH1D("h","",50,0.,0.);
    while (file>>x){
        h->Fill(x);
    }

    TTree *t = new TTree();
    t->ReadFile("dati_gamma.txt","t/D");

    TF1 *f = new TF1("f","[0]*pow(x,2)*exp(-x/[1])/(2*pow([1],3))",0,26);
    f->SetParameter(0,1.);
    f->SetParameter(1,2.);
    f->SetParLimits(0,0,10);
    f->SetParLimits(1,1,3);

    t->UnbinnedFit("f","t","t<17");

    f->SetParameter(1,h->GetEntries()*h->GetBinWidth(1));

    h->SetMarkerStyle(20);
    h->Draw("E");
    f->Draw("same");

}


