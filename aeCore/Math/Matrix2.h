#pragma once
/************************************************************************************************************************/
/* Inclusion of the necessary header files																				*/
/************************************************************************************************************************/
#include "Vector4.h"
namespace aeCore 
{
	/**********************************************************************************************//**
	 * @struct	aeMatrix2
	 *
	 * @brief	This structure is a 2x2 matrix of float values. This is an old structure, better use aeMatrix3.
	 *
	 * @author	Alvaro Estrada
	 * @date	14/05/2016
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeMatrix2
	{
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		float m_f00, m_f01, m_f10, m_f11;

		/************************************************************************************************************************/
		/* Constructors                                                        													*/
		/************************************************************************************************************************/
		aeMatrix2();
		~aeMatrix2();

		///Create a copy of another 2x2 matrix.
		aeMatrix2(const aeMatrix2& ReferenceMatrix);
		///Create a new Matrix from given values.
		aeMatrix2(float MatrixPosition00, float MatrixPosition01, float MatrixPosition10, float MatrixPosition11);

		/************************************************************************************************************************/
		/* Vectors inside the matrix related functions.					          												*/
		/************************************************************************************************************************/
		void SetCol(aeVector2& ReferenceVector, int ColumnNumber);
		void SetRow(aeVector2& ReferenceVector, int RowNumber);
		aeVector2 GetCol(int ColumnNumber);
		aeVector2 GetRow(int RowNumber);

		/************************************************************************************************************************/
		/* Implementation of arithmetic operators						          												*/
		/************************************************************************************************************************/
		aeVector2 operator*(aeVector2& ReferenceVector);
		aeMatrix2 operator+(aeMatrix2& ReferenceMatrix);
		aeMatrix2 operator-(aeMatrix2& ReferenceMatrix);
		aeMatrix2 operator*(aeMatrix2& ReferenceMatrix);
		aeMatrix2 operator*(float Coefficient);
		aeMatrix2 operator/(float Divider);

		/************************************************************************************************************************/
		/* Implementation of compound assignment operators			               												*/
		/************************************************************************************************************************/
		aeMatrix2 operator+=(aeMatrix2& ReferenceMatrix);
		aeMatrix2 operator-=(aeMatrix2& ReferenceMatrix);
		aeMatrix2 operator*=(aeMatrix2& ReferenceMatrix);
		aeMatrix2 operator*=(float Coefficient);
		aeMatrix2 operator/=(float Divider);

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
		 * @fn	aeVector2 Cramer(aeVector2& ReferenceVector);
		 *
		 * @brief	Uses Cramer's rule for the solution of an equation system.
		 *
		 * @param [in,out]	ReferenceVector	The reference vector.
		 *
		 * @return	A aeVector2.
		 **************************************************************************************************/

		aeVector2 Cramer(aeVector2& ReferenceVector);

		/**********************************************************************************************//**
		 * @fn	aeMatrix2 Transpose();
		 *
		 * @brief	Obtain the transposed matrix of this matrix.
		 *
		 * @return	A aeMatrix2.
		 **************************************************************************************************/

		aeMatrix2 Transpose();

		/**********************************************************************************************//**
		 * @fn	aeMatrix2 Cofactor();
		 *
		 * @brief	Obtains the cofactor matrix of this matrix.
		 *
		 * @return	A aeMatrix2.
		 **************************************************************************************************/

		aeMatrix2 Cofactor();

		/**********************************************************************************************//**
		 * @fn	aeMatrix2 Adjunct();
		 *
		 * @brief	Obtains the adjunct matrix of this matrix.
		 *
		 * @return	A aeMatrix2.
		 **************************************************************************************************/

		aeMatrix2 Adjunct();

		/**********************************************************************************************//**
		 * @fn	aeMatrix2 Inverse();
		 *
		 * @brief	Obtains the inverse matrix of this matrix.
		 *
		 * @return	A aeMatrix2.
		 **************************************************************************************************/

		aeMatrix2 Inverse();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix2 Zero();
		 *
		 * @brief	Returns an empty matrix.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix2 Zero();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix2 Identity();
		 *
		 * @brief	Returns an identity matrix.
		 *
		 * @return	A aeMatrix3.
		 **************************************************************************************************/

		static aeMatrix2 Identity();

		/**********************************************************************************************//**
		 * @fn	static aeMatrix2 ScalingMatrix(aeVector2& ScaleVector);
		 *
		 * @brief	Creates a scaling matrix from a vector.
		 *
		 * @param [in,out]	ScaleVector	The scale vector.
		 *
		 * @return	A aeMatrix2.
		 **************************************************************************************************/

