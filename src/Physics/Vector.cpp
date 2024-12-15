#include "Vector.h"
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////
//	Constructors
/////////////////////////////////////////////////////////////////////////////////////////////////
Vec2::Vec2(float x, float y):x(x),y(y){
}

Vec2::Vec2():x(0.0),y(0.0){
}

Vec2::Vec2(const Vec2& v):x(v.x),y(v.y){
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//	methods
/////////////////////////////////////////////////////////////////////////////////////////////////
float Vec2::magnitude() const {
	return sqrtf(x * x + y * y);
}
float Vec2::magnitudeSquared() const {
	return (x * x + y * y);
}


Vec2 Vec2::unit() const {
	float l = magnitude();
	if(l == 0){
		return Vec2(0,0);
	}else{
		return Vec2(x/l, y/l);
	}
}
Vec2 Vec2::normal() const {
	Vec2 result(this->y,-this->x);
	return result.normalize();
}
Vec2 Vec2::rotate(const float angle) const {
	return Vec2(
		x*cos(angle) - y*sin(angle),
		x*sin(angle) + y*cos(angle)
	);
}
Vec2& Vec2::normalize(){
	float length = this->magnitude();
	if(length != 0.0){
		x /= length;
		y /= length;
	}
	return *this;
}
Vec2& Vec2::scale(const float n) {
	x*=n;
	y*=n;
	return *this;
}


Vec2 Vec2::operator + (const Vec2& v) const {
	return Vec2(x+v.x,y+v.y);	
}
Vec2 Vec2::operator - (const Vec2& v) const {
	return Vec2(x-v.x,y-v.y);
}
Vec2 Vec2::operator*(const float scale) const {
	return Vec2(x*scale, y*scale);
}
Vec2 Vec2::operator/(const float scale) const {
	return Vec2(x/scale, y/scale);
}
Vec2 Vec2::operator - (){
	return Vec2(-1 * x, -1 * y);
}
float Vec2::operator*(const Vec2& v) const {
	return (x * v.x + y * v.y);
}



bool Vec2::operator == (const Vec2& v) const {
	return (x==v.x) && (y==v.y);
}
bool Vec2::operator != (const Vec2& v) const {
	return (x!=v.x) || (y!=v.y);
}


Vec2& Vec2::operator += (const Vec2& v){
	x+=v.x;
	y+=v.y;
	return *this;
}
Vec2& Vec2::operator -= (const Vec2& v){
	x-=v.x;
	y-=v.y;
	return *this;
}

float cross(const Vec2& v1, const Vec2& v2) {
  	return (v1.x * v2.y - v1.y * v2.x);
}
