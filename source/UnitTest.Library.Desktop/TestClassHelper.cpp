#include "Pch.h"
#include "TestClassHelper.h"

namespace UnitTestLibraryDesktop
{
	TestClassHelper::TestClassHelper() :
		mGenerator(nullptr), mDistribution(nullptr)
	{
	}

	void TestClassHelper::BeginClass()
	{
		std::random_device mDevice;
		mGenerator = new std::default_random_engine(mDevice());
		mDistribution = new std::uniform_int_distribution<std::uint32_t>(0, UINT32_MAX);
	}

	void TestClassHelper::EndClass()
	{
		delete mGenerator;
		delete mDistribution;
	}

	void TestClassHelper::Setup()
	{
#if _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
		_CrtMemCheckpoint(&mStartMemState);
#endif
	}

	void TestClassHelper::Teardown()
	{
#if _DEBUG
		_CrtMemState endMemState;
		_CrtMemState diffMemState;
		_CrtMemCheckpoint(&endMemState);
		if (_CrtMemDifference(&diffMemState, &mStartMemState, &endMemState))
		{
			_CrtMemDumpStatistics(&diffMemState);
			Assert::Fail(L"Memory leak...");
		}
#endif
	}

	std::uint32_t TestClassHelper::GetRandomUInt32() const
	{
		return (*mDistribution)(*mGenerator);
	}

	std::int32_t TestClassHelper::GetRandomInt32() const
	{
		return static_cast<std::int32_t>(GetRandomUInt32());
	}

	float TestClassHelper::GetRandomFloat() const
	{
		return static_cast<float>(GetRandomUInt32()) / GetRandomUInt32();
	}

	std::string TestClassHelper::GetRandomString() const
	{
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		
		char temp[33];
		std::uint32_t length = (GetRandomUInt32() % 32) + 1;

		for (std::uint32_t i = 0; i < length; ++i)
		{
			temp[i] = alphanum[GetRandomUInt32() % (sizeof(alphanum) - 1)];
		}
		temp[length] = '\0';
		return std::string(temp);
	}

	glm::vec4 TestClassHelper::GetRandomVec4() const
	{
		return glm::vec4(GetRandomFloat(), GetRandomFloat(), GetRandomFloat(), GetRandomFloat());
	}

	glm::mat4 TestClassHelper::GetRandomMat4() const
	{
		return glm::mat4(GetRandomVec4(), GetRandomVec4(), GetRandomVec4(), GetRandomVec4());
	}

	Foo TestClassHelper::GetRandomFoo() const
	{
		return Foo(GetRandomUInt32());
	}
}
