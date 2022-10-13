#ifndef _PUNTOMATERIALE
#define _PUNTOMATERIALE
#include<iostream>
#include<cmath>
#include"Particella.h"
#include"Vector.h"

template<class T>

class PuntoMateriale{

public:
PuntoMateriale(Vector<T> r,Vector<T> v):m_r(r),m_v(v){}

Vector<T> R()  {return m_r;}
Vector<T> V()  {return m_v;}

Vector<T> ForzaG(T M,Vector<T> r){
Vector<T> w=this->position()+(-r);
double K=w.modulo();
double N=this->mass();
Vector<double> G=M*N*w*(1/pow(K,3));
return G;
};

Vector<T> CampoG(T M,Vector<T> r){
Vector<T> w=this->R()+(-r);
double K=w.modulo();
Vector<double> G=M*w*(1/pow(K,3));
return G;
};

private:
Vector<T> m_v;
Vector<T> m_r;
T m_mass;

};
#endif