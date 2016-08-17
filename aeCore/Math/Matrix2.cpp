#include "aeCoreStd.h"
#include "Matrix2.h"

namespace aeCore
{
	/************************************************************************************************************************/
	/* Constructors                                                        													*/
	/************************************************************************************************************************/
	aeMatrix2::aeMatrix2() : m_f00(0), m_f01(0), m_f10(0), m_f11(0)
	{
	}


	aeMatrix2::~aeMatrix2()
	{
	}

	aeMatrix2::aeMatrix2(const aeMatrix2 & ReferenceMatrix)
	{
		*this = ReferenceMatrix;
	}

	aeMatrix2::aeMatrix2(
		float _00, float _01,
		float _10, float _11) : m_f00(_00),
		m_f01(_01), m_f10(_10), m_f11(_11)
	{
	}

	/************************************************************************************************************************/
	/* Vectors inside the matrix related functions.					          												*/
	/************************************************************************************************************************/
	void aeMatrix2::SetCol(aeVector2 & ReferenceVector, int ColumnNumber)
	{
		if (ColumnNumber == 0)
		{
			m_f00 = ReferenceVector.x;
			m_f10 = ReferenceVector.y;
		}
		else if (ColumnNumber == 1)
		{
			m_f01 = ReferenceVector.x;
			m_f11 = ReferenceVector.y;
		}
	}

	void aeMatrix2::SetRow(aeVector2 & ReferenceVector, int RowNumber)
	{
		if (RowNumber == 0)
		{
			m_f00 = ReferenceVector.x;
			m_f01 = ReferenceVector.y;
		}
		else if (RowNumber == 1)
		{
			m_f10 = ReferenceVector.x;
			m_f11 = ReferenceVector.y;
		}
	}

	aeVector2 aeMatrix2::GetCol(int ColumnNumber)
	{
		if (ColumnNumber == 0)
		{
			return aeVector2(m_f00, m_f10);
		}
		else if (ColumnNumber == 1)
		{
			return aeVector2(m_f01, m_f11);
		}
		return aeVector2();
	}

	aeVector2 aeMatrix2::GetRow(int RowNumber)
	{
		if (RowNumber == 0)
		{
			return aeVector2(m_f00, m_f01);
		}
		else if (RowNumber == 1)
		{
			return aeVector2(m_f10, m_f11);
		}
		return aeVector2();
	}

	/************************************************************************************************************************/
	/* Implementation of arithmetic operators						          												*/
	/************************************************************************************************************************/
	aeVector2 aeMatrix2::operator*(aeVector2 & ReferenceVector)
	{
		return aeVector2(m_f00 * ReferenceVector.x + m_f10 * ReferenceVector.y,
			m_f01 * ReferenceVector.x + m_f11 * ReferenceVector.y);
	}

	aeMatrix2 aeMatrix2::operator+(aeMatrix2 & ReferenceMatrix)
	{
		return aeMatrix2(m_f00 + ReferenceMatrix.m_f00, m_f01 + ReferenceMatrix.m_f01,
			m_f10 + ReferenceMatrix.m_f10, m_f11 + ReferenceMatrix.m_f11);
	}

	aeMatrix2 aeMatrix2::operator-(aeMatrix2 & ReferenceMatrix)
	{
		return aeMatrix2(m_f00 - ReferenceMatrix.m_f00, m_f01 - ReferenceMatrix.m_f01,
			m_f10 - ReferenceMatrix.m_f10, m_f11 - ReferenceMatrix.m_f11);
	}

	aeMatrix2 aeMatrix2::operator*(aeMatrix2 & ReferenceMatrix)
	{
		return aeMatrix2(m_f00 * ReferenceMatrix.m_f00, m_f01 * ReferenceMatrix.m_f01,
			m_f10 * ReferenceMatrix.m_f10, m_f11 * ReferenceMatrix.m_f11);
	}

	aeMatrix2 aeMatrix2::operator*(float Coefficient)
	{
		return aeMatrix2(m_f00 * Coefficient, m_f01 * Coefficient,
			m_f10 * Coefficient, m_f11 * Coefficient);
	}

	aeMatrix2 aeMatrix2::operator/(float Divider)
	{
		float Coefficient = 1 / Divider;
		return aeMatrix2(m_f00 * Coefficient, m_f01 * Coefficient,
			m_f10 * Coefficient, m_f11 * Coefficient);
	}

	/************************************************************************************************************************/
	/* Implementation of compound assignment operators			               												*/
	/************************************************************************************************************************/
	aeMatrix2 aeMatrix2::operator+=(aeMatrix2 & ReferenceMatrix)
	{
		return *this + ReferenceMatrix;
	}

	aeMatrix2 aeMatrix2::operator-=(aeMatrix2 & ReferenceMatrix)
	{
		return *this - ReferenceMatrix;
	}

	aeMatrix2 aeMatrix2::operator*=(aeMatrix2 & ReferenceMatrix)
	{
		return *this * ReferenceMatrix;
	}

	aeMatrix2 aeMatrix2::operator*=(float Coefficient)
	{
		return *this * Coefficient;
	}

