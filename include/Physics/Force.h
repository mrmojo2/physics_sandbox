#ifndef FORCE_H
#define FORCE_H

#include "Particle.h"
#include "Vector.h"

class Force{
public:
	static Vec2 getDragForce(const Particle& p, const float drag_coefficient);
};

#endif
