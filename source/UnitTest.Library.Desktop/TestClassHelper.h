#pragma once

#include "CppUnitTest.h"
#include <cstdint>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	class TestClassHelper
	{
	public:
		TestClassHelper();
		TestClassHelper(const TestClassHelper&) = delete;
		TestClassHelper& operator=(const TestClassHelper&) = delete;

		void BeginClass();
		void EndClass();

		void Setup();
		void Teardown();

		std::uint32_t getRandomUInt32() const;
	protected:
		_CrtMemState mStartMemState;
		std::default_random_engine* mGenerator;
		std::uniform_int_distribution<std::uint32_t>* mDistribution;
	};
}
