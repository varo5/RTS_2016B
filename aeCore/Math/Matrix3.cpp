#include "aeCoreStd.h"
#include "Matrix3.h"

namespace aeCore
{
	/************************************************************************************************************************/
	/* Constructors                                                        													*/
	/************************************************************************************************************************/
	aeMatrix3::aeMatrix3()
	{
	}


	aeMatrix3::~aeMatrix3()
	{
	}

	aeMatrix3::aeMatrix3(const aeMatrix3& M)
	{
		*this = M;
	}

	aeMatrix3::aeMatrix3(
		float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22)
	{
		m_f00 = _00; m_f01 = _01; m_f02 = _02;
		m_f10 = _10; m_f11 = _11; m_f12 = _12;
		m_f20 = _20; m_f21 = _21; m_f22 = _22;
	}

	/************************************************************************************************************************/
	/* Vectors inside the matrix related functions.					          												*/
	/************************************************************************************************************************/
	void aeMatrix3::SetCol(aeVector3 & ReferenceVector, int ColumnNumber)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == ColumnNumber)
				{
					m[i][j] = ReferenceVector.v[j];
				}
			}
		}
	}

	void aeMatrix3::SetRow(aeVector3 & ReferenceVector, int RowNumber)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (j == RowNumber)
				{
					m[i][j] = ReferenceVector.v[i];
				}
			}
		}
	}

	aeVector3 aeMatrix3::GetCol(int ColumnNumber)
	{
		aeVector3 V;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == ColumnNumber)
				{
					V.v[j] = m[i][j];
				}
			}
		}
		return V;
	}

	aeVector3 aeMatrix3::GetRow(int RowNumber)
	{
		aeVector3 V;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (j == RowNumber)
				{
					V.v[i] = m[i][j];
				}
			}
		}
		return V;
	}

	/************************************************************************************************************************/
	/* Implementation of arithmetic operators						          												*/
	/************************************************************************************************************************/
	aeVector3 aeMatrix3::operator*(aeVector3 & ReferenceVector)
	{
		aeVector3 R;
		for (int j = 0; j < 3; j++)
			for (int i = 0; i < 3; i++)
				R.v[j] += m[j][i] * ReferenceVector.v[i];
		return R;
	}

	aeMatrix3 aeMatrix3::operator+(aeMatrix3 & ReferenceMatrix)
	{
		aeMatrix3 R;
		for (int i = 0; i < 9; i++)
			R.v[i] = v[i] + ReferenceMatrix.v[i];
		return R;
	}

	aeMatrix3 aeMatrix3::operator-(aeMatrix3 & ReferenceMatrix)
	{
		aeMatrix3 R;
		for (int i = 0; i < 9; i++)
			R.v[i] = v[i] - ReferenceMatrix.v[i];
		return R;
	}

	aeMatrix3 aeMatrix3::operator*(aeMatrix3 & ReferenceMatrix)
	{
		aeMatrix3 R;
		for (int i = 0; i < 9; i++)
			R.v[i] = v[i] * ReferenceMatrix.v[i];
		return R;
	}

	aeMatrix3 aeMatrix3::operator*(float Coefficient)
	{
		aeMatrix3 R;
		for (int i = 0; i < 9; i++)
			R.v[i] = v[i] + Coefficient;
		return R;
	}

	aeMatrix3 aeMatrix3::operator/(float Divider)
	{
		aeMatrix3 R;
		for (int i = 0; i < 9; i++)
			R.v[i] = v[i] / Divider;
		return R;
	}

	/************************************************************************************************************************/
	/* Implementation of compound assignment operators			               												*/
	/************************************************************************************************************************/
	aeMatrix3 aeMatrix3::operator+=(aeMatrix3 & ReferenceMatrix)
	{
		return *this + ReferenceMatrix;
	}

	aeMatrix3 aeMatrix3::operator-=(aeMatrix3 & ReferenceMatrix)
	{
		return *this - ReferenceMatrix;
	}

	aeMatrix3 aeMatrix3::operator*=(aeMatrix3 & ReferenceMatrix)
	{
		return *this * ReferenceMatrix;
	}

	aeMatrix3 aeMatrix3::operator*=(float Coefficient)
	{
		return *this * Coefficient;
	}

	aeMatrix3 aeMatrix3::operator/=(float Divider)
	{
		return *this / Divider;
	}

	/************************************************************************************************************************/
	/* Functions Implementation                                            													*/
	/************************************************************************************************************************/
	float aeMatrix3::Det()
	{
		return m_f00*(m_f11*m_f22 - m_f12*m_f21) - m_f01*(m_f10*m_f22 - m_f12*m_f20) + m_f02*(m_f10*m_f21 - m_f11*m_f20);
	}

	aeVector3 aeMatrix3::Cramer(aeVector3 & ReferenceVector)
	{
		float DetM = Det();
		if (DetM != 0)
		{
			aeMatrix3 D0 = { ReferenceVector.x, m_f01, m_f02,
				ReferenceVector.y, m_f11, m_f12,
				ReferenceVector.z, m_f21, m_f22 };
			aeMatrix3 D1 = { m_f00, ReferenceVector.x, m_f02,
				m_f10, ReferenceVector.y, m_f12,
				m_f20, ReferenceVector.z, m_f22 };
			aeMatrix3 D2 = { m_f00, m_f01, ReferenceVector.x,
				m_f10, m_f11, ReferenceVector.y,
				m_f20, m_f21, ReferenceVector.z };
			float d0 = D0.Det();
			float d1 = D1.Det();
			float d2 = D2.Det();

			return aeVector3{ d0 / DetM, d1 / DetM, d2 / DetM };
		}
		return aeVector3{ -1,-1,-1 };
	}

	aeMatrix3 aeMatrix3::Transpose()
	{
		aeMatrix3 MatTemp = { 0,0 };
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				MatTemp.m[j][i] = m[i][j];
		return MatTemp;
	}

	aeMatrix3 aeMatrix3::Cofactor()
	{
		aeMatrix3 B;
		B.m_f00 = (m_f11*m_f22 - m_f12*m_f21);
		B.m_f01 = -(m_f10*m_f22 - m_f12*m_f20);
		B.m_f02 = (m_f10*m_f21 - m_f11*m_f20);

		B.m_f10 = -(m_f01*m_f22 - m_f02*m_f21);
		B.m_f11 = (m_f00*m_f22 - m_f02*m_f20);
		B.m_f12 = -(m_f00*m_f21 - m_f01*m_f20);

		B.m_f20 = (m_f01*m_f12 - m_f02*m_f11);
		B.m_f21 = -(m_f00*m_f12 - m_f02*m_f10);
		B.m_f22 = (m_f00*m_f11 - m_f01*m_f10);
		return B;
	}

	aeMatrix3 aeMatrix3::Adjunct()
	{
		aeMatrix3 B = Cofactor();
		B = B.Transpose();
		return B;
	}

	aeMatrix3 aeMatrix3::Inverse()
	{
		float DetA = Det();
		if (DetA != 0)
		{
			aeMatrix3 B = Adjunct();
			B = B / Det();
			return B;
		}
		return aeMatrix3{ -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	}

	aeMatrix3 aeMatrix3::Zero()
	{
		return aeMatrix3{ 0,0,0,0,0,0,0,0,0 };
	}

	aeMatrix3 aeMatrix3::Identity()
	{
		return aeMatrix3{ 1,0,0,0,1,0,0,0,1 };
	}

	aeMatrix3 aeMatrix3::TranslationMatrix(aeVector3 & TranslationVector)
	{
		return aeMatrix3(1, 0, 0,
			0, 1, 0,
			TranslationVector.x, TranslationVector.y, 1);
	}

	aeMatrix3 aeMatrix3::TranslationMatrix(aeVector2 & TranslationVector)
	{
		return aeMatrix3(1, 0, 0,
			0, 1, 0,
			TranslationVector.x, TranslationVector.y, 1);
	}

	aeMatrix3 aeMatrix3::TranslationMatrix(float X, float Y)
	{
		return aeMatrix3(1, 0, 0,
			0, 1, 0,
			X, Y, 1);
	}

	aeMatrix3 aeMatrix3::ScalingMatrix(aeVector2 & ScaleVector)
	{
		return aeMatrix3(ScaleVector.x, 0, 0,
			0, ScaleVector.y, 0,
			0, 0, 1);
	}

	aeMatrix3 aeMatrix3::ScalingMatrix(aeVector3 & ScaleVector)
	{
		return aeMatrix3(ScaleVector.x, 0, 0,
			0, ScaleVector.y, 0,
			0, 0, 1);
	}

	aeMatrix3 aeMatrix3::ScalingMatrix(float ScaleFactor)
	{
		return aeMatrix3(ScaleFactor, 0, 0,
			0, ScaleFactor, 0,
			0, 0, 1);
	}

	aeMatrix3 aeMatrix3::ScalingMatrix(float x, float y)
	{
		return aeMatrix3(
			x, 0, 0,
			0, y, 0,
			0, 0, 1);
	}

	aeMatrix3 aeMatrix3::RotationX(float theta)
	{
		aeMatrix3 R(1);
		R.m_f00 = R.m_f22 = cosf(theta);
		R.m_f12 = -sinf(theta);
		R.m_f21 = -R.m_f12;
		return R;
	}

	aeMatrix3 aeMatrix3::RotationY(float theta)
	{
		aeMatrix3 R(1);
		R.m_f00 = R.m_f22 = cosf(theta);
		R.m_f20 = -sinf(theta);
		R.m_f02 = -R.m_f20;
		return R;
	}

	aeMatrix3 aeMatrix3::RotationZ(float theta)
	{
		aeMatrix3 R(1);
		R.m_f11 = R.m_f00 = cosf(theta);
		R.m_f01 = -sinf(theta);
		R.m_f10 = -R.m_f01;
		return R;
	}
}