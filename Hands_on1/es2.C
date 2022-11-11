{
double L=0.01;
double d=0.20;

TRandom3 rnd;
rnd.SetSeed(123456789);

int ntot=100000;
int n1=0;
int n2=0;
for(int i=0;i<ntot;i++){
  double phi=2*TMath::Pi()*rnd.Rndm();
  double costheta=2*rnd.Rndm()-1;  //mi serve un intervallo tra -1 e 1
  double theta=acos(costheta);
  double alpha=d/costheta;
  if (theta>TMath::Pi()/2) continue;  //accetto solo il caso in cui theta<pi/2 cioè tolgo i fotoni che vanno all'indietro
  double x=alpha*sin(theta)*cos(phi);
  double y=alpha*sin(theta)*sin(phi);
  if(abs(x)<L/2 && abs(y)<L/2){  //mi sposto di L/2 in alto e in basso per far passare la direzione 
    n1++;                        //radiale per uno spigolo del quadrato
  }
  if(x>-L && x<0 && y>0 && y<L){
    n2++;
  }
}

double p=(double)n1/ntot;
double ep=sqrt(p*(1-p)/ntot);
cout<<"p="<<p<<"+/-"<<ep<<endl;
double p2=(double)n2/ntot;
double ep2=sqrt(p2*(1-p2)/ntot);
cout<<"p2="<<p2<<"+/-"<<ep2<<endl;
cout<<"approx d>>L: "<<L*L/(4*TMath::Pi()*d*d)  //ris analitico d>>L

}