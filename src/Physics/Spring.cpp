#include "Spring.h"

Spring::Spring(Vec2* anchor, float eqb_length, float stiffness) : anchor(anchor), eqb_length(eqb_length), stiffness(stiffness){	
}



SpringMass::SpringMass(Spring* sp, Body* bob):sp(sp),bob(bob){
}
