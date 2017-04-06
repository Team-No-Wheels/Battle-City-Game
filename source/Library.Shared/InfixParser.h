#pragma once

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
				Float,
				Integer,
				String,
				Variable,
				UnaryOperator,
				BinaryOperator,
				Function,
				Subscript,
				LeftParanthesis,
				RightParanthesis
			};

			enum Associativity
			{
				Left,
				Right
			};

			struct OperatorInfo
			{
				std::uint32_t mPrecedence;
				Associativity mAssociativity;
			};

			/** Convert an infix expression to RPN expression
			*  @param infixExpression The expression that should be parsed
			*  @return The RPN expression that is parsed from the input
			*/
			std::string ConvertToRPN(const std::string& infixExpression);

		private:
			// Handle parsed tokens
			void HandleToken(const std::string& token, TokenType tokenType);

			// The stack used for parsing
			Vector<std::string> mStack;
			// The string names of token type enum values
			static Vector<std::string> TokenTypes;
			// List of regular expressions for each token type
			static Vector<std::string> TokenExpressions;
			// Mapping for each supported operator and its Associativity and precedence
			static HashMap<std::string, OperatorInfo> OperatorInfoMap;
		};
	}
}
