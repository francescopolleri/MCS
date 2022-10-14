#include"Complex.h"
#include<TVector2.h>
#include<iostream>
#include<cmath>

int main(){

Complex a(1,1);

Complex b(2,2);

Complex c;
c=a+b;

Complex ac=a.Coniugate();

Complex d=a*b;

Complex e=a-b;

std::cout<<"a:"<<a<<std::endl;
std::cout<<"b:"<<b<<std::endl;
std::cout<<"c=a+b:"<<c<<std::endl;
std::cout<<"a coniugato:"<<ac<<std::endl;
std::cout<<"d=a*b:"<<d<<std::endl;
std::cout<<"e=a-b:"<<e<<std::endl;


return 0;
}