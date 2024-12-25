#include "Shape.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//				Circle Shape Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////


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

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//				Polygon Shape Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////

Polygon::Polygon(std::vector<Vec2> vertices):vertices(vertices){}

Polygon::~Polygon(){}

ShapeType Polygon::getShapeType() const {
	return POLYGON;
}

float Polygon::getMOI(float mass) const {
	return 0.0;  //will implement later
}

Shape* Polygon::getPointer() const {
	return new Polygon(this->vertices);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//				BOX Shape Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////

Box::Box(float width, float height): width(width),height(height){
}

Box::~Box(){}

ShapeType Box::getShapeType() const {
	return BOX;
}

float Box::getMOI(float mass) const {
	return 0.08333333333 * mass * (width*width + height*height);
}

Shape* Box::getPointer() const {
	return new Box(width, height);
}
