#include "Force.h"

#include <iostream>
#include <algorithm>

Vec2 Force::getDragForce(const Body& p, const float dc){
	Vec2 dragForce = Vec2(0,0);

	if(p.velocity.magnitudeSquared() > 0){
		float dragMagnitude = dc * p.velocity.magnitudeSquared();
		Vec2 dragDirection = p.velocity.unit() * -1;
	        
		dragForce = dragDirection * dragMagnitude;	
	}

	return dragForce;
}

Vec2 Force::getFrictionalForce(const Body& p, const float fc){
	Vec2 frictionalForce = Vec2(0,0);
	
	Vec2 direction = p.velocity.unit() * -1;
	float magnitude = fc * p.mass;			//for top down view on flat surface
	frictionalForce = direction * magnitude;

	return frictionalForce;
}

Vec2 Force::getGravitationalForce(const Body& p1, const Body& p2, float G, float min_distance, float max_distance){
	Vec2 gravitationalForce = Vec2(0,0);

	float distanceSquared = (p1.position - p2.position).magnitudeSquared();
	distanceSquared = std::clamp(distanceSquared, min_distance, max_distance);
	if(distanceSquared > 0){
		float magnitude = (G * p1.mass * p2.mass)/distanceSquared;
		Vec2 direction = (p1.position - p2.position).unit();
		gravitationalForce = direction * magnitude;
	}

	return gravitationalForce;
}

Vec2 Force::getSpringForce(const SpringMass& sm){
	Vec2 springForce = Vec2(0,0);
	
	Vec2 l = sm.bob->position - *(sm.sp->anchor);

	Vec2 direction = l.unit();
	double magnitude = sm.sp->stiffness * (sm.sp->eqb_length-l.magnitude());
	springForce = direction * magnitude;
	
	return springForce;	
}
