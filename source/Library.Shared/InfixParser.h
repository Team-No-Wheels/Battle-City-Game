#pragma once

#include "Vector.h"
#include <regex>
#include "HashMap.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		/** An infix expression to postfix expression parser
		 */
		class InfixParser
		{
		public:
			/** Type of expression tokens
			 */
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

			/** Convert an infix expression to RPN expression
			 *  @param infixExpression The expression that should be parsed
			 *  @return The RPN expression that is parsed from the input
			 */
			std::string ConvertToRPN(const std::string& infixExpression);

		private:
			// The stack used for parsing
			Vector<std::string> mStack;
			// Mapping of token types vs regular expression
			static HashMap<TokenType, std::string> TokenExpressions;
		};
	}
}
