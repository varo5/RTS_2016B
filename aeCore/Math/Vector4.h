#pragma once
/************************************************************************************************************************/
/* Inclusion of the necessary header files																				*/
/************************************************************************************************************************/
#include "Vector3.h"
namespace aeCore
{
	/**********************************************************************************************//**
	 * @struct	aeVector4
	 *
	 * @brief	This structure purpose is to make mathematical operations in a 4 dimensional space.
	 *
	 * @author	Alvaro Estrada
	 * @date	14/05/2016
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeVector4
	{
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		/// Is the union between X,Y and Z values and a 3D array.
		union
		{
			/// A structure meant to save the array as individual values.
			struct
			{
				float x, y, z, w;
			};
			/// A 4D float array.
			float v[4];
		};

		/************************************************************************************************************************/
		/* Constructors                                                        													*/
		/************************************************************************************************************************/
		aeVector4();
		~aeVector4();
		///Receives another vector and copies its values.
		aeVector4(const aeVector4& V);
		///Receives the X, Y, Z and W values.
		aeVector4(float X, float Y = 0, float Z = 0, float W = 0);

		/***********************************************************************************************************************/
		/* Declaration of arithmetic operators							          												*/
		/***********************************************************************************************************************/
		aeVector4 operator+(aeVector4& V);
		aeVector4 operator-(aeVector4& V);
		aeVector4 operator/(aeVector4& V);
		aeVector4 operator*(aeVector4& V);
		aeVector4 operator*(float S);
		aeVector4 operator/(float S);

		/***********************************************************************************************************************/
		/* Declaration of compound assignment operators					           												*/
		/***********************************************************************************************************************/
		aeVector4& operator+=(aeVector4& V);
		aeVector4& operator-=(aeVector4& V);
		aeVector4& operator*=(aeVector4& V);
		aeVector4& operator/=(aeVector4& V);
		aeVector4& operator*=(float S);

		/************************************************************************************************************************/
		/* Declaration of logic operators				             															*/
		/************************************************************************************************************************/
		bool operator==(aeVector4& A);
		bool operator!=(aeVector4& A);

		/************************************************************************************************************************/
		/* Functions declaration                                            													*/
		/************************************************************************************************************************/
	public:
		/**********************************************************************************************//**
		 * @fn	bool CloseEnough(aeVector4& V, float Range);
		 *
		 * @brief	It says if a point is close enough of another point.
		 * 			
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 * @param	Range	 	The range.
		 *
		 * @return	true if it's close enough, false if it's too far
		 * 			.
		 **************************************************************************************************/

		bool CloseEnough(aeVector4& V, float Range);

		/**********************************************************************************************//**
		 * @fn	float Magnitude();
		 *
		 * @brief	Return the scalar value of the vector in form of a floating number.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float Magnitude();

		/**********************************************************************************************//**
		 * @fn	float DotProduct(aeVector4& V);
		 *
		 * @brief	Returns the dot product between this vector and the input.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float DotProduct(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	float AngleBetweenVectors(aeVector4& V);
		 *
		 * @brief	Returns the angle between vectors.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float AngleBetweenVectors(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	float Cross2Product(aeVector4& V);
		 *
		 * @brief	Returns the cross product between vectors as they were 2D.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float Cross2Product(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	float ScalarProjection(aeVector4& V);
		 *
		 * @brief	Returns the magnitude of the shadow left by another vector on top of this vector.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float ScalarProjection(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	aeVector4 Cross3Product(aeVector4& V);
		 *
		 * @brief	Returns the cross product between vectors.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A aeVector4.
		 **************************************************************************************************/

		aeVector4 Cross3Product(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	aeVector4 Normalize();
		 *
		 * @brief	Returns the direction of this vector.
		 *
		 * @return	A aeVector4.
		 **************************************************************************************************/

		aeVector4 Normalize();

		/**********************************************************************************************//**
		 * @fn	aeVector4 VectorProjection(aeVector4& V);
		 *
		 * @brief	Returns the shadow left by another vector on top of this vector.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A aeVector4.
		 **************************************************************************************************/

		aeVector4 VectorProjection(aeVector4& V);

		/**********************************************************************************************//**
		 * @fn	aeVector4 AnglesBetweenVectors(aeVector4& V);
		 *
		 * @brief	Returns the angles between vectors as they were 2D.
		 *
		 * @param [in,out]	V	The aeVector4 to process.
		 *
		 * @return	A aeVector4.
		 **************************************************************************************************/

		aeVector4 AnglesBetweenVectors(aeVector4& V);
	};
}

