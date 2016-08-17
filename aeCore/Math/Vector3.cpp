#include "aeCoreStd.h"
#include "Vector3.h"

namespace aeCore
{

	/************************************************************************************************************************/
	/* Constructors                                                        													*/
	/************************************************************************************************************************/
	aeVector3::aeVector3() : x(0), y(0), z(0)
	{
	};

	aeVector3::~aeVector3()
	{
	}

	aeVector3::aeVector3(const aeVector3 & V)
	{
		*this = V;
	}

	aeVector3::aeVector3(float X, float Y, float Z) : x(X), y(Y), z(Z)
	{
	}

	/***********************************************************************************************************************/
	/* Implementation of arithmetic operators						          												*/
	/***********************************************************************************************************************/
	aeVector3 aeVector3::operator*(aeVector3& V) 
	{
		return aeVector3(x * V.x, y * V.y, z * V.z);
	}
	aeVector3 aeVector3::operator+(aeVector3& V) 
	{
		return aeVector3(x + V.x, y + V.y, z + V.z);
	}
	aeVector3 aeVector3::operator-(aeVector3& V)
	{
		return aeVector3(x - V.x, y - V.y, z - V.z);
	}
	aeVector3 aeVector3::operator/(aeVector3& V) 
	{
		return aeVector3(x / V.x, y / V.y, z / V.z);
	}
	aeVector3 aeVector3::operator*(float S) {
		return aeVector3(x * S, y * S, z * S);
	}
	aeVector3 aeVector3::operator/(float S) {
		return aeVector3(x / S, y / S, z / S);
	}

	/************************************************************************************************************************/
	/* Implementation of logic operators			               															*/
	/************************************************************************************************************************/
	bool aeVector3::operator==(aeVector3& V) {
		return x == V.x && y == V.y && z == V.z;
	}

	bool aeVector3::operator!=(aeVector3& V) {
		return x != V.x || y != V.y || z != V.z;
	}

	/***********************************************************************************************************************/
	/* Implementation of compound assignment operators			               												*/
	/***********************************************************************************************************************/
	aeVector3& aeVector3::operator+=(aeVector3& V) {
		x += V.x; y += V.y;
		return *this;
	}
	aeVector3& aeVector3::operator-=(aeVector3& V) {
		x -= V.x; y -= V.y;
		return *this;
	}
	aeVector3& aeVector3::operator*=(aeVector3& V) {
		x *= V.x; y *= V.y;
		return *this;
	}
	aeVector3& aeVector3::operator/=(aeVector3& V) {
		x /= V.x; y /= V.y;
		return *this;
	}
	aeVector3& aeVector3::operator*=(float S) {
		x *= S; y *= S;
		return *this;
	}
	aeVector3& aeVector3::operator/=(float S) {
		x /= S; y /= S;
		return *this;
	}

	/************************************************************************************************************************/
	/* Functions implementation                                            													*/
	/************************************************************************************************************************/
	bool aeVector3::CloseEnough(aeVector3 & V, float Range)
	{///Returns true if the magnitude between vectors is lower than the asked range.
		return ((*this - V).Magnitude() < Range);
	}
	
	float aeVector3::Magnitude()
	{
		return sqrtf(x*x + y*y + z*z);
	}

	float aeVector3::DotProduct(aeVector3 & V)
	{
		return x*V.x + y*V.y + z*V.z;
	}

	float aeVector3::AngleBetweenVectors(aeVector3 & V)
	{
		if (*this == V)
			return 0;
		return acos(DotProduct(V) / (Magnitude() * V.Magnitude()));
	}

	float aeVector3::Cross2Product(aeVector3 & V)
	{
		return (x*V.y) - (y*V.x);
	}

	float aeVector3::ScalarProjection(aeVector3 & V)
	{
		return this->DotProduct(V) / this->Magnitude();
	}

	aeVector3 aeVector3::Cross3Product(aeVector3 & V)
	{
		return aeVector3(y*V.z - V.y*z, z*V.x - V.z*x, x*V.y - V.x*y);
	}

	aeVector3 aeVector3::Normalize()
	{
		float fInvMag = 1.0f / Magnitude();
		return *this * fInvMag;
	}

	aeVector3 aeVector3::VectorProjection(aeVector3 & V)
	{
		return Normalize() *  DotProduct(V) / Magnitude();
	}

	aeVector3 aeVector3::AnglesBetweenVectors(aeVector3 & V)
	{
		aeVector2 A1 = aeVector2{ x,y };
		aeVector2 A2 = aeVector2{ x,z };
		aeVector2 A3 = aeVector2{ y,z };
		aeVector2 B1 = aeVector2{ V.x,V.y };
		aeVector2 B2 = aeVector2{ V.x,V.z };
		aeVector2 B3 = aeVector2{ V.y,V.z };

		aeVector3 Result = aeVector3{
			A3.AngleBetweenVectors(B3),
			A2.AngleBetweenVectors(B2),
			A1.AngleBetweenVectors(B1) };
		return Result;
	}
}