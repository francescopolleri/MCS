using namespace std;

void es18_esami_A(){

TRandom3 rnd;
rnd.SetSeed(123456789);

int Nev=10000;

double th=3;
double x=0;

ofstream file("File.txt");

vector<double> xi;

for (int i=0;i<Nev;i++){
    x=pow(rnd.Rndm(),(1/th));
    xi.push_back(x);
}

for(int i=0;i<Nev;i++){
    file<<xi[i]<<endl;
}

file.close();

ifstream ifile("File.txt");
double X;
TH1D *h = new TH1D("h","",80,0.,0.);
while (ifile >> X){
  h->Fill(X);
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

gApplication->Run(true);

}