	aeMatrix2 aeMatrix2::operator/=(float Divider)
	{
		return *this / Divider;
	}

	/************************************************************************************************************************/
	/* Functions declaration                                            													*/
	/************************************************************************************************************************/
	float aeMatrix2::Det()
	{
		return m_f00*m_f11 - m_f01*m_f10;
	}

	aeMatrix2 aeMatrix2::Transpose()
	{
		return aeMatrix2(m_f00, m_f10, m_f01, m_f11);
	}

	aeMatrix2 aeMatrix2::Cofactor()
	{
		return aeMatrix2(m_f11, -m_f10, -m_f01, m_f00);
	}

	aeMatrix2 aeMatrix2::Adjunct()
	{
		return aeMatrix2(m_f11, -m_f01, -m_f10, m_f00);
	}

	aeMatrix2 aeMatrix2::Inverse()
	{
		float DetTemp = Det();
		if (DetTemp != 0)
		{
			aeMatrix2 MatrixTemp = Adjunct();
			MatrixTemp = MatrixTemp / DetTemp;
			return MatrixTemp;
		}
		return aeMatrix2(-1, -1, -1, -1);
	}

	inline aeMatrix2 aeMatrix2::Zero()
	{
		return aeMatrix2(0, 0, 0, 0);
	}

	inline aeMatrix2 aeMatrix2::Identity()
	{
		return aeMatrix2(1, 0, 0, 1);
	}

	aeMatrix2 aeMatrix2::RotationMatrix(float DegreesOfRotation)
	{
		return aeMatrix2(cos(DegreesOfRotation), -sin(DegreesOfRotation),
			sin(DegreesOfRotation), cos(DegreesOfRotation));
	}

	aeMatrix2 aeMatrix2::ScalingMatrix(aeVector2& ScaleVector)
	{
		return aeMatrix2(ScaleVector.x, 0, 0, ScaleVector.y);
	}

	aeMatrix2 aeMatrix2::ScalingMatrix(float ScaleFactor)
	{
		return aeMatrix2(ScaleFactor, 0, 0, ScaleFactor);
	}

	aeVector2 aeMatrix2::Cramer(aeVector2 & ReferenceVector)
	{
		float DetM = Det();
		if (DetM != 0)
		{
			aeMatrix2 D0 = { ReferenceVector.x, m_f01, ReferenceVector.y, m_f11 };
			aeMatrix2 D1 = { m_f00, ReferenceVector.x, m_f10, ReferenceVector.y };
			float d0 = D0.Det();
			float d1 = D1.Det();

			return aeVector2{ d0 / DetM, d1 / DetM };
		}
		return aeVector2{ -1,-1 };
	}

	aeVector2 aeMatrix2::Rotate(float RadiansOfRotation, aeVector2& VectorToRotate)
	{
		return RotationMatrix(RadiansOfRotation) * VectorToRotate;
	}

	aeVector2 aeMatrix2::Rotate(aeVector2 & VectorToRotate, aeVector2 & VectorAddingRotation)
	{
		float fAngle = VectorToRotate.AngleBetweenVectors(VectorAddingRotation);
		return RotationMatrix(fAngle) * VectorToRotate;
	}

	aeVector2 aeMatrix2::HomogeneousTransformation(aeVector2 & VectorToTransform, aeVector2 & TranslationVector, aeVector2 & ScaleVector, aeVector2 & VectorAddingRotation)
	{
		aeMatrix2 Temp;
		float fAngle = VectorToTransform.AngleBetweenVectors(VectorAddingRotation);
		Temp = Temp.RotationMatrix(fAngle) + Temp.ScalingMatrix(ScaleVector);
		return aeVector2(VectorToTransform.x * Temp.m_f00 + VectorToTransform.y * Temp.m_f01 + TranslationVector.x, VectorToTransform.x * Temp.m_f10 + VectorToTransform.y * Temp.m_f11 + TranslationVector.y);
	}

	aeVector2 aeMatrix2::HomogeneousTransformation(aeVector2& VectorToTransform, aeVector2& TranslationVector, aeVector2 & ScaleVector, float RadiansOfRotation)
	{
		aeMatrix2 Temp;
		Temp = Temp.RotationMatrix(RadiansOfRotation) + Temp.ScalingMatrix(ScaleVector);
		return aeVector2(VectorToTransform.x * Temp.m_f00 + VectorToTransform.y * Temp.m_f01 + TranslationVector.x, VectorToTransform.x * Temp.m_f10 + VectorToTransform.y * Temp.m_f11 + TranslationVector.y);
	}

	aeVector2 aeMatrix2::HomogeneousTransformation(aeVector2& VectorToTransform, aeVector2 & TranslationVector, float ScaleFactor, float RadiansOfRotation)
	{
		aeMatrix2 Temp;
		Temp = Temp.RotationMatrix(RadiansOfRotation) + Temp.ScalingMatrix(ScaleFactor);
		return aeVector2(VectorToTransform.x * Temp.m_f00 + VectorToTransform.y * Temp.m_f01 + TranslationVector.x, VectorToTransform.x * Temp.m_f10 + VectorToTransform.y * Temp.m_f11 + TranslationVector.y);
	}
}