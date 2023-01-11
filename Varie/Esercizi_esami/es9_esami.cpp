#ifndef _MYTF1
#define _MYTF1
#include<TF1.h>
#include<iostream>

class myTF1:public TF1{
using TF1::TF1;
public:
myTF1(TF1 f):TF1(f){}

double find_zeroNR(double xmin,double xmax,int N){
    for(int i=0;i<N;i++){
        xmin=xmin-(*this)(xmin)/(this->Derivative(xmin));
      }
    return xmin;
}

double find_zeroBS(double a,double b,double eps){
    double xm=(a+b)/2;
    while((b-a)>eps){
      double fm=(*this)(xm);
      double fmin=(*this)(a);
      if(fm*fmin <= 0){
        b=xm;
      }
      else{
        a=xm;
      }
      xm=(a+b)/2;
    }
  return xm;
}
};

int main(){

myTF1 f("f","pow(x,2)+2*x-4");

double start=0; 
double finish=5;
int N=1000;

double f_zeroNR=f.find_zeroNR(start,finish,N);
double f_zeroBS=f.find_zeroBS(start,finish,0.0001);

double ris=sqrt(5)-1;

std::cout<<f_zeroNR<<std::endl;
std::cout<<f_zeroBS<<std::endl;
std::cout<<ris<<std::endl;
}
#endif