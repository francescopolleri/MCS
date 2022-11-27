#include "Vector.h"
#include "OdeSolver.h"
#include<functional>
#include<cmath>

void OdeSolver::SetMatPoint(MatPoint tmp){
  m_p.push_back(tmp);
}

vector<MatPoint> OdeSolver::GetMatPoints(){
  return m_p;
}

MatPoint OdeSolver::GetMatPoint(unsigned int i){
  return m_p[i];
}

unsigned int OdeSolver::N(){
  return m_p.size();
}

void OdeSolver::T(double t0){
  m_t = t0;
}

double OdeSolver::T(){
  return  m_t;
}

void OdeSolver::Step(double h){
  m_h = h;
}

double OdeSolver::Step(){
  return   m_h;
}

Vector OdeSolver::m_eqDiff(unsigned int i, double t, vector<MatPoint> p){
Vector a;
a = a + fExternal(i,t,p)*(1/p[0].Mass());
for(int j=0;j!=i && j<p.size();j++){
a = a + fInternal(i,j,t,p)*(1/(p[i].Mass()));
}
return a;
}

//Da implementare a cura dello studente
void OdeSolver::Solve(){

  if (m_method=="ELR"){
    vector<Vector>  k1(m_p.size());
    vector<Vector>  w1(m_p.size());
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() + w1[i]);
    }

  } else if (m_method=="RK2"){
    // STEP 5 implementare Runge Kutta al secondo ordine
    vector<Vector>  k1(m_p.size());
    vector<Vector>  w1(m_p.size());
    vector<Vector>  k2(m_p.size());
    vector<Vector>  w2(m_p.size());
    vector<MatPoint> matp=m_p;
    
    for (unsigned int i=0;i<m_p.size();i++){
     k1[i] = m_h*m_p[i].V();
     w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }

    for (unsigned int i=0;i<m_p.size();i++){
     matp[i].R(m_p[i].R()+k1[i]*0.5);
     matp[i].V(m_p[i].V()+w1[i]*0.5);
    }

    for (unsigned int i=0;i<m_p.size();i++){
     k2[i] = m_h*(m_p[i].V()+w1[i]*0.5);
     w2[i] = m_h*m_eqDiff(i,m_t,matp);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k2[i]);
      m_p[i].V(m_p[i].V() + w2[i]);
    }
    
  } else if(m_method=="VV"){
    vector<Vector> f1(m_p.size());
    
    auto mp(m_p);

    for(unsigned int i=0;i<m_p.size();i++){ 
    m_p[i].R(m_p[i].R() + m_h*m_p[i].V() + 0.5*pow(m_h,2)*m_eqDiff(i,m_t,mp));  //E' importante che qui ci sia mp
    }
    for(unsigned int i=0;i<m_p.size();i++){
      auto An = m_eqDiff(i,m_t,mp);
      auto An1 = m_eqDiff(i,m_t,m_p);
      m_p[i].V(m_p[i].V()+m_h/2*(An+An1));
    }

  } else if(m_method=="RK4"){
    vector<Vector>  k1(m_p.size());
    vector<Vector>  w1(m_p.size());
    vector<Vector>  k2(m_p.size());
    vector<Vector>  w2(m_p.size());
    vector<Vector>  k3(m_p.size());
    vector<Vector>  w3(m_p.size());
    vector<Vector>  k4(m_p.size());
    vector<Vector>  w4(m_p.size());

    for (unsigned int i=0;i<m_p.size();i++){
     k1[i] = m_h*m_p[i].V();
     w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }
    vector<MatPoint> matp1=m_p;
    for (unsigned int i=0;i<m_p.size();i++){
     matp1[i].R(m_p[i].R()+k1[i]*0.5);
     matp1[i].V(m_p[i].V()+w1[i]*0.5);
    }

    for (unsigned int i=0;i<m_p.size();i++){
     k2[i] = m_h*matp1[i].V();
     w2[i] = m_h*m_eqDiff(i,m_t+m_h/2,matp1);
    }
    vector<MatPoint> matp2=matp1;
    for (unsigned int i=0;i<m_p.size();i++){
      matp2[i].R(m_p[i].R() + k2[i]*0.5);
      matp2[i].V(m_p[i].V() + w2[i]*0.5);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      k3[i]=m_h*matp2[i].V();
      w3[i]=m_h*m_eqDiff(i,m_t+m_h/2,matp2);
    }
    vector<MatPoint> matp3=matp2;
    for (unsigned int i=0;i<m_p.size();i++){
      matp3[i].R(m_p[i].R()+k3[i]);
      matp3[i].V(m_p[i].V()+w3[i]);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      k4[i]=m_h*matp3[i].V();
      w4[i]=m_h*m_eqDiff(i,m_t+m_h/2,matp3);
    }
    
    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R()+k1[i]*(1/6.)+k2[i]*(1/3.)+k3[i]*(1/3.)+k4[i]*(1/6.));
      m_p[i].V(m_p[i].V()+w1[i]*(1/6.)+w2[i]*(1/3.)+w3[i]*(1/3.)+w4[i]*(1/6.));
    }

  }
  m_t += m_h;

}

