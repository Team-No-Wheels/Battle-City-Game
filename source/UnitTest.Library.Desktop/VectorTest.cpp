#include "Pch.h"
#include "Vector.h"
#include "Foo.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorTest)
	{
	public:
		TEST_CLASS_INITIALIZE(BeginClass)
		{
			srand(static_cast<unsigned int>(time(nullptr)));
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&mStartMemState);
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			if (DidMemoryStateChange(mStartMemState))
			{
				Assert::Fail(L"Memory leak...");
			}
		}

	private:
		_CrtMemState mStartMemState;

		static bool DidMemoryStateChange(_CrtMemState startState)
		{
			_CrtMemState endMemState;
			_CrtMemState diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &startState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				return true;
			}
			return false;
		}
	};
}

