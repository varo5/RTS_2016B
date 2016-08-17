#pragma once
#include "Matrix3.h"
namespace aeCore
{
	/**********************************************************************************************//**
	 * @struct	aeMatrix4
	 *
	 * @brief	This structure is a 4x4 matrix of float values.
	 *
	 * @author	Alvaro Estrada
	 * @date	14/05/2016
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeMatrix4
	{
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		/// Is the union between individual values and their array and matrix form.
		union {
			/// A structure meant to save the matrix as individual values.
			struct
			{
				float m_f00, m_f01, m_f02, m_f03;
				float m_f10, m_f11, m_f12, m_f13;
				float m_f20, m_f21, m_f22, m_f23;
				float m_f30, m_f31, m_f32, m_f33;
			};
			/// A 4x4 float array
			float m[4][4];
			/// A 16 times float array.
			float v[16];
		};

		/************************************************************************************************************************/
		/* Constructors                                                        													*/
		/************************************************************************************************************************/
		aeMatrix4();
		aeMatrix4(const aeMatrix4& M);
		aeMatrix4(float _00, float _01 = 0, float _02 = 0, float _03 = 0,
			float _10 = 0, float _11 = 1, float _12 = 0, float _13 = 0,
			float _20 = 0, float _21 = 0, float _22 = 1, float _23 = 0,
			float _30 = 0, float _31 = 0, float _32 = 0, float _33 = 1);

		/************************************************************************************************************************/
		/* Vectors inside the matrix related functions.					          												*/
		/************************************************************************************************************************/
		void SetCol(aeVector4& V, int nCol);
		void SetRow(aeVector4& V, int nRow);
		aeVector4 GetCol(int nCol);
		aeVector4 GetRow(int nRow);

		/************************************************************************************************************************/
		/* Implementation of arithmetic operators						          												*/
		/************************************************************************************************************************/
		aeMatrix4 operator+(aeMatrix4& M);
		aeMatrix4 operator-(aeMatrix4& M);
		aeMatrix4 operator*(aeMatrix4& M);
		aeMatrix4 operator*(float s);
		aeMatrix4 operator/(float s);
		aeVector4 operator*(aeVector4& V);

		/************************************************************************************************************************/
		/* Implementation of compound assignment operators			               												*/
		/************************************************************************************************************************/
		aeMatrix4& operator+=(aeMatrix4& A);
		aeMatrix4& operator-=(aeMatrix4& A);
		aeMatrix4& operator*=(aeMatrix4& A);
		aeMatrix4& operator*=(float s);
		aeMatrix4& operator/=(float s);

		/************************************************************************************************************************/
		/* Functions declaration                                            													*/
		/************************************************************************************************************************/

		/**********************************************************************************************//**
		 * @fn	float Det();
		 *
		 * @brief	Obtains the determinant of this matrix.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float Det();

		/**********************************************************************************************//**
		 * @fn	aeVector4 Cramer(aeVector4& V);
		 *
		 * @brief	Uses Cramer's rule for the solution of an equation system.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A aeVector4.
		 **************************************************************************************************/

		aeVector4 Cramer(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	aeMatrix4 Transpose();
		 *
		 * @brief	Obtain the transposed matrix of this matrix.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		aeMatrix4 Transpose();

		/**********************************************************************************************//**
		 * @fn	aeMatrix4 Cofactor();
		 *
		 * @brief	Obtains the cofactor matrix of this matrix.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		aeMatrix4 Cofactor();

		/**********************************************************************************************//**
		 * @fn	aeMatrix4 Adjunct();
		 *
		 * @brief	Obtains the adjunct matrix of this matrix.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		aeMatrix4 Adjunct();

		/**********************************************************************************************//**
		 * @fn	aeMatrix4 Inverse();
		 *
		 * @brief	Obtains the transposed matrix of this matrix.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		aeMatrix4 Inverse();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 Zero();
		 *
		 * @brief	Returns an empty matrix.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 Zero();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 Identity();
		 *
		 * @brief	Returns an identity matrix.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 Identity();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 TranslationMatrix(aeVector4& V);
		 *
		 * @brief	Creates a translation matrix from a vector.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 TranslationMatrix(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 TranslationMatrix(aeVector3& V);
		 *
		 * @brief	Creates a translation matrix from a vector.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 TranslationMatrix(aeVector3& V);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 TranslationMatrix(aeVector2& V);
		 *
		 * @brief	Creates a translation matrix from a vector.
		 *
		 * @param [in,out]	V	The aeVector2 to process.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 TranslationMatrix(aeVector2& V);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 TranslationMatrix(float x, float y, float z);
		 *
		 * @brief	Creates a translation matrix from 3 parameters.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 * @param	z	The z coordinate.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 TranslationMatrix(float x, float y, float z);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 ScalingMatrix(float ScaleFactor);
		 *
		 * @brief	Creates a scaling matrix from a scale factor.
		 *
		 * @param	ScaleFactor	The scale factor.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 ScalingMatrix(float ScaleFactor);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 ScalingMatrix(float x, float y, float z);
		 *
		 * @brief	Creates a scaling matrix from 3 scale factors.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 * @param	z	The z coordinate.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 ScalingMatrix(float x, float y, float z);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 ScalingMatrix(aeVector4& V);
		 *
		 * @brief	Creates a scaling matrix from a vector.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 ScalingMatrix(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 ScalingMatrix(aeVector3& V);
		 *
		 * @brief	Creates a scaling matrix from a vector.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 ScalingMatrix(aeVector3& V);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 ScalingMatrix(aeVector2& V);
		 *
		 * @brief	Creates a scaling matrix from a vector.
		 *
		 * @param [in,out]	V	The aeVector2 to process.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 ScalingMatrix(aeVector2& V);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 RotationX(float theta);
		 *
		 * @brief	Creates a rotation matrix from an angle to rotate on the X axis.
		 *
		 * @param	theta	The theta.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 RotationX(float theta);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 RotationY(float theta);
		 *
		 * @brief	Creates a rotation matrix from an angle to rotate on the Y axis.
		 *
		 * @param	theta	The theta.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 RotationY(float theta);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix4 RotationZ(float theta);
		 *
		 * @brief	Creates a rotation matrix from an angle to rotate on the Z axis.
		 *
		 * @param	theta	The theta.
		 *
		 * @return	A aeMatrix4.
		 **************************************************************************************************/

		static aeMatrix4 RotationZ(float theta);
	};
}