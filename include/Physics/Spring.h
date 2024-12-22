#ifndef SPRING_H
#define SPRING_H

#include "Body.h"

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
	Body* bob;

	SpringMass(Spring* sp, Body* bob);
};


#endif
