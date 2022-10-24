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
  m_t=t0;
}

double OdeSolver::T(){
  return      m_t;
}

void OdeSolver::Step(double h){
  m_h = h;
}

double OdeSolver::Step(){
  return   m_h;
}

double OdeSolver::GetMomentum(unsigned int i=0){
  double L;
   //L=(m_p[i].R()).Mod()*(m_p[i].V()).Mod()*m_p[i].Mass();
   L=(m_p[i].R().Cross(m_p[i].V())*m_p[i].Mass()).Mod();
  return L;
}


Vector OdeSolver::m_eqDiff(unsigned int i, double t, vector<MatPoint> p){
Vector a;
for(int j=0;j!=i && j<p.size();j++){
a = a + fInternal(i,j,t,p)*(1/(p[i].Mass()));
}
return a;
}

//Da implementare a cura dello studente
void OdeSolver::Solve(){

  if (m_method=="Eulero"){
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
    
  } else if(m_method=="VerletV"){
    vector<Vector> f1(m_p.size());
    
    auto mp(m_p);
    
    for(unsigned int i=0;i<m_p.size();i++){
     f1[i] = m_eqDiff(i,m_t,mp);
    }

    for(unsigned int i=0;i<m_p.size();i++){ 
    m_p[i].R(m_p[i].R() + m_h*m_p[i].V() + 0.5*pow(m_h,2)*m_eqDiff(i,m_t,m_p));
    m_p[i].V(m_p[i].V() + 0.5*m_h*(m_eqDiff(i,m_t,m_p)+f1[i]));
    }

  }
  m_t += m_h;

}

