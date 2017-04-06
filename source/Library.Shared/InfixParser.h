#pragma once

#include <regex>
#include "HashMap.h"
#include <functional>

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
				UnaryOperator,
				BinaryOperator,
				Comma,
				LeftSquareBracket,
				RightSquareBracket,
				LeftParanthesis,
				RightParanthesis,
				Function,
				Variable,
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
			const std::string& ConvertToRPN(const std::string& infixExpression);

		private:
			// Handle parsed tokens
			void HandleToken(const std::string& token, TokenType tokenType);
			// Move stack contents to output string
			void ClearOutStack();

			// Token Handlers
			static void HandleValues(InfixParser& parser, const std::string& token);
			static void HandleOperator(InfixParser& parser, const std::string& token);
			static void HandleFunction(InfixParser& parser, const std::string& token);
			static void HandleComma(InfixParser& parser, const std::string& token);
			static void HandleLeftSquareBracket(InfixParser& parser, const std::string& token);
			static void HandleRightSquareBracket(InfixParser& parser, const std::string& token);
			static void HandleLeftParanthesis(InfixParser& parser, const std::string& token);
			static void HandleRightParanthesis(InfixParser& parser, const std::string& token);

			// The stack used for parsing
			Vector<std::string> mStack;
			// Output postfix expression
			std::string mOutputExpression;

			// The string names of token type enum values
			static Vector<std::string> TokenTypes;
			// List of regular expressions for each token type
			static Vector<std::string> TokenExpressions;
			// Mapping for each supported operator and its Associativity and precedence
			static HashMap<std::string, OperatorInfo> OperatorInfoMap;
			// Map of token handlers
			static HashMap<TokenType, std::function<void(InfixParser&, const std::string&)>> TokenHandlers;
		};
	}
}
