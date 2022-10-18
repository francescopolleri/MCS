#ifndef _MATPOINT
#define _MATPOINT
#include<iostream>
#include<cmath>
#include"Particle.h"
#include"Vector.h"

class MatPoint:public Particle{
 public:
 using Particle::Particle;

    MatPoint(Particle p,Vector R,Vector V):Particle(p),m_R(R),m_V(V){}

    Vector R() {return m_R;}
    Vector V() {return m_V;}
   
    Vector GravField(Vector r){
        Vector w=this->R()-r;
        double A=w.Mod();
        double m=this->Mass();
        Vector GF=m*w*(1/pow(A,3));
        return GF;
    }
    

 private:
 
 Vector m_R;
 Vector m_V;
 

 

};


#endif


