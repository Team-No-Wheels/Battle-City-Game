#include "InfixParser.h"
#include <regex>
#include "../../../../../../../../../../Program Files (x86)/Microsoft Visual Studio 14.0/VC/UnitTest/include/CppUnitTestLogger.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		Vector<std::string> InfixParser::TokenTypes = {
			"Float",
			"Integer",
			"String",
			"Variable",
			"UnaryOperator",
			"BinaryOperator",
			"Function",
			"Subscript",
			"LeftParanthesis",
			"RightParanthesis"
		};

		Vector<std::string> InfixParser::TokenExpressions = {
			"^[[:digit:]]+\\.[[:digit:]]+",
			"^[[:digit:]]+",
			"^'[^']*'",
			"^[a-zA-Z_]+[a-zA-Z_0-9]*",
			"^!",
			"^(-|\\+|\\*|/|%|&&|\\|\\||==|!=|<|>|>=|<=|&|\\||^|<<|>>|\\.)",
			"^[a-zA-Z_]+[a-zA-Z_0-9]*\\(",
			"^[a-zA-Z_]+[a-zA-Z_0-9]*\\[",
			"^\\(",
			"^\\)"
		};

		HashMap<std::string, InfixParser::OperatorInfo> InfixParser::OperatorInfoMap = {
			{"()", {2, Left}},
			{"[]", {2, Left}},
			{".", {2, Left}},
			{"*", {5, Left}},
			{"/", {5, Left}},
			{"%", {5, Left}},
			{"-", {6, Left}},
			{"+", {6, Left}},
			{"<", {8, Left}},
			{">", {8, Left}},
			{"<=", {8, Left}},
			{">=", {8, Left}},
			{"==", {9, Left}},
			{"!=", {9, Left}},
			{"&&", {13, Left}},
			{"||", {14, Left}},
		};

		std::string InfixParser::ConvertToRPN(const std::string& expression)
		{
			mStack.Clear();
			bool matchFound;
			std::string input = expression;
			for(std::uint32_t index = 0; index < expression.size();)
			{
				matchFound = false;
				std::uint32_t type = 0;
				for (auto& regexString : TokenExpressions)
				{
					std::regex re(regexString);
					std::smatch matches;
					if (std::regex_search(input, matches, re))
					{
						matchFound = true;
						std::string match = matches[0];
						index += static_cast<std::int32_t>(match.length());
						input = expression.substr(index);
						match.append(" : ");
						match.append(TokenTypes[type]);
						Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(match.c_str());
					}
					++type;
				}

				if (!matchFound)
				{
					Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("No more matches found");
					break;
				}
			}
			return "";
		}

		void InfixParser::HandleToken(const std::string&, TokenType)
		{
		}
	}
}
