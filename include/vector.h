#ifndef VECTOR_H
#define VECTOR_H

class Vec2{
private:
	float x,y;
public:
	//construcors & destructors
	Vec2();
	Vec2(float x, float y);
	Vec2(const Vec2& v);
	~Vec2() = default;

	//getters and setters
	float get_x();
	float get_y();
	void set_x(float x);
	void set_y(float y);
	
	//methods
	float magnitude() const;
	float magnitudeSquared() const;
	
	Vec2 unit() const;
	Vec2 normal() const;
	Vec2 rotate(const float angle) const;
	Vec2& normalize();
	Vec2& scale(const float n);

	Vec2 operator  + (const Vec2& v) const;
	Vec2 operator  - (const Vec2& v) const;
	Vec2 operator  * (const float s) const;
	Vec2 operator  / (const float s) const;
	Vec2 operator  - ();
	float operator * (const Vec2& v) const;

	bool operator  == (const Vec2& v) const;
	bool operator  != (const Vec2& v) const;

	//Vec2& operator += (const Vec2& v);
	//Vec2& operator -= (const Vec2& v);
	
	friend float cross(const Vec2& v1, const Vec2& v2);
};


#endif
