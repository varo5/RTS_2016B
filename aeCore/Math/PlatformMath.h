/**********************************************************************************************//**
 * @file	Math\PlatformMath.h
 *
 * @brief	Declares the platform mathematics class.
 *****************
 * 
 *********************************************************************************/

#include "dll_definition.h"

#pragma once
 /************************************************************************************************************************/
 /* Common use math constants																							*/
 /************************************************************************************************************************/
#undef  PI
#define PI 						(3.1415926535897932f)		/*!< PI constant */
#define SMALL_NUMBER			(1.e-8f)					/*!< "Small number" definition */
#define KINDA_SMALL_NUMBER		(1.e-4f)					/*!< "Kinda small number" definition*/
#define BIG_NUMBER				(3.4e+38f)					/*!< "Big number" definition */
#define EULERS_NUMBER			(2.71828182845904523536f)	/*!< Euler�Mascheroni constant */

#define MAX_FLT					3.402823466e+38F			/*!< Max value of a float (copy of float.h) */

#define INV_PI					(0.31830988618f)			/*!< Inverse of PI (1/PI) */
#define HALF_PI					(1.57079632679f)			/*!< Half PI */

#define DELTA					(0.00001f)					/*!< Magic number used for math precision */

 /************************************************************************************************************************/
 /* Longitud de vectores normalizados (estos son la mitad de sus valores m�ximos para asegurarnos que los productos		*/
 /* punto con vectores normalizados no se desborden																		*/
 /************************************************************************************************************************/
#define FLOAT_NORMAL_THRESH		(0.0001f)					/*!<  */

 /************************************************************************************************************************/
 /* N�meros m�gicos usado para presici�n matem�tica                                                                     	*/
 /************************************************************************************************************************/
#define THRESH_POINT_ON_PLANE			(0.10f)				/*!< Thickness del plano para pruebas de front/back/inside */
#define THRESH_POINT_ON_SIDE			(0.20f)				/*!< "Grosor" de los planos laterales de un pol�gono para pruebas point-inside/outside/on side */
#define THRESH_POINTS_ARE_SAME			(0.00002f)			/*!< Dos puntos son el mismo si est�n dentro de esta distancia */
#define THRESH_POINTS_ARE_NEAR			(0.015f)			/*!< Dos puntos est�n cerca si est�n dentro de esta distancia y pueden ser convinados si la matem�tica imprecisa est� de acuerdo */
#define THRESH_NORMALS_ARE_SAME			(0.00002f)			/*!< Dos puntos normalizados son el mismo si est�n dentro de esta distancia (Hacer este n�mero muy grande resulta en clasificaci�n CSG incorrecta y en un desastre) */
#define THRESH_VECTORS_ARE_NEAR			(0.0004f)			/*!< Dos vectores est�n cerca si est�n dentro de esta distancia y pueden ser convinados si la matem�tica imprecisa est� de acuerdo (Hacer este n�mero muy grande resulta en problemas de iluminaci�n debido a coordenadas de textura imprecisas) */
#define THRESH_SPLIT_POLY_WITH_PLANE	(0.25f)				/*!< Un plano divide a un pol�gono a la mitad */
#define THRESH_SPLIT_POLY_PRECISELY		(0.01f)				/*!< Un plano divide exactamente por la mitad a un pol�gono */
#define THRESH_ZERO_NORM_SQUARED		(0.0001f)			/*!< Tama�o de una unidad normalizada que es considerada "zero" al cuadrado */
#define THRESH_VECTORS_ARE_PARALLEL		(0.02f)				/*!< Los vectores son paralelos si el producto punto varia en menos que esto */

 /************************************************************************************************************************/
 /* Funciones y objetos utilizados para la generaci�n de n�meros Random													*/
 /************************************************************************************************************************/
#define RANDOM_CONSTANT_A 196314165		//Primera constante de periodo
#define RANDOM_CONSTANT_B 907633515		//Segunda constante de periodo

namespace aeCore
{
	/************************************************************************************************************************/
	/* Divisiones por Bit shifts                                   															*/
	/************************************************************************************************************************/
	static FORCEINLINE int32 DivX2(int32 Val) { return Val >> 1; }
	static FORCEINLINE int32 MulX2(int32 Val) { return Val << 1; }
	static FORCEINLINE int32 DivX4(int32 Val) { return Val >> 2; }
	static FORCEINLINE int32 MulX4(int32 Val) { return Val << 2; }

