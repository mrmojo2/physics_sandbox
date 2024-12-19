#ifndef SPRING_H
#define SPRING_H

#include "Particle.h"

class Spring{
public:
	Vec2 anchor;
	float eqb_length;
	float stiffness;
	Particle bob;

	Spring(const Vec2& anchor, float eqb_length, float stiffness);
};


#endif
