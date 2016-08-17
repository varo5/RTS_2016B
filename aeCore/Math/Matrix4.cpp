#include "aeCoreStd.h"
#include "Matrix4.h"

namespace aeCore
{
	/************************************************************************************************************************/
	/* Constructors                                                        													*/
	/************************************************************************************************************************/
	aeMatrix4::aeMatrix4()
	{
		m_f00 = 0; m_f01 = 0; m_f02 = 0; m_f03 = 0;
		m_f10 = 0; m_f11 = 0; m_f12 = 0; m_f13 = 0;
		m_f20 = 0; m_f21 = 0; m_f22 = 0; m_f23 = 0;
		m_f30 = 0; m_f31 = 0; m_f32 = 0; m_f33 = 0;
	}

	aeMatrix4::aeMatrix4(const aeMatrix4& M)
	{
		*this = M;
	}

	aeMatrix4::aeMatrix4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33)
	{
		m_f00 = _00; m_f01 = _01; m_f02 = _02; m_f03 = _03;
		m_f10 = _10; m_f11 = _11; m_f12 = _12; m_f13 = _13;
		m_f20 = _20; m_f21 = _21; m_f22 = _22; m_f23 = _23;
		m_f30 = _30; m_f31 = _31; m_f32 = _32; m_f33 = _33;
	}

	/************************************************************************************************************************/
	/* Vectors inside the matrix related functions.					          												*/
	/************************************************************************************************************************/
	void aeMatrix4::SetCol(aeVector4 & V, int nCol)
	{
		for (int i = 0; i < 4; i++)
			m[i][nCol] = V.v[i];
	}

	void aeMatrix4::SetRow(aeVector4 & V, int nRow)
	{
		for (int i = 0; i < 4; i++)
			m[nRow][i] = V.v[i];
	}

	aeVector4 aeMatrix4::GetCol(int nCol)
	{
		aeVector4 R;
		for (int i = 0; i < 4; i++)
			R.v[i] = m[i][nCol];
		return R;
	}

	aeVector4 aeMatrix4::GetRow(int nRow)
	{
		aeVector4 R;
		for (int i = 0; i < 4; i++)
			R.v[i] = m[nRow][i];
		return R;
	}

	/************************************************************************************************************************/
	/* Implementation of arithmetic operators						          												*/
	/************************************************************************************************************************/
	aeMatrix4 aeMatrix4::operator+(aeMatrix4 & V) {
		aeMatrix4 R;
		for (int i = 0; i < 16; i++)
			R.v[i] = v[i] + V.v[i];
		return R;
	}

	aeMatrix4 aeMatrix4::operator-(aeMatrix4 & V) {
		aeMatrix4 R;
		for (int i = 0; i < 16; i++)
			R.v[i] = v[i] - V.v[i];
		return R;
	}

	aeMatrix4 aeMatrix4::operator*(aeMatrix4 & V) {
		aeMatrix4 R;
		for (int j = 0; j < 4; j++)
			for (int i = 0; i < 4; i++)
				for (int k = 0; k < 4; k++)
					R.m[j][i] += m[j][k] * V.m[k][i];
		return R;
	}

	aeMatrix4 aeMatrix4::operator*(float s) {
		aeMatrix4 R;
		for (int i = 0; i < 16; i++)
			R.v[i] = v[i] * s;
		return R;
	}

	aeMatrix4 aeMatrix4::operator/(float s) {
		s = 1.0f / s;
		return *this*s;
	}

	/************************************************************************************************************************/
	/* Implementation of compound assignment operators			               												*/
	/************************************************************************************************************************/
	aeMatrix4 & aeMatrix4::operator+=(aeMatrix4 & A)
	{
		*this = *this + A;
		return *this;
	}

	aeMatrix4 & aeMatrix4::operator-=(aeMatrix4 & A)
	{
		*this = *this - A;
		return *this;
	}

	aeMatrix4 & aeMatrix4::operator*=(aeMatrix4 & A)
	{
		*this = *this*A;
		return *this;
	}

	aeMatrix4 & aeMatrix4::operator*=(float s)
	{
		*this = *this*s;
		return *this;
	}

	aeMatrix4 & aeMatrix4::operator/=(float s)
	{
		*this = *this / s;
		return *this;
	}


	/************************************************************************************************************************/
	/* Functions Implementation                                            													*/
	/************************************************************************************************************************/
	aeMatrix4 aeMatrix4::Zero(void) {
		aeMatrix4 R;
		for (int i = 0; i < 16; i++)
			R.v[i] = 0;
		return R;
	}

	aeMatrix4 aeMatrix4::Identity(void) {
		aeMatrix4 R;
		for (int j = 0; j < 4; j++)
			for (int i = 0; i < 4; i++)
				R.m[i][j] = 0;
		return R;
	}


	aeMatrix4 aeMatrix4::Transpose()
	{
		aeMatrix4 MatTemp = { 0,0 };
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				MatTemp.m[j][i] = m[i][j];
		return MatTemp;
	}

	float aeMatrix4::Det() {
		float det =
			m_f00*(m_f11*(m_f22*m_f33 - m_f23*m_f32)
				- m_f12*(m_f21*m_f33 - m_f23*m_f31)
				+ m_f13*(m_f21*m_f32 - m_f22*m_f31))
			- m_f01*(m_f10*(m_f22*m_f33 - m_f23*m_f32)
				- m_f12*(m_f20*m_f33 - m_f23*m_f30)
				+ m_f13*(m_f20*m_f32 - m_f22*m_f30))
			+ m_f02*(m_f10*(m_f21*m_f33 - m_f23*m_f31)
				- m_f11*(m_f20*m_f33 - m_f23*m_f30)
				+ m_f13*(m_f20*m_f31 - m_f21*m_f30))
			- m_f03*(m_f10*(m_f21*m_f32 - m_f22*m_f31)
				- m_f11*(m_f20*m_f32 - m_f22*m_f30)
				+ m_f12*(m_f20*m_f31 - m_f21*m_f30));
		return det;
	}

	aeMatrix4 aeMatrix4::Cofactor()
	{
		aeMatrix4 B;
		B.m_f00 = (m_f11*(m_f22*m_f33 - m_f23*m_f32)
			- m_f12*(m_f21*m_f33 - m_f23*m_f31)
			+ m_f13*(m_f21*m_f32 - m_f22*m_f31));
		B.m_f01 = -(m_f10*(m_f22*m_f33 - m_f23*m_f32)
			- m_f12*(m_f20*m_f33 - m_f23*m_f30)
			+ m_f13*(m_f20*m_f32 - m_f22*m_f30));
		B.m_f02 = (m_f10*(m_f21*m_f33 - m_f23*m_f31)
			- m_f11*(m_f20*m_f33 - m_f23*m_f30)
			+ m_f13*(m_f20*m_f31 - m_f21*m_f30));
		B.m_f03 = -(m_f10*(m_f21*m_f32 - m_f22*m_f31)
			- m_f11*(m_f20*m_f32 - m_f22*m_f30)
			+ m_f12*(m_f20*m_f31 - m_f21*m_f30));

		B.m_f10 = -(m_f01*(m_f22*m_f33 - m_f23*m_f32)
			- m_f02*(m_f21*m_f33 - m_f23*m_f31)
			+ m_f03*(m_f21*m_f32 - m_f22*m_f31));
		B.m_f11 = (m_f00*(m_f22*m_f33 - m_f23*m_f32)
			- m_f02*(m_f20*m_f33 - m_f23*m_f30)
			+ m_f03*(m_f20*m_f32 - m_f22*m_f30));
		B.m_f12 = -(m_f00*(m_f21*m_f33 - m_f23*m_f31)
			- m_f01*(m_f20*m_f33 - m_f23*m_f30)
			+ m_f03*(m_f20*m_f31 - m_f21*m_f30));
		B.m_f13 = (m_f00*(m_f21*m_f32 - m_f22*m_f31)
			- m_f01*(m_f20*m_f32 - m_f22*m_f30)
			+ m_f02*(m_f20*m_f31 - m_f21*m_f30));

		B.m_f20 = (m_f01*(m_f12*m_f33 - m_f13*m_f32)
			- m_f02*(m_f11*m_f33 - m_f13*m_f31)
			+ m_f03*(m_f11*m_f32 - m_f12*m_f31));
		B.m_f21 = -(m_f00*(m_f12*m_f33 - m_f13*m_f32)
			- m_f02*(m_f10*m_f33 - m_f13*m_f30)
			+ m_f03*(m_f10*m_f32 - m_f12*m_f30));
		B.m_f22 = (m_f00*(m_f11*m_f33 - m_f13*m_f31)
			- m_f01*(m_f10*m_f33 - m_f13*m_f30)
			+ m_f03*(m_f10*m_f31 - m_f11*m_f30));
		B.m_f23 = -(m_f00*(m_f11*m_f32 - m_f12*m_f31)
			- m_f01*(m_f10*m_f32 - m_f12*m_f30)
			+ m_f02*(m_f10*m_f31 - m_f11*m_f30));

		B.m_f30 = -(m_f01*(m_f12*m_f23 - m_f13*m_f22)
			- m_f02*(m_f11*m_f23 - m_f13*m_f21)
			+ m_f03*(m_f11*m_f22 - m_f12*m_f21));
		B.m_f31 = (m_f00*(m_f12*m_f23 - m_f13*m_f22)
			- m_f02*(m_f10*m_f23 - m_f13*m_f20)
			+ m_f03*(m_f10*m_f22 - m_f12*m_f20));
		B.m_f32 = -(m_f00*(m_f11*m_f23 - m_f13*m_f21)
			- m_f01*(m_f10*m_f23 - m_f13*m_f20)
			+ m_f03*(m_f10*m_f21 - m_f11*m_f20));
		B.m_f33 = (m_f00*(m_f11*m_f22 - m_f12*m_f21)
			- m_f01*(m_f10*m_f22 - m_f12*m_f20)
			+ m_f02*(m_f10*m_f21 - m_f11*m_f20));
		return B;
	}

	aeMatrix4 aeMatrix4::Adjunct()
	{
		aeMatrix4 B = Cofactor();
		B = Transpose();
		return B;
	}

	aeMatrix4 aeMatrix4::Inverse()
	{
		float DetA = Det();
		if (DetA != 0)
		{
			aeMatrix4 B = Adjunct();
			B = B / Det();
			return B;
		}
		return aeMatrix4{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	}

	aeVector4 aeMatrix4::operator*(aeVector4& V) {
		aeVector4 R;
		for (int j = 0; j < 4; j++)
			for (int i = 0; i < 4; i++)
				R.v[j] += m[j][i] * V.v[i];
		return R;
	}

	aeVector4 aeMatrix4::Cramer(aeVector4& V)
	{
		float DetM = Det();
		if (DetM != 0)
		{
			aeMatrix4 D0 = { V.x, m_f01, m_f02, m_f03,
				V.y, m_f11, m_f12, m_f13,
				V.z, m_f21, m_f22, m_f23,
				V.w, m_f31, m_f32, m_f33 };
			aeMatrix4 D1 = { m_f00, V.x, m_f02, m_f03,
				m_f10, V.y, m_f12, m_f13,
				m_f20, V.z, m_f22, m_f23,
				m_f30, V.w, m_f32, m_f33 };
			aeMatrix4 D2 = { m_f00, m_f01, V.x, m_f03,
				m_f10, m_f11, V.y, m_f13,
				m_f20, m_f21, V.z, m_f23,
				m_f30, m_f31, V.w, m_f33 };
			aeMatrix4 D3 = { m_f00, m_f01, m_f02, V.x,
				m_f10, m_f11, m_f12, V.y,
				m_f20, m_f21, m_f22, V.z,
				m_f30, m_f31, m_f32, V.w };
			float d0 = D0.Det();
			float d1 = D1.Det();
			float d2 = D2.Det();
			float d3 = D3.Det();

			return aeVector4{ d0 / DetM, d1 / DetM, d2 / DetM, d3 / DetM };
		}
		return aeVector4{ -1,-1,-1,-1 };
	}

	aeMatrix4 aeMatrix4::ScalingMatrix(float ScaleFactor)
	{
		return aeMatrix4(
			ScaleFactor, 0, 0, 0,
			0, ScaleFactor, 0, 0,
			0, 0, ScaleFactor, 0,
			0, 0, 0, 1);
	}

	aeMatrix4 aeMatrix4::ScalingMatrix(float x, float y, float z)
	{
		return aeMatrix4(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
	}

	aeMatrix4 aeMatrix4::ScalingMatrix(aeVector4 & V)
	{
		return ScalingMatrix(V.x, V.y, V.z);
	}

	aeMatrix4 aeMatrix4::ScalingMatrix(aeVector3 & V)
	{
		return ScalingMatrix(V.x, V.y, V.z);
	}

	aeMatrix4 aeMatrix4::ScalingMatrix(aeVector2 & V)
	{
		return ScalingMatrix(V.x, V.y, 1);
	}

	aeMatrix4 aeMatrix4::RotationX(float theta)
	{
		aeMatrix4 R(1);
		R.m_f00 = R.m_f22 = cosf(theta);
		R.m_f12 = -sinf(theta);
		R.m_f21 = -R.m_f12;
		return R;
	}

	aeMatrix4 aeMatrix4::RotationY(float theta)
	{
		aeMatrix4 R(1);
		R.m_f00 = R.m_f22 = cosf(theta);
		R.m_f20 = -sinf(theta);
		R.m_f02 = -R.m_f20;
		return R;
	}

	aeMatrix4 aeMatrix4::RotationZ(float theta)
	{
		aeMatrix4 R(1);
		R.m_f11 = R.m_f00 = cosf(theta);
		R.m_f01 = -sinf(theta);
		R.m_f10 = -R.m_f01;
		return R;
	}

	aeMatrix4 aeMatrix4::TranslationMatrix(float x, float y, float z)
	{
		return aeMatrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, 1);
	}

	aeMatrix4 aeMatrix4::TranslationMatrix(aeVector4& V)
	{
		return TranslationMatrix(V.x, V.y, V.z);
	}

	aeMatrix4 aeMatrix4::TranslationMatrix(aeVector3 & V)
	{
		return TranslationMatrix(V.x, V.y, V.z);
	}

	aeMatrix4 aeMatrix4::TranslationMatrix(aeVector2 & V)
	{
		return TranslationMatrix(V.x, V.y, 0);
	}
}