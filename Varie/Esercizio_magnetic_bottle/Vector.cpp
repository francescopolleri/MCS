#include "Vector.h"
#include <cmath>
#include <iostream>


double Vector::X() const{
  return m_v[0];
}

double Vector::Y() const{
  return m_v[1];
}

double Vector::Z() const{
  return m_v[2];
}

void Vector::X(double x){
  m_v[0] = x;
}

void Vector::Y(double y){
  m_v[1] = y;
}

void Vector::Z(double z){
  m_v[2] = z;
}

Vector Vector::operator-(){
  Vector res;
  for (int i=0;i<3;i++){
    res.m_v[i] = -m_v[i];
  }
  return res;
}


Vector Vector::operator-(const Vector& b) const{
  Vector res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i] - b.m_v[i];
  }
  return res;
}

Vector Vector::operator+(const Vector& b) const{
  Vector res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i] + b.m_v[i];
  }
  return res;
}

double Vector::operator*(const Vector& b) const{
  double prod=0;
  for (int i=0;i<3;i++){
    prod += m_v[i]*b.m_v[i];
  }
  return prod;
}

Vector Vector::Cross(const Vector& b) const{
  Vector res;
  res.X(m_v[1]*b.m_v[2]-m_v[2]*b.m_v[1]);
  res.Y(m_v[2]*b.m_v[0]-m_v[0]*b.m_v[2]);
  res.Z(m_v[0]*b.m_v[1]-m_v[1]*b.m_v[0]);
  return res;
}

Vector Vector::operator*(double f) const{
  Vector res;
  for (int i=0;i<3;i++){
    res.m_v[i] = m_v[i]*f;
  }
  return res;
}

double Vector::Mod() const {
  return sqrt((*this)*(*this));
}

Vector Vector::Vers() const {
  return (*this)*(1/Mod());
}

Vector operator*(double f,  const Vector& b){
  return b*f;
}

std::ostream& operator<<(std::ostream& os,  const Vector& b){
  os << "(";
  os << b.X() << ",";
  os << b.Y() << ",";
  os << b.Z() << ")";
  return os;
}

std::istream& operator>>(std:: istream& is, Vector& b){
  double x,y,z;
  is >> x >> y >> z;
  b  = Vector(x,y,z);
  return is;
}
