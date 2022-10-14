#include "Vector_double.h"
#include<cmath>

double Vector::X(){   //getter
return m_v[0];
}

double Vector::Y(){
return m_v[1];    
}

double Vector::Z(){
return m_v[2];
}

void Vector::X(double x){   //setter
m_v[0]=x;    
}
void Vector::Y(double y){
m_v[0]=y;   
}
void Vector::Z(double z){
m_v[0]=z;    
}

Vector Vector::operator+(Vector b){
Vector sum;
for(int i=0;i<3;i++)
    sum.m_v[i]=m_v[i]+b.m_v[i];
    return sum;
}

Vector Vector::operator-(){
    Vector dif;
    for(int i=0;i<3;i++)
    dif.m_v[i]=-m_v[i];
    return dif;
}

Vector operator*(double a, Vector b){
    return b*a;
}
Vector Vector::operator*(double a){
    Vector v;
    for(int i=0;i<3;i++)
    v.m_v[i]=m_v[i]*a;
    return v;
}

void Vector::Print() {
    std::cout<<"("<<m_v[0]<<","<<m_v[1]<<","<<m_v[2]<<")"<<std::endl;
    return;
}

double Vector::modulo(){
    double M=sqrt(pow(m_v[0],2)+pow(m_v[1],2)+pow(m_v[2],2));
    return M;
}

Vector Vector::versore(double M){
    Vector v;
    for(int i=0;i<3;i++)
    v.m_v[i]=m_v[i]/M;
    return v;
}

double Vector::p_scalare(Vector a){
    double p;
    p=a.X()*m_v[0]+a.Y()*m_v[1]+a.Z()*m_v[2];
    return p;
}

Vector Vector::p_vettore(Vector b){
    Vector v;
    v.m_v[0]=m_v[1]*b.m_v[2]-m_v[2]*b.m_v[1];
    v.m_v[1]=m_v[2]*b.m_v[0]-m_v[0]*b.m_v[2];
    v.m_v[2]=m_v[0]*b.m_v[1]-m_v[1]*b.m_v[0];
    return v;
}

std::ostream& operator<<(std::ostream& stream,Vector V){
    stream << "("<<V.X()<<","<<V.Y()<<","<<V.Z()<< ")";
    return stream;
}

/*
std::istream& operator>>(std::istream& stream,Vector& V){
    double x,y,z;
    stream>>x>>y>>z;
    V.X(x);
    V.Y(y);
    V.Z(z);
    return stream;
}
*/
