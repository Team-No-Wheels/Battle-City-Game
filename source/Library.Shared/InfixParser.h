#pragma once

#include <functional>
#include "HashMap.h"
#include "RpnTypes.h"

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

			/** Associativity of operators
			 */
			enum Associativity
			{
				Left,
				Right
			};

			/** Struct to hold precedence and associativity of an operator
			 */
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
			// Add to output queue with token type and separator
			void OutputToQueue(const StackEntry& stackEntry);

			// Token Handlers
			static void HandleValues(InfixParser& parser, const std::string& token, const RpnToken tokenType);
			static void HandleOperator(InfixParser& parser, const std::string& token, const RpnToken tokenType);
			static void HandleFunction(InfixParser& parser, const std::string& token, const RpnToken tokenType);
			static void HandleComma(InfixParser& parser, const std::string& token, const RpnToken tokenType);
			static void HandleLeftSquareBracket(InfixParser& parser, const std::string& token, const RpnToken tokenType);
			static void HandleRightSquareBracket(InfixParser& parser, const std::string& token, const RpnToken tokenType);
			static void HandleLeftParanthesis(InfixParser& parser, const std::string& token, const RpnToken tokenType);
			static void HandleRightParanthesis(InfixParser& parser, const std::string& token, const RpnToken tokenType);

			// The stack used for parsing
			Vector<StackEntry> mStack;
			// Output postfix expression
			std::string mOutputExpression;

			// The string names of token type enum values
			static Vector<std::string> TokenTypes;
			// List of regular expressions for each token type
			static Vector<std::string> TokenExpressions;
			// Mapping for each supported operator and its Associativity and precedence
			static HashMap<std::string, OperatorInfo> OperatorInfoMap;
			// Map of token handlers
			static HashMap<TokenType, std::function<void(InfixParser&, const std::string&, const RpnToken)>> TokenHandlers;
			// Parsing types to RPN token types mapping
			static HashMap<TokenType, RpnToken> InfixTokensToRpnTokens;

			// Stack token literals
			static const std::string LeftParanthesis;
			static const std::string RightParanthesis;
			static const std::string LeftSquareBracket;
			static const std::string RightSquareBracket;
			static const std::string FunctionOperator;
			static const std::string SubscriptOperator;
			static const std::string TokenSeparator;
		};
	}
}
