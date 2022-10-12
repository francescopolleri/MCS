#ifndef _PARTICELLA
#define _PARTICELLA
#include<iostream>
#include<cmath>

template <class T>
class Particella;

template <class T>
std::ostream& operator<<(std::ostream& o,const Particella<T>&);

template <class T>

class Particella{

public:
Particella(T mass=0,T charge=0):m_mass(mass),m_charge(charge){}

T mass() const {return m_mass;}
T charge() const {return m_charge;}

inline friend std::ostream& operator<<(std::ostream& o,const Particella<T>& P){
    o<<"massa="<<" "<<P.m_mass<<"; "<<"carica="<<" "<<P.m_charge;
    return o;
}


private:
T m_mass;
T m_charge;

};

#endif