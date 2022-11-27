#ifndef _POLIGONO
#define _POLIGONO
#include<cmath>
#include "punto.h"
#include <vector>
#include <iostream>

using namespace std;

class poligono{

    public:
    poligono(const vector<punto>& punti):m_punti(punti){}
    poligono():poligono(vector<punto>(0)){}

    vector<double> polX(){
        vector<double> x;
        for(int i=0;i<m_punti.size();i++){
            x[i]=m_punti[i].X();
        }
      return x;
    }

    vector<double> polY(){
        vector<double> y;
        for(int i=0;i<m_punti.size();i++){
            y[i]=m_punti[i].Y();
        }
      return y;
    }

    double perimetro(){
        double p=0;
        for(int i=0;i<m_punti.size()-1;i++){
        p += sqrt( pow(m_punti[i].X()-m_punti[i+1].X(),2)+pow(m_punti[i].Y()-m_punti[i+1].Y(),2) );
      }
      p=p+sqrt(pow(m_punti[0].X()-m_punti[m_punti.size()-1].X(),2)+pow(m_punti[0].Y()-m_punti[m_punti.size()-1].Y(),2));
      return p;
    }

    void print(){
      for (auto p:m_punti){
        cout<<p.X()<<" "<<p.Y()<<endl;
      }
    }

    protected:
    vector<punto> m_punti;

};












#endif