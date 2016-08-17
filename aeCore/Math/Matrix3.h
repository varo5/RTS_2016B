#pragma once
/************************************************************************************************************************/
/* Inclusion of the necessary header files																				*/
/************************************************************************************************************************/
#include "Matrix2.h"
namespace aeCore
{
	/**********************************************************************************************//**
	 * @struct	aeMatrix3
	 *
	 * @brief	This structure is a 3x3 matrix of float values.
	 *
	 * @author	Alvaro Estrada
	 * @date	14/05/2016
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeMatrix3
	{
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		/// Is the union between individual values and their array and matrix form.
		union {
			/// A structure meant to save the matrix as individual values.
			struct {
				float m_f00, m_f01, m_f02;
				float m_f10, m_f11, m_f12;
				float m_f20, m_f21, m_f22;
			};
			/// A 9 times float array.
			float v[9];
			/// A 3x3 float array
			float m[3][3];
		};

		/************************************************************************************************************************/
		/* Constructors                                                        													*/
		/************************************************************************************************************************/
		aeMatrix3();
		~aeMatrix3();
		///Create a copy of another 2x2 matrix.
		aeMatrix3(const aeMatrix3& ReferenceMatrix);
		///Create a new Matrix from given values.
		aeMatrix3(float _00, float _01 = 0, float _02 = 0,
			float _10 = 0, float _11 = 1, float _12 = 0,
			float _20 = 0, float _21 = 0, float _22 = 1);

		/************************************************************************************************************************/
		/* Vectors inside the matrix related functions.					          												*/
		/************************************************************************************************************************/
		void SetCol(aeVector3& ReferenceVector, int ColumnNumber);
		void SetRow(aeVector3& ReferenceVector, int RowNumber);
		aeVector3 GetCol(int ColumnNumber);
		aeVector3 GetRow(int RowNumber);

		/************************************************************************************************************************/
		/* Declaration of arithmetic operators								     												*/
		/************************************************************************************************************************/
		aeVector3 operator*(aeVector3& ReferenceVector);
		aeMatrix3 operator+(aeMatrix3& ReferenceMatrix);
		aeMatrix3 operator-(aeMatrix3& ReferenceMatrix);
		aeMatrix3 operator*(aeMatrix3& ReferenceMatrix);
		aeMatrix3 operator*(float Coefficient);
		aeMatrix3 operator/(float Divider);

		/************************************************************************************************************************/
		/* Declaration of compound assignment operators						    												*/
		/************************************************************************************************************************/
		aeMatrix3 operator+=(aeMatrix3& ReferenceMatrix);
		aeMatrix3 operator-=(aeMatrix3& ReferenceMatrix);
		aeMatrix3 operator*=(aeMatrix3& ReferenceMatrix);
		aeMatrix3 operator*=(float Coefficient);
		aeMatrix3 operator/=(float Divider);

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
		 * @fn	aeVector3 Cramer(aeVector3& ReferenceVector);
		 *
		 * @brief	Uses Cramer's rule for the solution of an equation system.
		 *
		 * @param [in,out]	ReferenceVector	The reference vector.
		 *
		 * @return	A aeVector3.
		 **************************************************************************************************/

		aeVector3 Cramer(aeVector3& ReferenceVector);

		/**********************************************************************************************//**
		 * @fn	aeMatrix3 Transpose();
		 *
		 * @brief	Obtain the transposed matrix of this matrix.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		aeMatrix3 Transpose();

		/**********************************************************************************************//**
		 * @fn	aeMatrix3 Cofactor();
		 *
		 * @brief	Obtains the cofactor matrix of this matrix.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		aeMatrix3 Cofactor();

		/**********************************************************************************************//**
		 * @fn	aeMatrix3 Adjunct();
		 *
		 * @brief	Obtains the adjunct matrix of this matrix.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		aeMatrix3 Adjunct();

		/**********************************************************************************************//**
		 * @fn	aeMatrix3 Inverse();
		 *
		 * @brief	Obtains the transposed matrix of this matrix.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		aeMatrix3 Inverse();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 Zero();
		 *
		 * @brief	Returns an empty matrix.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 Zero();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 Identity();
		 *
		 * @brief	Returns an identity matrix.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 Identity();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 TranslationMatrix(aeVector3& TranslationVector);
		 *
		 * @brief	Creates a translation matrix from a vector.
		 *
		 * @param [in,out]	TranslationVector	The translation vector.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 TranslationMatrix(aeVector3& TranslationVector);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 TranslationMatrix(aeVector2& TranslationVector);
		 *
		 * @brief	Creates a translation matrix from a vector.
		 *
		 * @param [in,out]	TranslationVector	The translation vector.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 TranslationMatrix(aeVector2& TranslationVector);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 TranslationMatrix(float X, float Y);
		 *
		 * @brief	Creates a translation matrix from 2 parameters.
		 *
		 * @param	X	The X coordinate.
		 * @param	Y	The Y coordinate.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 TranslationMatrix(float X, float Y);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 ScalingMatrix(aeVector3& ScaleVector);
		 *
		 * @brief	Creates a scaling matrix from a vector.
		 *
		 * @param [in,out]	ScaleVector	The scale factor.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 ScalingMatrix(aeVector3& ScaleVector);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 ScalingMatrix(aeVector2& ScaleVector);
		 *
		 * @brief	Creates a scaling matrix from a vector.
		 *
		 * @param [in,out]	ScaleVector	The scale factor.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 ScalingMatrix(aeVector2& ScaleVector);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 ScalingMatrix(float ScaleFactor);
		 *
		 * @brief	Creates a scaling matrix from a scale factor.
		 *
		 * @param	ScaleFactor	The scale factor.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 ScalingMatrix(float ScaleFactor);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 ScalingMatrix(float x, float y);
		 *
		 * @brief	Creates a scaling matrix from 2 scale factors.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 ScalingMatrix(float x, float y);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 RotationX(float theta);
		 *
		 * @brief	Creates a rotation matrix from an angle to rotate on the X axis.
		 *
		 * @param	theta	The radians of rotation.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 RotationX(float theta);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 RotationY(float theta);
		 *
		 * @brief	Creates a rotation matrix from an angle to rotate on the Y axis.
		 *
		 * @param	theta	The radians of rotation.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 RotationY(float theta);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix3 RotationZ(float theta);
		 *
		 * @brief	Creates a rotation matrix from an angle to rotate on the Z axis.
		 *
		 * @param	theta	The radians of rotation.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix3 RotationZ(float theta);
	};
}



