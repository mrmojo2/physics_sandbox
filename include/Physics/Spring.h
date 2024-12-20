#ifndef SPRING_H
#define SPRING_H

#include "Particle.h"

class Spring{
public:
	Vec2 *anchor;
	float eqb_length;
	float stiffness;

	Spring(Vec2* anchor, float eqb_length, float stiffness);
};

class SpringMass{
public:
	Spring* sp;
	Particle* bob;

	SpringMass(Spring* sp, Particle* bob);
};


#endif
