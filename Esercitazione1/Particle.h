#ifndef _PARTICLE
#define _PARTICLE
#include<string>
class Particle{
 public:
  Particle(double mass=0, double charge=0,std::string pName=" "):m_mass(mass),m_charge(charge),m_pName(pName){}

  std::string ParticleName() {return m_pName;}
  double Mass() {return  m_mass;}
  double Charge(){return m_charge;}

  void Mass(double mass){
    m_mass=mass;
  }
  void Charge(double charge){
    m_charge=charge;
  }

  void ParticleName(std::string pName){
    m_pName=pName;
  }

 private:
  double m_mass;
  double m_charge;
  std::string m_pName;
};
#endif
