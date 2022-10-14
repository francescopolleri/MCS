#include"VectorN.h"

template<class T>
VectorN<T> VectorN<T>::operator+(const VectorN<T>& v) const{
 VectorN S(m_n);
 for(int i=0;i<this->size();i++){
    S.at(i)=this->at(i)+v.at(i);
 }
 return S;
}

template<class T>
VectorN<T> VectorN<T>::operator*(double a) const{
 VectorN<T> P(this->size());
 for(int i=0;i<this->size();i++){
    p.at(i)=this->at(i)*a;
 }
 return P;
}
