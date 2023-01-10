#ifndef _MYTF1
#define _MYTF1
#include<TF1.h>
#include<iostream>
#include<vector>

class myTF1:public TF1{
using TF1::TF1;
public:
myTF1(TF1 f):TF1(f){}

double find_zero(double xmin,double xmax,int N){
    for(int i=0;i<N;i++){
        xmin=xmin-(*this)(xmin)/(this->Derivative(xmin));
      }
    return xmin;
}
};

int main(){

myTF1 f("f","pow(x,2)+2*x-4");

double start=0; 
double finish=5;
int N=1000;

double f_zero=f.find_zero(start,finish,N);

std::cout<<f_zero<<std::endl;

}
#endif