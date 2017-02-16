#pragma once

#include "CppUnitTest.h"
#include <cstdint>
#include <random>
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "Foo.h"

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

		std::uint32_t GetRandomUInt32() const;
		std::int32_t GetRandomInt32() const;
		float GetRandomFloat() const;
		std::string GetRandomString() const;
		glm::vec4 GetRandomVec4() const;
		glm::mat4 GetRandomMat4() const;
		Foo GetRandomFoo() const;
	protected:
		_CrtMemState mStartMemState;
		std::default_random_engine* mGenerator;
		std::uniform_int_distribution<std::uint32_t>* mDistribution;
	};
}
