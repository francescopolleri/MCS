#include"Complex.h"
#include<TVector2.h>
#include<iostream>
#include<cmath>

int main(){

Complex a(1,1);

Complex b(2,2);

Complex c=a+b;

Complex ac=a.Conjugate();

Complex d=a*b;

Complex e=a-b;

Complex f=-a;

std::cout<<"a="<<a<<std::endl;
std::cout<<"b="<<b<<std::endl;
std::cout<<"c=a+b="<<c<<std::endl;
std::cout<<"a coniugato="<<ac<<std::endl;
std::cout<<"d=a*b="<<d<<std::endl;
std::cout<<"e=a-b="<<e<<std::endl;
std::cout<<"f=-a="<<f<<std::endl;

return 0;
}