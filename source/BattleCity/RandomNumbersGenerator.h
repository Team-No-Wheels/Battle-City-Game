#pragma once

namespace AnonymousEngine
{
	class RandomNumbersGenerator
	{
		static std::unique_ptr<RandomNumbersGenerator> sInstance;
		RandomNumbersGenerator() = default;

		static std::random_device sRandomDevice;

	public:

		static RandomNumbersGenerator& GetInstance();

		float GetRangedRandom(const float min, const float max);

		int32_t GetRangedRandom(const int32_t min, const int32_t max);

	};
}
