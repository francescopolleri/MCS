#include<iostream>
#include<cmath>
#include"Vector.h"
#include"Particella.h"
#include"PuntoMateriale.h"

int main(){

//Particella<double> p1(25,0);
//double M=p1.mass();
Vector<double> a(1,2,3);
Vector<double> b(1,1,1);
double M=10;

PuntoMateriale<double> Q(b,a);

Vector<double> f=Q.R();


PuntoMateriale<double> P(a,b);

Vector<double> vP=P.V();
Vector<double> rP=P.R();
//double M=P.mass();

Vector<double> G=P.CampoG(M,f);

std::cout<<"Posizione di P:"<<rP<<";"<<"velocità di P:"<<vP<<std::endl;
//std::cout<<"L'attrazione gravitazionale in unità di G prodotta da P su p1 è:"<<F<<std::endl;
std::cout<<"Il campo gravitazionale per unità di G prodotto da P su p1 è:"<<G<<std::endl;
return 0;
}