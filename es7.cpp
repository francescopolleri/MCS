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

PuntoMateriale<double> Q(25,b,a);
double M=Q.mass();
Vector<double> f=Q.position();


PuntoMateriale<double> P(10,a,b);

Vector<double> vP=P.velocity();
Vector<double> rP=P.position();
//double M=P.mass();

Vector<double> F=P.ForzaG(M,f);
Vector<double> G=P.CampoG(f);

std::cout<<"Posizione di P:"<<rP<<";"<<"velocità di P:"<<vP<<std::endl;
std::cout<<"L'attrazione gravitazionale in unità di G prodotta da P su p1 è:"<<F<<std::endl;
std::cout<<"Il campo gravitazionale per unità di G prodotto da P su p1 è:"<<G<<std::endl;
return 0;
}