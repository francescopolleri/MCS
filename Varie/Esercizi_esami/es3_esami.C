using namespace std;

void es3_esami(){

double x;
ifstream file("Dati_spettrometro.dat");

TH1D *h=new TH1D("h","",60,0.,0.);
while(file>>x){
   h->Fill(x);
}

h->Draw();



gApplication->Run(true);





}