	/************************************************************************************************************************/
	/* Declaraci�n de funciones matem�ticas para la plataforma              												*/
	/************************************************************************************************************************/
	static FORCEINLINE int32 Trunc(float F) { return (int32)F; }
	static FORCEINLINE float TruncFloat(float F) { return (float)Trunc(F); }
	static FORCEINLINE int32 Floor(float F) { return Trunc(floorf(F)); }
	static FORCEINLINE int32 Round(float F) { return Floor(F + 0.5f); }
	static FORCEINLINE int32 Ceil(float F) { return Trunc(ceilf(F)); }
	static FORCEINLINE float Fractional(float Value) { return Value - TruncFloat(Value); }								//Regresa la parte fraccional de un flotante
	static FORCEINLINE float Exp(float Value) { return expf(Value); }
	static FORCEINLINE float Loge(float Value) { return logf(Value); }
	static FORCEINLINE float LogX(float Base, float Value) { return Loge(Value) / Loge(Base); }
	static FORCEINLINE float Fmod(float X, float Y) { return fmodf(X, Y); }
	static FORCEINLINE float Sin(float Value) { return sinf(Value); }
	static FORCEINLINE float Asin(float Value) { return asinf((Value < -1.f) ? -1.f : ((Value < 1.f) ? Value : 1.f)); }
	static FORCEINLINE float Cos(float Value) { return cosf(Value); }
	static FORCEINLINE float Acos(float Value) { return acosf((Value < -1.f) ? -1.f : ((Value < 1.f) ? Value : 1.f)); }
	static FORCEINLINE float Tan(float Value) { return tanf(Value); }
	static FORCEINLINE float Atan(float Value) { return atanf(Value); }
	static FORCEINLINE float Atan2(float Y, float X) { return atan2f(Y, X); }
	static FORCEINLINE float Sqrt(float Value) { return sqrtf(Value); }
	static FORCEINLINE float Pow(float A, float B) { return powf(A, B); }
	static FORCEINLINE float InvSqrt(float F) { return 1.0f / sqrtf(F); }
	static FORCEINLINE float InvSqrtEst(float F) { return InvSqrt(F); }
	static FORCEINLINE bool IsNaN(float A) { return ((*(uint32*)&A) & 0x7FFFFFFF) > 0x7F800000; }
	static FORCEINLINE bool IsFinite(float A) { return ((*(uint32*)&A) & 0x7F800000) != 0x7F800000; }
	static FORCEINLINE bool IsNegativeFloat(const float& F1) { return ((*(uint32*)&F1) >= (uint32)0x80000000); }



	/************************************************************************************************************************/
	/* Funciones de Random dependientes del sistema operativo																*/
	/************************************************************************************************************************/
	static FORCEINLINE void RandInit(int32 Seed) { srand(Seed); }
	static FORCEINLINE int32 Rand() { return rand(); }
	static FORCEINLINE float FRand() { return rand() / (float)RAND_MAX; }

	/************************************************************************************************************************/
	/* Funciones de Random propias																							*/
	/************************************************************************************************************************/
	extern void	LIBRARY_EXPORT RNGInit(int32 Seed);
	extern uint32 LIBRARY_EXPORT  UIRand();
	extern int32 LIBRARY_EXPORT IRand();
	extern float LIBRARY_EXPORT  FRandU();

	/************************************************************************************************************************/
	/* Regresa un n�mero random entre [0..A)																				*/
	/************************************************************************************************************************/
	extern int32 LIBRARY_EXPORT RandHelper(int32 A);

	/************************************************************************************************************************/
	/* Funci�n de ayuda. Regresa un n�mero random >= Min y <=Max															*/
	/************************************************************************************************************************/
	extern int32 LIBRARY_EXPORT RandRange(int32 Min, int32 Max);

	/************************************************************************************************************************/
	/* Utilidad para generar un n�mero random en un rango																	*/
	/************************************************************************************************************************/
	extern float LIBRARY_EXPORT FRandRange(float InMin, float InMax);

	/************************************************************************************************************************/
	/* Funciones de random con la forma polar de la transformaci�n Box-Muller												*/
	/************************************************************************************************************************/
	extern void LIBRARY_EXPORT GaussRandomPair(float& result_a, float& result_b, float dMean = 0.0f, float dStdDeviation = 1.0f);
	extern float LIBRARY_EXPORT GaussRandom(float dMean = 0.0f, float dStdDeviation = 1.0f);

	extern double LIBRARY_EXPORT ZigguratRandom();
	extern double LIBRARY_EXPORT ZigguratNRandom();

