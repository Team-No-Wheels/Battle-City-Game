#pragma once

#include "Vector.h"
#include <regex>
#include "HashMap.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class InfixParser
		{
		public:
			enum class TokenType
			{
				Integer,
				Float,
				String,
				Variable,
				Operator,
				Function,
				LeftParanthesis,
				RightParanthesis
			};

			std::string ConvertToRPN(const std::string& infixExpression);

		private:
			Vector<std::string> mStack;
			static HashMap<TokenType, std::string> TokenExpressions;
		};
	}
}
