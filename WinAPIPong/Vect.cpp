#include "Vect.h"
class Vect
{
public:
	float x, y;

	Vect() : x(0.0f), y(0.0f) {}
	Vect(float x, float y) : x(x), y(y) {}

	Vect operator+(Vect const& rhs)
	{
		return Vect(x + rhs.x, y + rhs.y);
	}

	Vect& operator+=(Vect const& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vect operator*(float rhs)
	{
		return Vect(x * rhs, y * rhs);
	}

};