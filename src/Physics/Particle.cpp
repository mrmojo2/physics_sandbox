#include "Particle.h"

int Particle::radius = 10;

Particle::Particle(int x, int y, float mass):mass(mass),position(Vec2(x,y)){}
