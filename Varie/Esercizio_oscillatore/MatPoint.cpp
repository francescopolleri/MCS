#include "MatPoint.h"
#include "Vector.h"
#include <cmath>

Vector MatPoint::R(){
  return m_r;
}

Vector MatPoint::V(){
  return m_v;
}

void MatPoint::R(Vector r){
  m_r = r;
}

void MatPoint::V(Vector v){
  m_v = v;
}

Vector MatPoint::GravField(Vector r){
  // F = -G m m_prova/(r-r0)^2 vers(r-r0)
  // a = F/m_prova = -G m /(r-r0)^2 vers(r-r0)


  Vector r0   = m_r;
  Vector dist = r-r0;

  Vector val  = -consts::G*Mass()/pow(dist.Mod(),2)*dist.Vers();

  return val;
  
  
}
