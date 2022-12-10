#include<iostream>
#include<cmath>

class Compatibility;
std::ostream& operator<<(std::ostream& o, Compatibility&);

class Compatibility{

public:

Compatibility(double a=0,double b=0,double ea=0,double eb=0):m_a(a),m_b(b),m_ea(ea),m_eb(eb){}

double Val1(){return m_a;}
double Val2(){return m_b;}
double sig1(){return m_ea;}
double sig2(){return m_eb;}

double Comp(){
    return abs(m_a-m_b)-3*sqrt(pow(m_ea,2)+pow(m_eb,2));
}

double BestValue(){
    if (this->Comp()<0){
     return (m_a/pow(m_ea,2)+m_b/pow(m_eb,2))/(1/pow(m_ea,2)+1/pow(m_eb,2));
   }
   else{
    return 0;
   }
}

double BestValueError(){
    if (this->Comp()<0){
      return pow(m_ea*m_eb,2)/(pow(m_ea,2)+pow(m_eb,2));
    }
    else{
        return 0;
    }
}

inline friend std::ostream& operator<<(std:: ostream& o, Compatibility& C){
    if(C.Comp()<0){
        o<<"Valori compatibili";
    }else{
        o<<"Valori NON compatibili";
    }
        return o;
}

private:

double m_a,m_b,m_ea,m_eb;

};