		static aeMatrix2 ScalingMatrix(aeVector2& ScaleVector);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix2 ScalingMatrix(float ScaleFactor);
		 *
		 * @brief	Creates a scaling matrix from a scale factor.
		 *
		 * @param	ScaleFactor	The scale factor.
		 *
		 * @return	A aeMatrix2.
		 **************************************************************************************************/

		static aeMatrix2 ScalingMatrix(float ScaleFactor);

		/**********************************************************************************************//**
		 * @fn	static aeMatrix2 RotationMatrix(float RadiansOfRotation);
		 *
		 * @brief	Creates a rotation matrix from an angle.
		 *
		 * @param	RadiansOfRotation	The radians of rotation.
		 *
		 * @return	A aeMatrix2.
		 **************************************************************************************************/

		static aeMatrix2 RotationMatrix(float RadiansOfRotation);

		/**********************************************************************************************//**
		 * @fn	static aeVector2 Rotate(float RadiansOfRotation, aeVector2& VectorToRotate);
		 *
		 * @brief	Returns the rotated vector given an angle.
		 *
		 * @param	RadiansOfRotation	  	The radians of rotation.
		 * @param [in,out]	VectorToRotate	The vector to rotate.
		 *
		 * @return	A aeVector2.
		 **************************************************************************************************/

		static aeVector2 Rotate(float RadiansOfRotation, aeVector2& VectorToRotate);

		/**********************************************************************************************//**
		 * @fn	static aeVector2 Rotate(aeVector2 & VectorToRotate, aeVector2 & VectorAddingRotation);
		 *
		 * @brief	Returns the rotated vector given another vector.
		 *
		 * @param [in,out]	VectorToRotate			The vector to rotate.
		 * @param [in,out]	VectorAddingRotation	The vector adding rotation.
		 *
		 * @return	A aeVector2.
		 **************************************************************************************************/

		static aeVector2 Rotate(aeVector2 & VectorToRotate, aeVector2 & VectorAddingRotation);

		/**********************************************************************************************//**
		 * @fn	static aeVector2 HomogeneousTransformation(aeVector2& VectorToTransform, aeVector2& TranslationVector,aeVector2& ScaleVector, aeVector2& VectorAddingRotation);
		 *
		 * @brief	Homogeneous transformation.
		 *
		 * @param [in,out]	VectorToTransform   	The vector to transform.
		 * @param [in,out]	TranslationVector   	The translation vector.
		 * @param [in,out]	ScaleVector				The scale vector.
		 * @param [in,out]	VectorAddingRotation	The vector adding rotation.
		 *
		 * @return	A aeVector2.
		 **************************************************************************************************/

		static aeVector2 HomogeneousTransformation(aeVector2& VectorToTransform,
			aeVector2& TranslationVector, aeVector2& ScaleVector, aeVector2& VectorAddingRotation);

		/**********************************************************************************************//**
		 * @fn	static aeVector2 HomogeneousTransformation(aeVector2& VectorToTransform, aeVector2& TranslationVector, aeVector2& ScaleVector, float RadiansOfRotation);
		 *
		 * @brief	Homogeneous transformation.
		 *
		 * @param [in,out]	VectorToTransform	The vector to transform.
		 * @param [in,out]	TranslationVector	The translation vector.
		 * @param [in,out]	ScaleVector		 	The scale vector.
		 * @param	RadiansOfRotation		 	The radians of rotation.
		 *
		 * @return	A aeVector2.
		 **************************************************************************************************/

		static aeVector2 HomogeneousTransformation(aeVector2& VectorToTransform,
			aeVector2& TranslationVector, aeVector2& ScaleVector, float RadiansOfRotation);

		/**********************************************************************************************//**
		 * @fn	static aeVector2 HomogeneousTransformation(aeVector2& VectorToTransform, aeVector2& TranslationVector,float ScaleFactor, float RadiansOfRotation);
		 *
		 * @brief	Homogeneous transformation.
		 *
		 * @param [in,out]	VectorToTransform	The vector to transform.
		 * @param [in,out]	TranslationVector	The translation vector.
		 * @param	ScaleFactor				 	The scale factor.
		 * @param	RadiansOfRotation		 	The radians of rotation.
		 *
		 * @return	A aeVector2.
		 **************************************************************************************************/

		static aeVector2 HomogeneousTransformation(aeVector2& VectorToTransform,
			aeVector2& TranslationVector, float ScaleFactor, float RadiansOfRotation);
	};
}



