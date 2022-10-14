#include "Electron.h"
#include "Particle.h"
#include "MatPoint.h"
#include <iostream>

using namespace std;

int main(){
  
  //Costruzione da particella "nota"
  MatPoint p(Electron(),Vector(1,0,0),Vector(2,0,0));
  cout << p.ParticleName() << endl;
  cout << p.Mass() << " " << p.Charge() << endl;
  cout << p.R() << endl;
  cout << p.V() << endl;
  
  //Costruzione punto materiale generico
  Particle P(1,0,"neutrino");
  MatPoint pm(P,Vector(1,0,0),Vector(1,1,1));
  cout << pm.ParticleName() << endl;
  cout << pm.Mass() << " " << pm.Charge() << endl;
  cout << pm.R() << endl;
  cout << pm.V() << endl;


  // Calcolo Campo Gravitazionale
  Vector v = pm.GravField(Vector(1.5,0,0));
  if (v.X()!=-4){
    cout << "Errore campo vettoriale:" << endl;
  }
  else{
    cout << " valore aspettato -4, ottenuto " << v.X() << endl;
  }
  
  
}