	/************************************************************************************************************************/
	/* Implementaci�n de las funciones matem�ticas																			*/
	/************************************************************************************************************************/
	static FORCEINLINE uint32 FloorLog2(uint32 Value)
	{
		uint32 Bit = 32;
		for (; Bit > 0;)
		{
			Bit--;
			if (Value & (1 << Bit))
			{
				break;
			}
		}
		return Bit;
	}

	static FORCEINLINE uint32 CountLeadingZeros(uint32 Value)
	{
		if (Value == 0) return 32;
		return 31 - FloorLog2(Value);
	}

	static FORCEINLINE uint32 CeilLogTwo(uint32 Arg)
	{
		int32 Bitmask = ((int32)(CountLeadingZeros(Arg) << 26)) >> 31;
		return (32 - CountLeadingZeros(Arg - 1)) & (~Bitmask);
	}

	static FORCEINLINE uint32 RoundUpToPowerOfTwo(uint32 Arg)
	{
		return 1 << CeilLogTwo(Arg);
	}

	static  FORCEINLINE float FloatSelect(float Comparand, float ValueGEZero, float ValueLTZero)
	{
		return Comparand >= 0.f ? ValueGEZero : ValueLTZero;
	}

	static  FORCEINLINE double FloatSelect(double Comparand, double ValueGEZero, double ValueLTZero)
	{
		return Comparand >= 0.f ? ValueGEZero : ValueLTZero;
	}

	template< class T >
	static  FORCEINLINE T Abs(const T A)
	{
		return (A >= (T)0) ? A : -A;
	}

	template< class T >
	static  FORCEINLINE T Sign(const T A)
	{
		return (A > (T)0) ? (T)1 : ((A < (T)0) ? (T)-1 : (T)0);
	}

	template< class T >
	static  FORCEINLINE T Max(const T A, const T B)
	{//Regresa el m�ximo de dos valores
		return (A >= B) ? A : B;
	}

	template< class T >
	static  FORCEINLINE T Min(const T A, const T B)
	{//Regresa el m�nimo de dos valores
		return (A <= B) ? A : B;
	}

	template< class T >
	static FORCEINLINE T Max3(const T A, const T B, const T C)
	{//Regresa el m�ximo de 3 valores
		return Max(Max(A, B), C);
	}

	template< class T >
	static FORCEINLINE T Min3(const T A, const T B, const T C)
	{//Regresa el m�nimo de tres valores
		return Min(Min(A, B), C);
	}

	template< class T >
	static FORCEINLINE T Square(const T A)
	{//Regresa el cuadrado de un n�mero
		return A*A;
	}

	template< class T >
	static FORCEINLINE T Clamp(const T X, const T Min, const T Max)
	{//Hace un clamp a X para que est� dentro de los valores Min y Max, esta funci�n es inclusiva
		return X < Min ? Min : X < Max ? X : Max;
	}

	static FORCEINLINE float GridSnap(float Location, float Grid)
	{//Cambia el valor de una variable al m�ltiplo del grid m�s cercano
		if (Grid == 0.f) return Location;
		else
		{
			return Floor((Location + 0.5f*Grid) / Grid)*Grid;
		}
	}

	static FORCEINLINE uint32 DivideAndRoundUp(uint32 Dividend, uint32 Divisor)
	{//Divide dos enteros y redondea el resultado
		return (Dividend + Divisor - 1) / Divisor;
	}

	static FORCEINLINE float Log2(float Value)
	{//Log base 2
	 //Valor cacheado para conversiones r�pidas
		static const float LogToLog2 = 1.f / Loge(2.f);

		//Ejecutamos el log espec�fico a la plataforma y convertimos usando el valor cacheado
		return Loge(Value) * LogToLog2;
	}

	/************************************************************************************************************************/
	/* Especializaci�n para flotantes                                       												*/
	/************************************************************************************************************************/
	template<>
	static FORCEINLINE float Abs(const float A)
	{
		return fabsf(A);
	}

	/************************************************************************************************************************/
	/* Funciones predicados																									*/
	/************************************************************************************************************************/

	/************************************************************************************************************************/
	/* Revisa si un valor est� dentro del rango, exclusivo en MaxValue														*/
	/************************************************************************************************************************/
	template< class U >
	static FORCEINLINE bool IsWithin(const U& TestValue, const U& MinValue, const U& MaxValue)
	{
		return ((TestValue >= MinValue) && (TestValue < MaxValue));
	}

	/************************************************************************************************************************/
	/* Revisa si un valor est� dentr de un rango, inclusivo en MaxValue														*/
	/************************************************************************************************************************/
	template< class U >
	static FORCEINLINE bool IsWithinInclusive(const U& TestValue, const U& MinValue, const U& MaxValue)
	{
		return ((TestValue >= MinValue) && (TestValue <= MaxValue));
	}

