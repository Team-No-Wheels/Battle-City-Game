#include "InfixParser.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		HashMap<InfixParser::TokenType, std::string> InfixParser::TokenExpressions = {
			{ TokenType::Integer, "[0-9]+" },
			{ TokenType::Float, "[0-9]+" },
			{ TokenType::String, "'[^']*'" },
			{ TokenType::Variable, "[a-zA-Z]+[a-zA-Z0-9]*" },
			{ TokenType::Operator, "" },
			{ TokenType::Function, "" },
			{ TokenType::LeftParanthesis, "" },
			{ TokenType::RightParanthesis, "" }
		};

		std::string InfixParser::ConvertToRPN(const std::string&)
		{
			mStack.Clear();
			return "";
		}
	}
}
