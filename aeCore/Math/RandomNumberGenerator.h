#pragma once
#include "BasicClasses.h"

/************************************************************************************************************************/
/* Funciones y objetos utilizados para la generación de números Random													*/
/************************************************************************************************************************/
#define RANDOM_CONSTANT_A 196314165		//Primera constante de periodo
#define RANDOM_CONSTANT_B 907633515		//Segunda constante de periodo

#define ZIGGURAT_TABLE_SIZE 256
#define ZIGGURAT_R 3.6541528853610088
#define ZIGGURAT_INV_R 0.27366123732975828
#define TWO_TO_POWER_31 2147483648.0
#define SECTION_AREA 0.00492867323399

namespace aeCore
{
	class aeZiggurat;

	class LIBRARY_EXPORT aeRandomNumberGenerator
	{
	private:
		int32 m_iRandomSeed;
		bool bUsePrecalcedResult;
		float x1, x2, w, y1, y2;
		float precalcY2;

		aeZiggurat* m_pZigg;
	public:
		aeRandomNumberGenerator();
		~aeRandomNumberGenerator();

		/************************************************************************************************************************/
		/* Basic random functions																								*/
		/************************************************************************************************************************/
	public:

		/**********************************************************************************************//**
		 * @fn	void aeRandomNumberGenerator::SRand(int32 Seed);
		 *
		 * @brief	Randoms the given seed.
		 *
		 * @param	Seed	The seed.
		 **************************************************************************************************/

		void SRand(int32 Seed);

		/**********************************************************************************************//**
		 * @fn	uint32 aeRandomNumberGenerator::UIRand();
		 *
		 * @brief	Gets the random.
		 *
		 * @return	An uint32.
		 **************************************************************************************************/

		uint32 UIRand();

		/**********************************************************************************************//**
		 * @fn	int32 aeRandomNumberGenerator::IRand();
		 *
		 * @brief	Gets the random.
		 *
		 * @return	An int32.
		 **************************************************************************************************/

		int32 IRand();

		/**********************************************************************************************//**
		 * @fn	float aeRandomNumberGenerator::FRandU();
		 *
		 * @brief	Random u.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		float FRandU();

		/************************************************************************************************************************/
		/* Regresa un número random entre [0..A)																				*/
		/************************************************************************************************************************/
		int32 RandHelper(int32 A);

		/************************************************************************************************************************/
		/* Función de ayuda. Regresa un número random >= Min y <=Max															*/
		/************************************************************************************************************************/
		int32 RandRange(int32 Min, int32 Max);

		/************************************************************************************************************************/
		/* Utilidad para generar un número random en un rango																	*/
		/************************************************************************************************************************/
		float FRandRange(float InMin, float InMax);

		/************************************************************************************************************************/
		/* Box-Muller random functions in their polar form																		*/
		/************************************************************************************************************************/
		void GaussRandomPair(float& result_a, float& result_b, float dMean = 0.0f, float dStdDeviation = 1.0f);
		float GaussRandom(float dMean = 0.0f, float dStdDeviation = 1.0f);
		double Zigg();
		double ZiggN();
	};

	/**********************************************************************************************//**
	 * @class	aeZiggurat
	 *
	 * @brief	An ae ziggurat.
	 **************************************************************************************************/

	class LIBRARY_EXPORT aeZiggurat
	{
	public:

		/**********************************************************************************************//**
		 * @fn	aeZiggurat::aeZiggurat();
		 *
		 * @brief	Default constructor.
		 **************************************************************************************************/

		aeZiggurat();

		/**********************************************************************************************//**
		 * @fn	aeZiggurat::aeZiggurat(aeRandomNumberGenerator* pRNG);
		 *
		 * @brief	Constructor.
		 *
		 * @param [in,out]	pRNG	If non-null, the random number generator.
		 **************************************************************************************************/

		aeZiggurat(aeRandomNumberGenerator* pRNG);

		/**********************************************************************************************//**
		 * @fn	aeZiggurat::~aeZiggurat();
		 *
		 * @brief	Destructor.
		 **************************************************************************************************/

		~aeZiggurat();

		/**********************************************************************************************//**
		 * @fn	double aeZiggurat::DRand();
		 *
		 * @brief	Gets a random .
		 *
		 * @return	A double.
		 **************************************************************************************************/

		double DRand();

		/**********************************************************************************************//**
		 * @fn	double aeZiggurat::UDRand();
		 *
		 * @brief	Gets the random.
		 *
		 * @return	A double.
		 **************************************************************************************************/

		double UDRand();
	private:

		/**********************************************************************************************//**
		 * @fn	void aeZiggurat::CreateTables();
		 *
		 * @brief	Creates the tables.
		 **************************************************************************************************/

		void CreateTables();

		bool m_bDestroy;	///< A boolean to determine if to destroy or not the RNG

		aeRandomNumberGenerator* m_pRNG;	///< The random number generator

		std::vector<uint32> ki; ///< The ki
		std::vector<double> wi; ///< The wi
		std::vector<double> fi; ///< The fi
	};
}