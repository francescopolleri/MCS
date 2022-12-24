using namespace std;

void es14_esami(){

int nobs=30;
int n_att=15;

double p=0;
for (int i=0;i<nobs;i++){
    p += TMath::PoissonI(i,n_att);
}

cout<<"p-value = "<<1-p<<endl;
if(1-p<0.05){
    cout<<"Al 5{%} possiamo rigettare l'ipotesi nulla"<<endl;
}
else{
    cout<<"Al 5{%} di significanza non possiamo rigettare l'ipotesi nulla"<<endl;
}

for (int ns=0;ns<1000;ns++){
    double prob=0;
    for(int j=0;j<=nobs;j++){
	    prob+= TMath::PoissonI(j,ns+n_att);
    }
    if(1-prob>0.05){   //Per avere UL devo mettere prob<0.05
      cout<<"LL (95% CL)= "<<ns<<endl;  
    break;
    }
  }

for (int ns=0;ns<1000;ns++){
    double prob=0;
    for(int j=0;j<=nobs;j++){
	    prob+= TMath::PoissonI(j,ns+n_att);
    }
    if(prob<0.05){   //Per avere UL devo mettere prob<0.05
      cout<<"UL (95% CL)= "<<ns<<endl;  
    break;
    }
  } 

}
