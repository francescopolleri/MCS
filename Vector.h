#ifndef _VECTOR
#define _VECTOR
#include<iostream>
#include<cmath>

template <class T>

class Vector; 

template <class T>
Vector<T> operator*(T a, Vector<T> v){
    return v*a;
};
template <class T>
std::ostream& operator<<(std::ostream& stream,const Vector<T>&);
template <class T>
std::istream& operator>>(std::istream& stream,Vector<T>&);

template <class T>
class Vector{

public:

Vector(T x=0, T y=0, T z=0):m_v{x,y,z}{}

T X(){return m_v[0];};
T Y(){return m_v[1];};
T Z(){return m_v[2];};
void X(T x){m_v[0]=x;};
void Y(T y){m_v[1]=y;};
void Z(T z){m_v[2]=z;};

Vector<T> operator+(Vector<T> v){
    Vector<T> S;
    for(int i=0;i<3;i++){
      S.m_v[i]=m_v[i]+v.m_v[i];
    }
    return S;
};
Vector<T> operator-(){
    Vector<T> d;
    for(int i=0;i<3;i++){
    d.m_v[i]=-m_v[i];
    }
    return d;
};
Vector operator*(T a){
    Vector<T> v;
    for(int i=0;i<3;i++){
     v.m_v[i]=m_v[i]*a;
    } 
  return v;
};

Vector versore(T M){
    Vector<T> v;
    for(int i=0;i<3;i++){
        v.m_v[i]=m_v[i]/this->modulo();
    }
    return v;
};

void Print();

T modulo(){
    T M;
    M=sqrt(pow(m_v[0],2)+pow(m_v[1],2)+pow(m_v[2],2));
    return M;
};

T p_scalare(Vector<T> v){
    T p;
    p=v.m_v[0]*m_v[0]+v.m_v[1]*m_v[1]+v.m_v[2]*m_v[2];
    return p;
};

Vector p_vettore(Vector<T> b){
    Vector<T> v;
    v.m_v[0]=m_v[1]*b.m_v[2]-m_v[2]*b.m_v[1];
    v.m_v[1]=m_v[2]*b.m_v[0]-m_v[0]*b.m_v[2];
    v.m_v[2]=m_v[0]*b.m_v[1]-m_v[1]*b.m_v[0];
    return v;
};

inline friend std::ostream& operator<<(std::ostream& o,const Vector<T>& v){
    o<<"("<<v.m_v[0]<<","<<v.m_v[1]<<","<<v.m_v[2]<<")";
    return o;
}

inline friend std::istream& operator>>(std::istream& i,Vector<T>& V){
    T x;
    T y;
    T z;
    i>>x>>y>>z;
    V.m_v[0]=x;
    V.m_v[1]=y;    
    V.m_v[2]=z;
    return i;
}


private:

T m_v[3];

};
#endif