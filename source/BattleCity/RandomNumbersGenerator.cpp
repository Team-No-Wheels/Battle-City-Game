#include "Pch.h"
#include "RandomNumbersGenerator.h"

using namespace std;

namespace AnonymousEngine
{
	unique_ptr<RandomNumbersGenerator> RandomNumbersGenerator::sInstance = nullptr;
	random_device RandomNumbersGenerator::sRandomDevice; // only used once to initialise (seed) engine

	/************************************************************************/
	RandomNumbersGenerator& RandomNumbersGenerator::GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance.reset(new RandomNumbersGenerator());
		}

		return *sInstance;
	}

	/************************************************************************/
	float RandomNumbersGenerator::GetRangedRandom(const float min, const float max)
	{
		mt19937 rng(sRandomDevice());    // random-number engine used (Mersenne-Twister in this case)
		uniform_real_distribution<float> uni(min, max); // guaranteed unbiased

		return uni(rng);
	}

	/************************************************************************/
	int32_t RandomNumbersGenerator::GetRangedRandom(const int32_t min, const int32_t max)
	{
		mt19937 rng(sRandomDevice());    // random-number engine used (Mersenne-Twister in this case)
		uniform_int_distribution<int32_t> uni(min, max); // guaranteed unbiased

		return uni(rng);
	}
}
