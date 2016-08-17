#include "aeCoreStd.h"
#include "Vector4.h"

namespace aeCore
{
	/************************************************************************************************************************/
	/* Constructors                                                        													*/
	/************************************************************************************************************************/
	aeVector4::aeVector4() : x(0), y(0), z(0), w(0)
	{
	}

	aeVector4::~aeVector4()
	{
	}

	aeVector4::aeVector4(const aeVector4& V)
	{
		*this = V;
	}

	aeVector4::aeVector4(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W)
	{
	}

	/***********************************************************************************************************************/
	/* Implementation of arithmetic operators						          												*/
	/***********************************************************************************************************************/
	aeVector4 aeVector4::operator*(aeVector4& V)
	{
		return aeVector4(x * V.x, y * V.y, z * V.z, w * V.w);
	}

	aeVector4 aeVector4::operator+(aeVector4& V)
	{
		return aeVector4(x + V.x, y + V.y, z + V.z, w + V.w);
	}

	aeVector4 aeVector4::operator-(aeVector4& V)
	{
		return aeVector4::aeVector4(x - V.x, y - V.y, z - V.z, w - V.w);
	}

	aeVector4 aeVector4::operator/(aeVector4& V)
	{
		return aeVector4(x / V.x, y / V.y, z / V.z, w / V.w);
	}

	aeVector4 aeVector4::operator*(float S)
	{
		return aeVector4(x * S, y * S, z * S, w * S);
	}

	aeVector4 aeVector4::operator/(float S)
	{
		return *this*(1.0f / S);
	}

	/***********************************************************************************************************************/
	/* Implementation of compound assignment operators			               												*/
	/***********************************************************************************************************************/
	aeVector4& aeVector4::operator+=(aeVector4& A)
	{
		x += A.x;
		y += A.y;
		z += A.z;
		w += A.w;
		return *this;
	}

	aeVector4& aeVector4::operator-=(aeVector4& A)
	{
		x -= A.x;
		y -= A.y;
		z -= A.z;
		w -= A.w;
		return *this;
	}

	aeVector4& aeVector4::operator*=(aeVector4& A)
	{
		x *= A.x;
		y *= A.y;
		z *= A.z;
		w *= A.w;
		return *this;
	}

	aeVector4& aeVector4::operator/=(aeVector4& A)
	{
		x /= A.x;
		y /= A.y;
		z /= A.z;
		w /= A.w;
		return *this;
	}

	aeVector4& aeVector4::operator*=(float S)
	{
		x *= S;
		y *= S;
		z *= S;
		w *= S;
		return *this;
	}

	/************************************************************************************************************************/
	/* Implementation of logic operators			               															*/
	/************************************************************************************************************************/
	bool aeVector4::operator==(aeVector4 & V)
	{
		return (x == V.x &&	y == V.y && z == V.z && w == V.w);
	}

	bool aeVector4::operator!=(aeVector4 & V)
	{
		return (x != V.x || y != V.y || z != V.z || w != V.w);
	}

	/************************************************************************************************************************/
	/* Functions declaration                                            													*/
	/************************************************************************************************************************/
	float aeVector4::DotProduct(aeVector4& V)
	{
		return x*V.x + y*V.y + z*V.z + w*V.w;
	}

	bool aeVector4::CloseEnough(aeVector4 & V, float Range)
	{///Returns true if the magnitude between vectors is lower than the asked range.
		return ((*this - V).Magnitude() < Range);
	}

	float aeVector4::Magnitude()
	{
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	float aeVector4::AngleBetweenVectors(aeVector4 &V)
	{
		if (*this == V)
			return 0;
		return acos(DotProduct(V) / (Magnitude() * V.Magnitude()));
	}

	float aeVector4::Cross2Product(aeVector4 & V)
	{
		return (x*V.y) - (y*V.x);
	}

	float aeVector4::ScalarProjection(aeVector4 & V)
	{
		return DotProduct(V) / Magnitude();
	}

	aeVector4 aeVector4::Cross3Product(aeVector4& V)
	{
		return aeVector4(y*V.z - V.y*z, z*V.x - V.z*x, x*V.y - V.x*y);
	}

	aeVector4 aeVector4::Normalize()
	{
		return *this *(1.0f / Magnitude());
	}

	aeVector4 aeVector4::VectorProjection(aeVector4 & V)
	{
		return Normalize() * (DotProduct(V) / Magnitude());
	}

	aeVector4 aeVector4::AnglesBetweenVectors(aeVector4 & V)
	{
		aeVector2 A1 = aeVector2{ x,y };
		aeVector2 A2 = aeVector2{ x,z };
		aeVector2 A3 = aeVector2{ y,z };
		aeVector2 B1 = aeVector2{ V.x,V.y };
		aeVector2 B2 = aeVector2{ V.x,V.z };
		aeVector2 B3 = aeVector2{ V.y,V.z };

		aeVector4 Result;
		Result.x = A3.AngleBetweenVectors(B3);
		Result.y = A2.AngleBetweenVectors(B2);
		Result.z = A1.AngleBetweenVectors(B1);
		return Result;
	}
}