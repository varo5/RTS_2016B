#include "aeCoreStd.h"
#include "Vector2.h"

namespace aeCore
{
	/************************************************************************************************************************/
	/* Constructors                                                        													*/
	/************************************************************************************************************************/

	aeVector2::aeVector2() : x(0), y(0)
	{
	}

	aeVector2::aeVector2(const aeVector2 & V)
	{
		*this = V;
	}

	aeVector2::aeVector2(float X, float Y) : x(X), y(Y)
	{
	}

	aeVector2::~aeVector2()
	{
	}

	/***********************************************************************************************************************/
	/* Implementation of arithmetic operators						          												*/
	/***********************************************************************************************************************/
	aeVector2  aeVector2::operator*(aeVector2& V) 
	{
		return aeVector2(x * V.x, y * V.y);
	}
	aeVector2  aeVector2::operator+(aeVector2& V) 
	{
		return aeVector2(x + V.x, y + V.y);
	}
	aeVector2  aeVector2::operator-(aeVector2& V)
	{
		return aeVector2(x - V.x, y - V.y);
	}
	aeVector2  aeVector2::operator/(aeVector2& V) 
	{
		return aeVector2(x / V.x, y / V.y);
	}
	aeVector2  aeVector2::operator*(float S) 
	{
		return aeVector2(x * S, y * S);
	}
	aeVector2  aeVector2::operator/(float S) 
	{
		return aeVector2(x / S, y / S);
	}
	///Is the same as using the dot product function.
	float  aeVector2::operator|(aeVector2& V)
	{
		return x*V.x + y*V.y;
	}
	///Is the same as using the cross product function.
	float  aeVector2::operator^(aeVector2& V)
	{
		return x*V.y - y*V.x;
	}

	/***********************************************************************************************************************/
	/* Implementation of compound assignment operators			               												*/
	/***********************************************************************************************************************/
	aeVector2&  aeVector2::operator+=(aeVector2& V) {
		x += V.x; y += V.y;
		return *this;
	}
	aeVector2&  aeVector2::operator-=(aeVector2& V) {
		x -= V.x; y -= V.y;
		return *this;
	}
	aeVector2&  aeVector2::operator*=(aeVector2& V) {
		x *= V.x; y *= V.y;
		return *this;
	}
	aeVector2&  aeVector2::operator/=(aeVector2& V) {
		x /= V.x; y /= V.y;
		return *this;
	}
	aeVector2&  aeVector2::operator*=(float S) {
		x *= S; y *= S;
		return *this;
	}
	aeVector2&  aeVector2::operator/=(float S) {
		x /= S; y /= S;
		return *this;
	}

	bool aeVector2::operator==(aeVector2 & V)
	{
		return x == V.x && y == V.y;
	}

	bool aeVector2::operator!=(aeVector2 & V)
	{
		return x != V.x || y != V.y;
	}

	/************************************************************************************************************************/
	/* Functions implementation                                            													*/
	/************************************************************************************************************************/
	bool aeVector2::CloseEnough(aeVector2 & V, float Range)
	{///Returns true if the magnitude between vectors is lower than the asked range.
		return ((*this - V).Magnitude() < Range);
	}

	float aeVector2::Magnitude()
	{///The magnitude of the vector is the length of the vector, it is obtained by the square root of the addition of the squared values of x and y.
		return sqrtf(x*x + y*y);
	}


	float aeVector2::DotProduct(aeVector2 & V)
	{///The dot product is the result of the sum of the products of the corresponding entries of the two sequences of numbers.
		return x*V.x + y*V.y;
	}

	float aeVector2::AngleBetweenVectors(aeVector2 & V)
	{///It gets the angle by using the definition of the dot product, and gives it direction getting the orientation given by the sign of the cross product.
		float fTemp = DotProduct(V) / (Magnitude() * V.Magnitude());
		fTemp = acos(fTemp);
		float fCrossProduct = CrossProduct(V);
		if (fCrossProduct < 0)
		{
			fTemp *= -1;
		}
		return fTemp;
	}

	float aeVector2::CrossProduct(aeVector2 & V)
	{///The cross product is the value of the resulting vector that is perpendicular to both entries, with a direction given by the right - hand rule and a magnitude equal to the area of the parallelogram that the vectors span.
		return (x*V.y) - (y*V.x);
	}

	float aeVector2::ScalarProjection(aeVector2 & V)
	{///The scalar projection is a scalar, equal to the length of the orthogonal projection of A on B, with a negative sign if the projection has an opposite direction with respect to B.
		return (*this | V) / Magnitude();
	}


	aeVector2 aeVector2::Normalize()
	{///The normalized vector is a vector in the same direction but with a magnitude equals to one
		float fInvMag = 1.0f / Magnitude();
		return *this * fInvMag;
	}

	aeVector2 aeVector2::VectorProjection(aeVector2 & V)
	{///The vector projection of A on B is a vector whose magnitude is the scalar projection of A on B and whose angle against B.
		return aeVector2(Normalize() *  ScalarProjection(V));
	}
}