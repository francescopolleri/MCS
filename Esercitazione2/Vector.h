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
  Vector operator-();          
  Vector operator-(Vector);    
  Vector operator+(Vector);    
  double  operator*(Vector);   
  Vector Cross(Vector);        
  Vector operator*(double);    
  double  Mod();               
  Vector Vers();               
 private:
  double m_v[3];
};

std::ostream& operator<<(std::ostream&,  Vector );
std::istream& operator>>(std::istream&, Vector &);
Vector operator*(double,  Vector );

#endif
