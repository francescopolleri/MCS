#ifndef _MATPOINT
#define _MATPOINT
#include "Particle.h"
#include "Vector.h"

namespace consts{
  const double c = 299792458;
  const double G = 1;
};

class MatPoint: public Particle{
 public:
  MatPoint(Particle p=Particle(), Vector r=Vector(), Vector v=Vector()):Particle(p),m_r(r),m_v(v){}
  MatPoint(double massa, double carica, Vector r, Vector v):MatPoint(Particle(massa,carica),r,v){}

  Vector R();    
  Vector V();
  void   R(Vector);
  void   V(Vector);

  Vector GravField(Vector);
  
 private:
  Vector m_r;
  Vector m_v;
};

#endif
