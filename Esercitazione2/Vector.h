#ifndef _VECTOR
#define _VECTOR

#include <iostream>
class Vector{
 public:
  Vector(double x=0,double y=0,double z=0):m_v{x,y,z}{}
  double  X() const;
  void    X(double);
  double  Y() const;
  void    Y(double);
  double  Z() const;
  void    Z(double);
  Vector operator-();                        // - unario
  Vector operator-(const Vector&) const;    // - binario
  Vector operator+(const Vector&) const;    // + binario     
  double  operator*(const Vector&) const;    // prod. scalare 
  Vector Cross(const Vector&) const;        // prod. vettore 
  Vector operator*(double) const;            // molt. per scalare
  double  Mod() const;                        // modulo  (da impl.)
  Vector Vers() const;                       // versore (da impl.)
 private:
  double m_v[3];
};

std::ostream& operator<<(std::ostream&, const Vector & );
std::istream& operator>>(std::istream&, Vector &);
Vector operator*(double,const Vector& );

#endif
