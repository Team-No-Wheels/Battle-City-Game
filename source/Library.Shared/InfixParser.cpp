#include "InfixParser.h"
#include <regex>

namespace AnonymousEngine
{
	namespace Parsers
	{
		Vector<std::string> InfixParser::TokenTypes = {
			"Float",
			"Integer",
			"String",
			"UnaryOperator",
			"BinaryOperator",
			"Comma",
			"LeftSquareBracket",
			"RightSquareBracket",
			"LeftParanthesis",
			"RightParanthesis",
			"Function",
			"Variable"
		};

		Vector<std::string> InfixParser::TokenExpressions = {
			"^[[:digit:]]+\\.[[:digit:]]+",
			"^[[:digit:]]+",
			"^'[^']*'",
			"^!",
			"^(-|\\+|\\*|/|%|&&|\\|\\||==|!=|<|>|>=|<=|&|\\||\\^|<<|>>|\\.)",
			"^\\,",
			"^\\[",
			"^\\]",
			"^\\(",
			"^\\)",
			"^(sin|cos|tan|atan|exp|log|pow|sqrt|isqrt|min|max)",
			"^[a-zA-Z_]+[a-zA-Z_0-9]*"
		};

		HashMap<std::string, InfixParser::OperatorInfo> InfixParser::OperatorInfoMap = {
			{"()", {15, Left}},
			{"[]", {15, Left}},
			{".", {15, Left}},
			{"!", {14, Right}},
			{"*", {12, Left}},
			{"/", {12, Left}},
			{"%", {12, Left}},
			{"-", {11, Left}},
			{"+", {11, Left}},
			{"<<", {10, Left}},
			{">>", {10, Left}},
			{"<", {9, Left}},
			{">", {9, Left}},
			{"<=", {9, Left}},
			{">=", {9, Left}},
			{"==", {8, Left}},
			{"!=", {8, Left}},
			{"&", {7, Left}},
			{"^", {6, Left}},
			{"|", {5, Left}},
			{"&&", {4, Left}},
			{"||", {3, Left}},
			{"\\,", {1, Left}},
		};

		HashMap<InfixParser::TokenType, std::function<void(InfixParser&, const std::string&)>> InfixParser::TokenHandlers = {
			{TokenType::Float, HandleValues},
			{TokenType::Integer, HandleValues},
			{TokenType::String, HandleValues},
			{TokenType::UnaryOperator, HandleOperator},
			{TokenType::BinaryOperator, HandleOperator},
			{TokenType::Function, HandleFunction},
			{TokenType::Comma, HandleComma},
			{TokenType::Variable, HandleValues},
			{TokenType::LeftSquareBracket, HandleLeftSquareBracket},
			{TokenType::RightSquareBracket, HandleRightSquareBracket},
			{TokenType::RightParanthesis, HandleRightParanthesis},
			{TokenType::LeftParanthesis, HandleLeftParanthesis}
		};

		const std::string& InfixParser::ConvertToRPN(const std::string& expression)
		{
			mStack.Clear();
			bool matchFound;
			std::string trimmedExpression = std::regex_replace(expression, std::regex("\\s+"), "");
			std::string input = trimmedExpression;
			for(std::uint32_t index = 0; index < trimmedExpression.size();)
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
						HandleToken(match, static_cast<TokenType>(type));
						input = trimmedExpression.substr(index);
						break;
					}
					++type;
				}

				if (!matchFound)
				{
					break;
				}
			}
			ClearOutStack();
			return mOutputExpression;
		}

		void InfixParser::HandleToken(const std::string& token, const TokenType tokenType)
		{
			TokenHandlers[tokenType](*this, token);
		}

		void InfixParser::ClearOutStack()
		{
			while (!mStack.IsEmpty())
			{
				if (mStack.Back() == "(" || mStack.Back() == ")")
				{
					throw std::runtime_error("Mismatched paranthesis");
				}
				mOutputExpression.append("`");
				mOutputExpression.append(mStack.Back());
				mStack.PopBack();
			}
		}

		void InfixParser::HandleValues(InfixParser& parser, const std::string& token)
		{
			parser.mOutputExpression.append("`");
			parser.mOutputExpression.append(token);
		}

		void InfixParser::HandleOperator(InfixParser& parser, const std::string& token)
		{
			while (!parser.mStack.IsEmpty() && OperatorInfoMap.ContainsKey(parser.mStack.Back()))
			{
				const OperatorInfo& info = OperatorInfoMap[token];
				if ((info.mAssociativity == Left && info.mPrecedence <= OperatorInfoMap[parser.mStack.Back()].mPrecedence) ||
					(info.mAssociativity == Right && info.mPrecedence < OperatorInfoMap[parser.mStack.Back()].mPrecedence))
				{
					parser.mOutputExpression.append("`");
					parser.mOutputExpression.append(parser.mStack.Back());
					parser.mStack.PopBack();
				}
				else
				{
					break;
				}
			}
			parser.mStack.PushBack(token);
		}

		void InfixParser::HandleFunction(InfixParser& parser, const std::string& token)
		{
			parser.mStack.PushBack(token);
		}

		void InfixParser::HandleComma(InfixParser& parser, const std::string&)
		{
			while (parser.mStack.Back() != "(")
			{
				parser.mOutputExpression.append("`");
				parser.mOutputExpression.append(parser.mStack.Back());
				parser.mStack.PopBack();
			}
		}

		void InfixParser::HandleLeftSquareBracket(InfixParser& parser, const std::string& token)
		{
			parser.mStack.PushBack(token);
		}

		void InfixParser::HandleRightSquareBracket(InfixParser& parser, const std::string&)
		{
			while (parser.mStack.Back() != "[")
			{
				parser.mOutputExpression.append("`");
				parser.mOutputExpression.append(parser.mStack.Back());
				parser.mStack.PopBack();
			}

			parser.mStack.PopBack();
			std::regex re(TokenExpressions[static_cast<std::uint32_t>(TokenType::Function)]);
			std::smatch matches;
			std::string top = parser.mStack.Back();
			if (!parser.mStack.IsEmpty() && std::regex_search(top, matches, re))
			{
				parser.mOutputExpression.append("`");
				parser.mOutputExpression.append(top);
				parser.mStack.PopBack();
			}
		}

		void InfixParser::HandleLeftParanthesis(InfixParser& parser, const std::string& token)
		{
			parser.mStack.PushBack(token);
		}

		void InfixParser::HandleRightParanthesis(InfixParser& parser, const std::string&)
		{
			while (parser.mStack.Back() != "(")
			{
				parser.mOutputExpression.append("`");
				parser.mOutputExpression.append(parser.mStack.Back());
				parser.mStack.PopBack();
			}

			parser.mStack.PopBack();
			std::regex re(TokenExpressions[static_cast<std::uint32_t>(TokenType::Function)]);
			std::smatch matches;
			std::string top = parser.mStack.Back();
			if (!parser.mStack.IsEmpty() && std::regex_search(top, matches, re))
			{
				parser.mOutputExpression.append("`");
				parser.mOutputExpression.append(top);
				parser.mStack.PopBack();
			}
		}
	}
}
