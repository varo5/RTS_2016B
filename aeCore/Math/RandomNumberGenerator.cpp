#include "aeCoreStd.h"
#include "RandomNumberGenerator.h"

namespace aeCore
{
	aeRandomNumberGenerator::aeRandomNumberGenerator()
	{
		bUsePrecalcedResult = false;
		SRand(time(NULL));
		m_pZigg = new aeZiggurat(this);
	}

	aeRandomNumberGenerator::~aeRandomNumberGenerator()
	{
		delete m_pZigg;
	}

	void aeRandomNumberGenerator::SRand(int32 Seed)
	{
		m_iRandomSeed = Seed;
	}

	uint32 aeRandomNumberGenerator::UIRand()
	{
		return static_cast<uint32>(m_iRandomSeed = (m_iRandomSeed * RANDOM_CONSTANT_A) + RANDOM_CONSTANT_B);
	}

	int32 aeRandomNumberGenerator::IRand()
	{
		return m_iRandomSeed = (m_iRandomSeed * RANDOM_CONSTANT_A) + RANDOM_CONSTANT_B;
	}

	float aeRandomNumberGenerator::FRandU()
	{
		return 0.5f*(((float)IRand() / (float)0x7fffffff)+1);
	}

	int32 aeRandomNumberGenerator::RandHelper(int32 A)
	{
		//RAND_MAX+1 da intervalo [0..A) con distribución non
		return A > 0 ? Trunc(IRand() / (float)((uint32)RAND_MAX + 1) * A) : 0;
	}

	int32 aeRandomNumberGenerator::RandRange(int32 Min, int32 Max)
	{
		const int32 Range = (Max - Min) + 1;
		return Min + RandHelper(Range);
	}

	float aeRandomNumberGenerator::FRandRange(float InMin, float InMax)
	{
		return InMin + (InMax - InMin) * FRandU();
	}

	void aeRandomNumberGenerator::GaussRandomPair(float & result_a, float & result_b, float dMean, float dStdDeviation)
	{
		do
		{
			x1 = 2.0f * FRandU() - 1.0f;
			x2 = 2.0f * FRandU() - 1.0f;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0f);

		w = Sqrt((-2.0f * Loge(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;

		result_a = (dMean + y1 * dStdDeviation);
		result_b = (dMean + y2 * dStdDeviation);
	}

	float aeRandomNumberGenerator::GaussRandom(float dMean, float dStdDeviation)
	{
		if (bUsePrecalcedResult)
		{
			bUsePrecalcedResult = false;
			return(dMean + precalcY2 * dStdDeviation);
		}

		//This part is an unfolded copy of the "GaussRandomPair" function, we do this just to keep this as an optimized function
		do
		{
			x1 = (2.0f * FRandU()) - 1.0f;
			x2 = (2.0f * FRandU()) - 1.0f;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0f || w == 0);

		w = Sqrt(-2.0f * Loge(w) / w);
		y1 = x1 * w;
		precalcY2 = x2 * w;

		//Set the flag to indicate that the next call to this function doesn't need to be calculated
		bUsePrecalcedResult = true;

		return(dMean + y1 * dStdDeviation);
	}

	double aeRandomNumberGenerator::Zigg()
	{
		return m_pZigg->DRand();
	}

	double aeRandomNumberGenerator::ZiggN()
	{
		return m_pZigg->UDRand();
	}

	aeZiggurat::aeZiggurat()
	{
		m_pRNG = new aeRandomNumberGenerator();
		m_bDestroy = true;
		ki.resize(ZIGGURAT_TABLE_SIZE);
		wi.resize(ZIGGURAT_TABLE_SIZE);
		fi.resize(ZIGGURAT_TABLE_SIZE);
		CreateTables();
	}

	aeZiggurat::aeZiggurat(aeRandomNumberGenerator* pRNG)
	{
		m_pRNG = pRNG;
		m_bDestroy = false;
		ki.resize(ZIGGURAT_TABLE_SIZE);
		wi.resize(ZIGGURAT_TABLE_SIZE);
		fi.resize(ZIGGURAT_TABLE_SIZE);
		CreateTables();
	}

	aeZiggurat::~aeZiggurat()
	{
		ki.clear();
		wi.clear();
		fi.clear();
		if (m_bDestroy)
			delete m_pRNG;
	}	double aeZiggurat::DRand()
	{
		while (true)
		{
			uint32 ri = m_pRNG->UIRand();
			uint8 idx = ri & 0x00FF;
			double x = ri * wi[idx];
			if (ri < ki[idx])
			{
				return x;		// 99.33% of the time we return here 1st try
			}
			else if (idx == 0)
			{
				/* As stated in Marsaglia and Tsang
				*
				* For the normal tail, the method of Marsaglia[5] provides:
				* generate x = -ln(U_1)/r, y = -ln(U_2), until y+y > x*x,
				* then return r+x. Except that r+x is always in the positive
				* tail!!!! Any thing random might be used to determine the
				* sign, but as we already have ri we might as well use it
				*/
				double xx, yy;
				do
				{
					xx = -ZIGGURAT_INV_R * log(m_pRNG->FRandU());
					yy = -log(m_pRNG->FRandU());
				} while (yy + yy <= xx*xx);
				return (ri < 0 ? -ZIGGURAT_R - xx : ZIGGURAT_R + xx);
			}
			else if ((fi[idx - 1] - fi[idx]) * m_pRNG->FRandU() + fi[idx] <
				exp(-0.5*x*x))
			{
				return x;
			}
		}
	}

	double aeZiggurat::UDRand()
	{
		double x = DRand();
		return exp(-0.5*x*x);
	}

	void aeZiggurat::CreateTables()
	{
		double x, x1;

		x1 = ZIGGURAT_R;
		wi[255] = x1 / TWO_TO_POWER_31;
		fi[255] = exp(-0.5 * x1 * x1);

		/* Index zero is special for tail strip, where Marsaglia and Tsang defines
		* this as
		* k_0 = 2^31 * r * f(r) / v, w_0 = 0.5^31 * v / f(r), f_0 = 1,
		* where v is the area of each strip of the ziggurat.
		*/
		ki[0] = (uint32) (x1 * fi[255] / SECTION_AREA * TWO_TO_POWER_31);
		wi[0] = SECTION_AREA / fi[255] / TWO_TO_POWER_31;
		fi[0] = 1;

		for (int i = 254; i > 0; i--)
		{
			/* New x is given by x = f^{-1}(v/x_{i+1} + f(x_{i+1})), thus
			* need inverse operator of y = exp(-0.5*x*x) -> x = sqrt(-2*ln(y))
			*/
			x = sqrt(-2. * log(SECTION_AREA / x1 + fi[i + 1]));
			ki[i + 1] = (uint32)(x / x1 * TWO_TO_POWER_31);
			wi[i] = x / TWO_TO_POWER_31;
			fi[i] = exp(-0.5 * x * x);
			x1 = x;
		}

		ki[1] = 0;
	}
}