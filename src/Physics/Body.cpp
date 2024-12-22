#include "Body.h"

#include <algorithm>

Body::Body():position(Vec2(0,0)),mass(0){}

Body::Body(const Shape& s,int x, int y, float mass):position(Vec2(x,y)),mass(mass){
	shape = s.getPointer();
	moi = shape->getMOI(mass);
	invMass = (mass == 0.0) ? 0.0 : 1/mass;
	invMOI  = (moi  == 0.0) ? 0.0 : 1/moi;
}

Body::~Body(){
	delete shape;
}

void Body::integrateLinear(float dt){
	acceleration = netForce * invMass;

	velocity += acceleration * dt;
	position += velocity * dt;

	//make netfor 0 for next frame
	netForce = Vec2(0,0);
}
void Body::integrateAngular(float dt){
	angular_acceleration = netTorque * invMOI;

	angular_velocity += angular_acceleration * dt;
	angle += angular_velocity * dt;

	//make netTorque 0 for next frame
	netTorque = 0;
}

void Body::addForce(const Vec2& f){
	netForce += f;
}
void Body::addTorque(const float t){
	netTorque += t;
}
