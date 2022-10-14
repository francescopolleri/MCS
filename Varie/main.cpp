#include "Vector.h"
#include<iostream>

int main(){
double alpha=3.2;
Vector<double> k(2,9,0);
Vector<double> a(1,1,1);
Vector<double> c(2,2,2);
Vector<double> v=c*alpha;
Vector<double> w=alpha*c;
Vector<double> d= a+c;
double M=a.modulo();
Vector<double> vk=k.versore(k.modulo());
double ps=a.p_scalare(c);
Vector<double> pv=a.p_vettore(c);

std::cout<<d.X()<<std::endl;
std::cout<<v.X()<<std::endl;
std::cout<<"v="<<v<<std::endl;
std::cout<<"il modulo del vettore a è:"<<M<<std::endl;
std::cout<<"a scalare c vale:"<<ps<<std::endl;
std::cout<<pv<<std::endl;
std::cout<<vk<<std::endl;


return 0;
}
