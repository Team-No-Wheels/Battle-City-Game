#pragma once

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

			std::string ConvertToRPN(const std::string& infixExpression);

		private:
			void HandleToken(const std::string& token, TokenType tokenType);

			Vector<std::string> mStack;
			static Vector<std::string> TokenTypes;
			static Vector<std::string> TokenExpressions;
			static HashMap<std::string, OperatorInfo> OperatorInfoMap;
		};
	}
}
