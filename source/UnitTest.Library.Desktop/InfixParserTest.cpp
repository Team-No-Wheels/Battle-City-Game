#include "Pch.h"
#include "InfixParser.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine;

	TEST_CLASS(InfixParserTest)
	{
	public:
		TEST_METHOD(TestAddAndRemove)
		{
			Parsers::InfixParser parser;
			parser.ConvertToRPN("0.1+123-0.79'asdf'-asdf+cos(10)");
		}

		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			mHelper.BeginClass();
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			mHelper.Setup();
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			mHelper.Teardown();
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			mHelper.EndClass();
		}

		static TestClassHelper mHelper;
	};

	TestClassHelper InfixParserTest::mHelper;
}
