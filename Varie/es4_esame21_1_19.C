using namespace std;

void es4_esame21_1_19(){
    ifstream file("dati_gamma.dat");
    double x;
    TH1D *h=new TH1D("h","",100,0.,0.);
    while (file>>x){
        h->Fill(x);
    }

    TTree *t= new TTree();
    t->ReadFile("dati_gamma.dat","t/D");

    TF1 *f=new TF1("f","[1]*(pow(x,2)*exp(-x/[0]))/(2*pow([0],3))",0,30);
        
    f->SetParameter(0,1.5);
    f->FixParameter(1,1.);

    t->UnbinnedFit("f","t");

    h->Draw();

    f->SetParameter(1,h->GetEntries()*h->GetBinWidth(1));
    f->Draw("SAME");

}