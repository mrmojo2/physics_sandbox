#include "Force.h"

Vec2 Force::getDragForce(const Particle& p, const float dc){
	Vec2 dragForce = Vec2(0,0);

	if(p.velocity.magnitudeSquared() > 0){
		float dragMagnitude = dc * p.velocity.magnitudeSquared();
		Vec2 dragDirection = p.velocity.unit() * -1;
	        
		dragForce = dragDirection * dragMagnitude;	
	}

	return dragForce;
}
