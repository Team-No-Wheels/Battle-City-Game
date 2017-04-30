#pragma once

namespace AnonymousEngine
{
	/** A singleton used to generate random numbers.
	*/
	class RandomNumbersGenerator
	{
		static std::unique_ptr<RandomNumbersGenerator> sInstance;
		RandomNumbersGenerator() = default;

		static std::random_device sRandomDevice;

	public:

		/** Returns the singleton instance.
		* @return Instance of the random number generator.
		*/
		static RandomNumbersGenerator& GetInstance();

		/** Returns a random float between a min and a max.
		* @param min: minimum of the random float.
		* @param max: maximum of the random float.
		* @return Random float.
		*/
		float GetRangedRandom(const float max, const float min = 0);

		/** Returns a random int between a min and a max.
		* @param min: minimum of the random int.
		* @param max: maximum of the random int.
		* @return Random float.
		*/
		int32_t GetRangedRandom(const int32_t max, const int32_t min = 0);

	};
}