	/************************************************************************************************************************/
	/* Revisa si dos n�meros con punto flotante son casi iguales															*/
	/*	@param A				Primer n�mero a comparar																	*/
	/*	@param B				Segundo n�mero a comparar																	*/
	/*	@param ErrorTolerance	M�xima diferencia permitida para considerarlos como "casi iguales"							*/
	/*	@return					true si A y B son casi iguales																*/
	/************************************************************************************************************************/
	static FORCEINLINE bool IsNearlyEqual(float A, float B, float ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<float>(A - B) < ErrorTolerance;
	}

	/************************************************************************************************************************/
	/* Revisa si dos n�meros con punto flotante son casi iguales															*/
	/*	@param A				Primer n�mero a comparar																	*/
	/*	@param B				Segundo n�mero a comparar																	*/
	/*	@param ErrorTolerance	M�xima diferencia permitida para considerarlos como "casi iguales"							*/
	/*	@return					true si A y B son casi iguales																*/
	/************************************************************************************************************************/
	static FORCEINLINE bool IsNearlyEqual(double A, double B, double ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<double>(A - B) < ErrorTolerance;
	}

	/************************************************************************************************************************/
	/* Revisa si dos n�meros con punto flotante son casi zero																*/
	/*	@param Value			N�mero a comparar																			*/
	/*	@param ErrorTolerance	M�xima diferencia permitida para considerar que el valor es "casi zero"						*/
	/*	@return					true si Value es casi zero																	*/
	/************************************************************************************************************************/
	static FORCEINLINE bool IsNearlyZero(float Value, float ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<float>(Value) < ErrorTolerance;
	}

	/************************************************************************************************************************/
	/* Revisa si dos n�meros con punto flotante son casi zero																*/
	/*	@param Value			N�mero a comparar																			*/
	/*	@param ErrorTolerance	M�xima diferencia permitida para considerar que el valor es "casi zero"						*/
	/*	@return					true si Value es casi zero																	*/
	/************************************************************************************************************************/
	static FORCEINLINE bool IsNearlyZero(double Value, double ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<double>(Value) < ErrorTolerance;
	}

	/************************************************************************************************************************/
	/* Revisa si un n�mero es una potencia de dos																			*/
	/************************************************************************************************************************/
	static FORCEINLINE bool IsPowerOfTwo(uint32 Value)
	{
		return ((Value & (Value - 1)) == 0);
	}

	/************************************************************************************************************************/
	/* Funciones de conversi�n																								*/
	/************************************************************************************************************************/

	/************************************************************************************************************************/
	/* Convierte radianes a grados																							*/
	/************************************************************************************************************************/
	template<class T>
	static FORCEINLINE T RadiansToDegrees(T const& RadVal)
	{
		return RadVal * (180.f / PI);
	}

	/************************************************************************************************************************/
	/* Convierte grados a radianes																							*/
	/************************************************************************************************************************/
	template<class T>
	static FORCEINLINE T DegreesToRadians(T const& DegVal)
	{
		return DegVal * (PI / 180.f);
	}

	/************************************************************************************************************************/
	/* Limita un �ngulo arbitrario a que est� entre los �ngulos dados. Limitar� a el borde m�s cercano						*/
	/* @param MinAngleDegrees	�ngulo que define el inicio del rango de �ngulos v�lidos (barrido clockwise)				*/
	/* @param MaxAngleDegrees	�ngulo que define el final del rango de �ngulos v�lidos										*/
	/* @return Regresa el �ngulo limitado en el rango de -180..180.															*/
	/************************************************************************************************************************/
	static float ClampAngle(float AngleDegrees, float MinAngleDegrees, float MaxAngleDegrees);

	/************************************************************************************************************************/
	/* Gets map to screen coordinates																						*/
	/************************************************************************************************************************/
	extern aePoint LIBRARY_EXPORT GetMapToScreenCoords(aeVector2 Point, aeVector2 CameraPosition, aeRect ScreenPrecalc, bool Isometric);
	/************************************************************************************************************************/
	/* Gets screen to map coordinates																						*/
	/************************************************************************************************************************/
	extern aeVector2 LIBRARY_EXPORT GetScreenToMapCoords(aePoint Point, aeVector2 CameraPosition, aeRect ScreenPrecalc, bool Isometric);

	extern float LIBRARY_EXPORT Fade(float t);

	extern float LIBRARY_EXPORT Lerp(float Start, float End, float Porcentage);

	extern float LIBRARY_EXPORT Grad(int hash, float x, float y, float z);
}