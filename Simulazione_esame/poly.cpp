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