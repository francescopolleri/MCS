#ifndef _ELECTRON
#define _ELECTRON
#include"Particle.h"
#include<iostream>

class Electron:public Particle{
public:
using Particle::Particle;

Electron ():Particle(9.1,-1.6,"elettrone"){};

};

#endif