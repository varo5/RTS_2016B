#pragma once
/************************************************************************************************************************/
/* Inclusion of the necessary header files																				*/
/************************************************************************************************************************/
#include "Vector2.h"
namespace aeCore
{
	/**********************************************************************************************//**
	 * @struct	aeVector3
	 *
	 * @brief	This structure purpose is to make mathematical operations in a 3 dimensional space.
	 *
	 * @author	Alvaro Estrada
	 * @date	14/05/2016
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeVector3
	{

		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		/// Is the union between X,Y and Z values and a 3D array.
		union
		{
			/// A structure meant to save the array as individual values.
			struct {
				float x, y, z;
			};
			/// A 3D float array.
			float v[3];
		};

		/************************************************************************************************************************/
		/* Constructors                                                        													*/
		/************************************************************************************************************************/
		aeVector3();
		~aeVector3();

		///Receives another vector and copies its values.
		aeVector3(const aeVector3 & V);
		///Receives the X, Y and Z values.
		aeVector3(float X, float Y = 0, float Z = 0);

		//Do to a linker error, the definitions are made here
		/***********************************************************************************************************************/
		/* Declaration of arithmetic operators						          												*/
		/***********************************************************************************************************************/
		aeVector3 operator*(aeVector3& V);
		aeVector3 operator+(aeVector3& V);
		aeVector3 operator-(aeVector3& V);
		aeVector3 operator/(aeVector3& V);
		aeVector3 operator*(float S);
		aeVector3 operator/(float S);

		/************************************************************************************************************************/
		/* Declaration of logic operators			               															*/
		/************************************************************************************************************************/
		bool operator==(aeVector3& V);
		bool operator!=(aeVector3& V);

		/***********************************************************************************************************************/
		/* Declaration of compound assignment operators			               												*/
		/***********************************************************************************************************************/
		aeVector3& operator+=(aeVector3& V);
		aeVector3& operator-=(aeVector3& V);
		aeVector3& operator*=(aeVector3& V);
		aeVector3& operator/=(aeVector3& V);
		aeVector3& operator*=(float S);
		aeVector3& operator/=(float S);

		/************************************************************************************************************************/
		/* Functions declaration                                            													*/
		/************************************************************************************************************************/
	public:
		/**********************************************************************************************//**
		 * @fn	bool CloseEnough(aeVector3& V, float Range);
		 *
		 * @brief	It says if a point is close enough of another point.
		 * 			
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 * @param	Range	 	The range.
		 *
		 * @return	true if it's close enough, false if it's too far
		 * 			.
		 **************************************************************************************************/

		bool CloseEnough(aeVector3& V, float Range);

		/**********************************************************************************************//**
		 * @fn	float Magnitude();
		 *
		 * @brief	Return the scalar value of the vector in form of a floating number.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float Magnitude();

		/**********************************************************************************************//**
		 * @fn	float DotProduct(aeVector3& V);
		 *
		 * @brief	Returns the dot product between this vector and the input.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float DotProduct(aeVector3& V);

		/**********************************************************************************************//**
		 * @fn	float AngleBetweenVectors(aeVector3& V);
		 *
		 * @brief	Returns the angle between vectors.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float AngleBetweenVectors(aeVector3& V);

		/**********************************************************************************************//**
		 * @fn	float Cross2Product(aeVector3& V);
		 *
		 * @brief	Returns the cross product between vectors as they were 2D.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float Cross2Product(aeVector3& V);

		/**********************************************************************************************//**
		 * @fn	float ScalarProjection(aeVector3& V);
		 *
		 * @brief	Returns the magnitude of the shadow left by another vector on top of this vector.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float ScalarProjection(aeVector3& V);

		/**********************************************************************************************//**
		 * @fn	aeVector3 Cross3Product(aeVector3& V);
		 *
		 * @brief	Returns the cross product between vectors.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A aeVector3.
		 **************************************************************************************************/

		aeVector3 Cross3Product(aeVector3& V);

		/**********************************************************************************************//**
		 * @fn	aeVector3 Normalize();
		 *
		 * @brief	Returns the direction of this vector.
		 *
		 * @return	A aeVector3.
		 **************************************************************************************************/

		aeVector3 Normalize();

		/**********************************************************************************************//**
		 * @fn	aeVector3 VectorProjection(aeVector3& V);
		 *
		 * @brief	Returns the shadow left by another vector on top of this vector.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A aeVector3.
		 **************************************************************************************************/

		aeVector3 VectorProjection(aeVector3& V);

		/**********************************************************************************************//**
		 * @fn	aeVector3 AnglesBetweenVectors(aeVector3& V);
		 *
		 * @brief	Returns the angles between vectors as they were 2D.
		 *
		 * @param [in,out]	V	The aeVector3 to process.
		 *
		 * @return	A aeVector3.
		 **************************************************************************************************/

		aeVector3 AnglesBetweenVectors(aeVector3& V);
	};
}