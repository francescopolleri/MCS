#ifndef _PUNTOMATERIALE
#define _PUNTOMATERIALE
#include<iostream>
#include<cmath>
#include"Particella.h"
#include"Vector.h"

template<class T>

class PuntoMateriale{

public:
PuntoMateriale(T mass,Vector<T> r,Vector<T> v):m_mass(mass),m_r(r),m_v(v){}

Vector<T> position()  {return m_r;}
Vector<T> velocity()  {return m_v;}
T mass() {return m_mass;}

Vector<T> ForzaG(T M,Vector<T> r){
Vector<T> w=this->position()+(-r);
double K=w.modulo();
double N=this->mass();
Vector<double> G=M*N*w*(1/pow(K,3));
return G;
};

Vector<T> CampoG(Vector<T> r){
Vector<T> w=this->position()+(-r);
double K=w.modulo();
double N=this->mass();
Vector<double> G=N*w*(1/pow(K,3));
return G;
};

private:
Vector<T> m_v;
Vector<T> m_r;
T m_mass;

};
#endif