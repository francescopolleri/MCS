#ifndef _ELECTRON
#define _ELECTRON
#include"Particle.h"
#include<iostream>

class Electron:public Particle{
public:
using Particle::Particle;

Electron ():Particle(9.1e-31,-1.6e-19,"elettrone"){};

};

#endif