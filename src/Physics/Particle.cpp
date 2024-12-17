#include "Particle.h"


Particle::Particle(int x, int y, float mass):position(Vec2(x,y)),mass(mass){
	radius = 5 * mass/10;
}

void Particle::integrate(float dt){
	acceleration = netForce/mass;

	velocity += acceleration * dt;
	position += velocity * dt;

	//make netfor 0 for next frame
	netForce = Vec2(0,0);
}

void Particle::addForce(const Vec2& f){
	netForce += f;
}
