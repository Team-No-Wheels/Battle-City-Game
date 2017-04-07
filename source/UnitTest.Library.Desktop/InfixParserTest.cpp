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
		TEST_METHOD(TestParse)
		{
			Parsers::InfixParser parser;
			for(std::uint32_t index = 0; index < InfixExpressions.Size(); ++index)
			{
				std::string rpnExpression = parser.ConvertToRPN(InfixExpressions[index]);
				Assert::AreEqual(RPNExpressions[index], rpnExpression);
			}
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

		static const Vector<std::string> InfixExpressions;
		static const Vector<std::string> RPNExpressions;
	};

	TestClassHelper InfixParserTest::mHelper;

	const Vector<std::string> InfixParserTest::InfixExpressions = {
		" 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3",
		"sin(max(2, 3) / 3 * 3.1415)",
		"sin ( max ( units[0].health, attacker[1+2].damage ) / 3 * 3.1415 )"
	};

	const Vector<std::string> InfixParserTest::RPNExpressions = {
		"3`1`4`1`2`1`*`5`1`1`5`1`-`5`/`5`+`5`2`1`^`5`3`1`^`5",
		"2`1`3`1`()`6`max`6`3`1`/`5`3.1415`2`*`5`()`6`sin`6",
		"units`4`0`1`[]`7`health`4`.`5`attacker`4`1`1`2`1`+`5`[]`7`damage`4`.`5`()`6`max`6`3`1`/`5`3.1415`2`*`5`()`6`sin`6"
	};
}
