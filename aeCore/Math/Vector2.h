#pragma once
/************************************************************************************************************************/
/* Inclusion of the necessary header files																				*/
/************************************************************************************************************************/
#include <cmath>

namespace aeCore
{
	/**********************************************************************************************//**
	 * @struct	aeVector2
	 *
	 * @brief	This structure purpose is to make mathematical operations in a 2 dimensional space.
	 *
	 * @author	Alvaro Estrada
	 * @date	14/05/2016
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeVector2
	{
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		float x, y;

		/************************************************************************************************************************/
		/* Constructors declaration                                            													*/
		/************************************************************************************************************************/
		aeVector2();
		~aeVector2();

		///Receives another vector and copies its values.
		aeVector2(const aeVector2& V);
		///Receives the X and Y values.
		aeVector2(float X, float Y);

		/***********************************************************************************************************************/
		/* Declaration of arithmetic operators							          												*/
		/***********************************************************************************************************************/
		aeVector2 operator*(aeVector2& V);
		aeVector2 operator+(aeVector2& V);
		aeVector2 operator-(aeVector2& V);
		aeVector2 operator/(aeVector2& V);
		aeVector2 operator*(float S);
		aeVector2 operator/(float S);
		///Is the same as using the dot product function.
		float operator|(aeVector2& V);
		///Is the same as using the cross product function.
		float operator^(aeVector2& V);

		/***********************************************************************************************************************/
		/* Declaration of compound assignment operators			               												*/
		/***********************************************************************************************************************/
		aeVector2& operator+=(aeVector2& V);
		aeVector2& operator-=(aeVector2& V);
		aeVector2& operator*=(aeVector2& V);
		aeVector2& operator/=(aeVector2& V);
		aeVector2& operator*=(float S);
		aeVector2& operator/=(float S);

		/************************************************************************************************************************/
		/* Declaration of logic operators			               																*/
		/************************************************************************************************************************/
		bool operator==(aeVector2& V);
		bool operator!=(aeVector2& V);

		/************************************************************************************************************************/
		/* Functions declaration                                            													*/
		/************************************************************************************************************************/
	public:

		/**********************************************************************************************//**
		 * @fn	bool CloseEnough(aeVector2& V, float Range);
		 *
		 * @brief	It says if a point is close enough of another point.
		 * 			
		 *
		 * @param [in,out]	V	The aeVector2 to process.
		 * @param	Range	 	The range.
		 *
		 * @return	true if it's close enough, false if it's too far
		 * 			.
		 **************************************************************************************************/

		bool CloseEnough(aeVector2& V, float Range);

		/**********************************************************************************************//**
		 * @fn	float Magnitude();
		 *
		 * @brief	Returns the scalar value of the vector in form of a floating number.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float Magnitude();

		/**********************************************************************************************//**
		 * @fn	float DotProduct(aeVector2& V);
		 *
		 * @brief	Returns the sum of the products of the corresponding entries.
		 *
		 * @param [in,out]	V	The aeVector2 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float DotProduct(aeVector2& V);

		/**********************************************************************************************//**
		 * @fn	float AngleBetweenVectors(aeVector2& V);
		 *
		 * @brief	Returns the angle between vectors in rads.
		 *
		 * @param [in,out]	V	The aeVector2 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float AngleBetweenVectors(aeVector2& V);

		/**********************************************************************************************//**
		 * @fn	float CrossProduct(aeVector2& V);
		 *
		 * @brief	Returns the value of the resulting vector that is perpendicular to both entries, with
		 * 			a direction given by the right - hand rule and a magnitude equal to the area of the
		 * 			parallelogram that the vectors span.
		 *
		 * @param [in,out]	V	The aeVector2 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float CrossProduct(aeVector2& V);

		/**********************************************************************************************//**
		 * @fn	float ScalarProjection(aeVector2& V);
		 *
		 * @brief	Returns the magnitude of the shadow left by another vector on top of this vector.
		 *
		 * @param [in,out]	V	The aeVector2 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float ScalarProjection(aeVector2& V);

		/**********************************************************************************************//**
		 * @fn	aeVector2 Normalize();
		 *
		 * @brief	Returns the direction of this vector.
		 *
		 * @return	A aeVector2.
		 **************************************************************************************************/

		aeVector2 Normalize();

		/**********************************************************************************************//**
		 * @fn	aeVector2 VectorProjection(aeVector2& V);
		 *
		 * @brief	Returns the shadow left by another vector on top of this vector.
		 *
		 * @param [in,out]	V	The aeVector2 to process.
		 *
		 * @return	A aeVector2.
		 **************************************************************************************************/

		aeVector2 VectorProjection(aeVector2& V);
	};
}
