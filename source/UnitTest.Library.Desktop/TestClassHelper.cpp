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
}
