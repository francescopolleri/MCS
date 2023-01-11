//ESERCIZIO 9 ESAMI

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


//CLASSE COMPLEX(COMPITO 1)

#ifndef _COMPITO1
#define _COMPITO1
#include<TVector2.h>
#include<iostream>
#include<cmath>

class Complex;
std::ostream& operator<<(std::ostream& stream,const Complex&);

class Complex:public TVector2{

public:
using TVector2::TVector2;

Complex(TVector2 C):TVector2(C){}

Complex operator-(){         //non è necessario definire anche gli operatori + e - tra due complessi perchè
    Complex c=*this*(-1);    //li prendo di default dalla classe TVector2
    return c;
}

Complex Conjugate(){     
    double x=this->X();
    double y=(-1)*this->Y();
    Complex a(x,y);
    return a;
}

Complex operator*(Complex b){  
    double x1=this->X();
    double y1=this->Y();
    double x2=b.X();
    double y2=b.Y();
    Complex c(x1*x2-y1*y2,x1*y2+x2*y1);
    return c;
}

inline friend std::ostream& operator<<(std::ostream& stream,const Complex& C){ 
  if(C.Y()>0){
  stream<<"("<<C.X()<<"+"<<C.Y()<<"i)";
  return stream;
  }
  else{
  stream<<"("<<C.X()<<C.Y()<<"i)";
  return stream;
  }
}
};

int main(){
Complex a(1,1);
Complex b(2,2);
Complex c=a+b;
Complex ac=a.Conjugate();
Complex d=a*b;
Complex e=a-b;
Complex f=-a;

std::cout<<"a ="<<" "<<a<<std::endl;
std::cout<<"b ="<<" "<<b<<std::endl;
std::cout<<"c =a+b ="<<" "<<c<<std::endl;
std::cout<<"a coniugato ="<<" "<<ac<<std::endl;
std::cout<<"d =a*b ="<<" "<<d<<std::endl;
std::cout<<"e = a-b ="<<" "<<e<<std::endl;
std::cout<<"f = -a ="<<" "<<f<<std::endl;

return 0;
}
#endif


//CLASSE POLY(SIMULAZIONE ESAME)

#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

class poly:public vector<double>{
    public:

    poly(int n=3):vector<double>(n){};  //n è la dimensione
    poly(double p0=0, double p1=0, double p2=0, double p3=0):vector<double>{p0,p1,p2,p3}{};
    
    int dim(){return this->size();}
    
    poly operator+(poly b);
    
    double eval(double);    
};

poly poly::operator+(poly b){
    poly sum(b.dim());
    for (int i=0;i<b.size();i++){
        sum[i]=(*this)[i]+b[i];
    }
  return sum;
}

double poly::eval(double x){
    double sum=0;
    for(int i=0;i<size();i++){
        sum += (*this)[i]*pow(x,i);
    }
  return sum;
}

int main(){

poly a(1,2,3);
poly b(2,2,3);

poly sum(3);

sum=a+b;

cout<<sum.eval(2)<<endl;

}