#ifndef _TRIANGOLO
#define _TRIANGOLO
#include<cmath>
#include "poligono.h"
#include "punto.h"

using namespace std;

class triangolo: public poligono{
    public:
    using poligono::poligono;

    triangolo(double a, double b, double th):poligono(){
    m_punti.push_back(punto(0,0));
    m_punti.push_back(punto(a,0));
    m_punti.push_back(punto(b*cos(th),b*sin(th)));
  }

  double area(){
    return (m_punti[1].X()*m_punti[2].Y())/2 ;
  }
};







#endif