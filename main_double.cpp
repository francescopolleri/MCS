#include "Vector_double.h"
#include<iostream>

int main(){
double alpha=3.2;
Vector k(2,0,0);
Vector a(1,1,1);
Vector c(2,2,2);
Vector v=c*alpha;
Vector w=alpha*c;
Vector d= a+c;
double M=a.modulo();
Vector vk=k.versore(k.modulo());
double ps=a.p_scalare(c);
Vector pv=a.p_vettore(c);

std::cout<<d.X()<<std::endl;
std::cout<<v.X()<<std::endl;
v.Print();
w.Print();
std::cout<<"v="<<v<<std::endl;
std::cout<<"il modulo del vettore a è:"<<M<<std::endl;
k.Print();
vk.Print();
std::cout<<"a scalare c vale:"<<ps<<std::endl;
pv.Print();

return 0;
}
