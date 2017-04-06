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
			//Logger::WriteMessage(parser.ConvertToRPN("0.1+123-0.79+'asdf'*123+('test'+'def')+!cos(10)/(life[10]-damage)+attack[0]").c_str());
			Logger::WriteMessage(parser.ConvertToRPN("sin ( max ( units[0].health, attacker[1].damage ) / 3 * 3.1415 )").c_str());
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
