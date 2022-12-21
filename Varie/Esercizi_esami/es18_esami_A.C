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

gApplication->Run(true);
}