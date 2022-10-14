#ifndef _VECTORDOUBLE
#define _VECTORDOUBLE
#include<iostream>

//template <class T>

class Vector; 

Vector operator*(double, Vector);
std::ostream& operator<<(std::ostream& stream,Vector V);
std::istream& operator>>(std::istream& stream,Vector& V);

class Vector{

public:

Vector(double x=0, double y=0, double z=0):m_v{x,y,z}{}

double X();
double Y();
double Z();
void X(double);
void Y(double);
void Z(double);

Vector operator+(Vector);
Vector operator-();
Vector operator*(double);

Vector versore(double);
void Print();
double modulo();
double p_scalare(Vector);
Vector p_vettore(Vector);

inline friend std::istream& operator>>(std::istream& i,Vector& V){
    double x,y,z;
    i>>x>>y>>z;
    V.m_v[0]=x;
    V.m_v[1]=y;    
    V.m_v[2]=z;
    return i;
}


private:

double m_v[3];

};
#endif