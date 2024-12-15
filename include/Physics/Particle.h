#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"

class Particle{
public:
	static int radius;
	
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
	float mass;
	
	Particle(int x, int y, float mass);
};

#endif
