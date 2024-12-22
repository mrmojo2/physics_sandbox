#ifndef SHAPE_H
#define SHAPE_H

enum ShapeType {
	CIRCLE,
	POLYGON,
	BOX
};

class Shape{
public:	
	virtual ~Shape() = default;
	virtual ShapeType getShapeType() const = 0;
	virtual Shape*    getPointer() const = 0;
	virtual float 	  getMOI(float mass) const = 0;
	
};

class Circle:public Shape{
public:
	float radius;

	Circle(float radius);	
	~Circle();
	ShapeType getShapeType() const;
	Shape*    getPointer() const;
	float getMOI(float mass) const;
};

class Polygon:public Shape{
//
};



#endif
