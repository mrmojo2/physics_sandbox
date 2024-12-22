#include "Shape.h"

Circle::Circle(float radius):radius(radius){
}

Circle::~Circle(){

}

Shape* Circle::getPointer() const{
	return new Circle(this->radius);
}

ShapeType Circle::getShapeType() const {
	return CIRCLE;
}

float Circle::getMOI(float mass) const {
	return (0.5 * mass * radius * radius);
}

