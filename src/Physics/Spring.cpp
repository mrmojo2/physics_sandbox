#include "Spring.h"

Spring::Spring(const Vec2& anchor, float eqb_length, float stiffness) : anchor(anchor), eqb_length(eqb_length), stiffness(stiffness){
	bob = Particle(anchor.x, anchor.y+eqb_length, 5);	
}
