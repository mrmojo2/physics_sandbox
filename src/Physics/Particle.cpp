#include "Particle.h"

#include <algorithm>

Particle::Particle():radius(0),position(Vec2(0,0)),mass(0){}

Particle::Particle(int x, int y, float mass):position(Vec2(x,y)),mass(mass){
	radius = std::clamp((int)mass,5,20);
	invMass = 1/mass;
}

void Particle::integrate(float dt){
	acceleration = netForce * invMass;

	velocity += acceleration * dt;
	position += velocity * dt;

	//make netfor 0 for next frame
	netForce = Vec2(0,0);
}

void Particle::addForce(const Vec2& f){
	netForce += f;
}
