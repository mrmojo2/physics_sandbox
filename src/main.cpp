#include <iostream>

#include "vector.h"

int main(){
	std::cout<<"hello simulated world"<<std::endl;
	
	Vec2 v(2,3);
	Vec2 v2(4,5);
	v = v + v2;
	std::cout<<"v: ("<<v.get_x()<<","<<v.get_y()<<")"<<std::endl;
	v = v*3;
	std::cout<<"v: ("<<v.get_x()<<","<<v.get_y()<<")"<<std::endl;
	return 0;
}
