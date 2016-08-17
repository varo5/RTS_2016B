#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>

namespace aeCore
{
	class LIBRARY_EXPORT PerlinNoise
	{
	private:
		//All the variables needed for the noise execution
		int X;
		int Y;
		int Z;
		double u;
		double v;
		double w;
		int A;
		int AA;
		int AB;
		int B;
		int BA;
		int BB;
		double res;
		// The permutation vector
		std::vector<int> p;
	public:
		
	public:
		// Initialize with the reference values for the permutation vector
		PerlinNoise();
		// Generate a new permutation vector based on the value of seed
		PerlinNoise(uint32 seed);
		// Set new seed in the perlin noise class
		void Seed(uint32 seed);
		// Get a noise value in 3D
		double Noise(double x, double y, double z);
	private:
		double fade(double t);
		double lerp(double t, double a, double b);
		double grad(int hash, double x, double y, double z);
	};

	class LIBRARY_EXPORT FractalNoise
	{
	public:
		FractalNoise();
		FractalNoise(unsigned long seed);
		~FractalNoise();

		// Returns a noise value, typically in the range -1 to 1, given a 3D sample position.
		double Noise(double sample_x, double sample_y, double sample_z);

		// Set new seed in the perlin noise class
		void Seed(uint32 seed);

		// Set the number of octaves to sum. Has no effect if parameter 'o' is less than 1.
		void SetOctaves(int o);
		// Sets the persistence of each octave. Negative values or values greater than 0.5 (especially greater than 1.0) may produce bizarre results.
		void SetPersistence(double p);
		// Sets the lacunarity of each octave. Values less than 2.0 may produce odd/undesirable results.
		void SetLacunarity(double l);
		// Sets the scale by which the noise will be executed
		void SetScale(double s);

		void SetBaseFrequency(double f);
		void SetBaseAmplitude(double f);

	private:
		PerlinNoise m_pPerlin;

		int m_nOctaves; // Number of octaves to sum together. Default is 10.
		double m_dPersistence; // Amplitude multiplier for each subsequent octave. Default is 0.5.
		double m_dLacunarity; // Frequency multiplier for each subsequent octave. Default is 2.0.
		double m_dBaseFrequency; // Initial starting frequency. Default is 1.0.
		double m_dBaseAmplitude; // Initial starting amplitude. Default is 1.0.
		double m_dScale; //Initial starting scale. Default is 1.0
	};
}