#ifndef FORCE_H
#define FORCE_H

#include "Body.h"
#include "Vector.h"
#include "Spring.h"

class Force{
public:
	static Vec2 getDragForce(const Body& p, float drag_coefficient);
	static Vec2 getFrictionalForce(const Body& p, float friction_coefficient);
	static Vec2 getGravitationalForce(const Body& p1, const Body& p2, float gravitational_const, float min_distance, float max_distance);
	static Vec2 getSpringForce(const SpringMass& sm);
};

#endif
