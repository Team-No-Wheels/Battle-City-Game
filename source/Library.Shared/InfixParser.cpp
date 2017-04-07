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
			"^[a-zA-Z_]+[a-zA-Z_0-9]\\(",
			"^[a-zA-Z_]+[a-zA-Z_0-9]*"
		};

		HashMap<std::string, InfixParser::OperatorInfo> InfixParser::OperatorInfoMap = {
			{"()",{15, Left}},
			{"[]",{15, Left}},
			{".",{15, Left}},
			{"!",{14, Right}},
			{"*",{12, Left}},
			{"/",{12, Left}},
			{"%",{12, Left}},
			{"-",{11, Left}},
			{"+",{11, Left}},
			{"<<",{10, Left}},
			{">>",{10, Left}},
			{"<",{9, Left}},
			{">",{9, Left}},
			{"<=",{9, Left}},
			{">=",{9, Left}},
			{"==",{8, Left}},
			{"!=",{8, Left}},
			{"&",{7, Left}},
			{"^",{6, Left}},
			{"|",{5, Left}},
			{"&&",{4, Left}},
			{"||",{3, Left}},
			{"\\,",{1, Left}},
		};

		HashMap<InfixParser::TokenType, std::function<void(InfixParser&, const std::string&, const RpnToken)>> InfixParser::TokenHandlers = {
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

		HashMap<InfixParser::TokenType, RpnToken> InfixParser::InfixTokensToRpnTokens = {
			{TokenType::Float, RpnToken::Float},
			{TokenType::Integer, RpnToken::Integer},
			{TokenType::String, RpnToken::String},
			{TokenType::UnaryOperator, RpnToken::Operator},
			{TokenType::BinaryOperator, RpnToken::Operator},
			{TokenType::Comma, RpnToken::Invalid},
			{TokenType::Function, RpnToken::Operator},
			{TokenType::Variable, RpnToken::Variable},
			{TokenType::LeftSquareBracket, RpnToken::Operator},
			{TokenType::RightSquareBracket, RpnToken::Operator},
			{TokenType::RightParanthesis, RpnToken::Operator},
			{TokenType::LeftParanthesis, RpnToken::Operator}
		};

		const std::string InfixParser::LeftParanthesis = "(";
		const std::string InfixParser::RightParanthesis = ")";
		const std::string InfixParser::LeftSquareBracket = "[";
		const std::string InfixParser::RightSquareBracket = "]";
		const std::string InfixParser::FunctionOperator = "()";
		const std::string InfixParser::SubscriptOperator = "[]";
		const std::string InfixParser::TokenSeparator = "`";

		const std::string& InfixParser::ConvertToRPN(const std::string& expression)
		{
			// remove white spaces from the input expression. This doesn't support spaces within strings
			std::string trimmedExpression = std::regex_replace(expression, std::regex("\\s+"), "");
			std::string input = trimmedExpression;

			mStack.Clear();
			mOutputExpression.clear();
			bool matchFound;
			for (std::uint32_t index = 0; index < trimmedExpression.size();)
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
			TokenHandlers[tokenType](*this, token, InfixTokensToRpnTokens[tokenType]);
		}

		void InfixParser::ClearOutStack()
		{
			while (!mStack.IsEmpty())
			{
				const StackEntry& stackEntry = mStack.Back();
				if (stackEntry.mToken == LeftParanthesis || stackEntry.mToken == RightParanthesis)
				{
					throw std::runtime_error("Mismatched paranthesis");
				}
				OutputToQueue(mStack.Back());
				mStack.PopBack();
			}
		}

		void InfixParser::OutputToQueue(const StackEntry& stackEntry)
		{
			if (mOutputExpression.size() > 0)
			{
				mOutputExpression.append(TokenSeparator);
			}
			mOutputExpression.append(stackEntry.mToken);
			mOutputExpression.append(TokenSeparator);
			mOutputExpression.append(std::to_string(static_cast<std::uint32_t>(stackEntry.mTokenType)));
		}

		void InfixParser::HandleValues(InfixParser& parser, const std::string& token, const RpnToken tokenType)
		{
			parser.OutputToQueue({token, tokenType});
		}

		void InfixParser::HandleOperator(InfixParser& parser, const std::string& token, const RpnToken tokenType)
		{
			while (!parser.mStack.IsEmpty() && OperatorInfoMap.ContainsKey(parser.mStack.Back().mToken))
			{
				const OperatorInfo& info = OperatorInfoMap[token];
				if ((info.mAssociativity == Left && info.mPrecedence <= OperatorInfoMap[parser.mStack.Back().mToken].mPrecedence) ||
					(info.mAssociativity == Right && info.mPrecedence < OperatorInfoMap[parser.mStack.Back().mToken].mPrecedence))
				{
					parser.OutputToQueue(parser.mStack.Back());
					parser.mStack.PopBack();
				}
				else
				{
					break;
				}
			}
			parser.mStack.PushBack({token, tokenType});
		}

		void InfixParser::HandleFunction(InfixParser& parser, const std::string& token, const RpnToken tokenType)
		{
			parser.mStack.PushBack({token.substr(0, token.size() - 1), tokenType});
			parser.mStack.PushBack({LeftParanthesis, tokenType});
		}

		void InfixParser::HandleComma(InfixParser& parser, const std::string&, const RpnToken)
		{
			while (parser.mStack.Back().mToken != LeftParanthesis)
			{
				parser.OutputToQueue(parser.mStack.Back());
				parser.mStack.PopBack();
			}
		}

		void InfixParser::HandleLeftSquareBracket(InfixParser& parser, const std::string& token, const RpnToken tokenType)
		{
			parser.mStack.PushBack({token, tokenType});
		}

		void InfixParser::HandleRightSquareBracket(InfixParser& parser, const std::string&, const RpnToken)
		{
			while (parser.mStack.Back().mToken != LeftSquareBracket)
			{
				parser.OutputToQueue(parser.mStack.Back());
				parser.mStack.PopBack();
			}

			parser.mStack.PopBack();
			parser.OutputToQueue({SubscriptOperator, RpnToken::Operator});
		}

		void InfixParser::HandleLeftParanthesis(InfixParser& parser, const std::string& token, const RpnToken tokenType)
		{
			parser.mStack.PushBack({token, tokenType});
		}

		void InfixParser::HandleRightParanthesis(InfixParser& parser, const std::string&, const RpnToken)
		{
			while (parser.mStack.Back().mToken != LeftParanthesis)
			{
				parser.OutputToQueue(parser.mStack.Back());
				parser.mStack.PopBack();
			}

			parser.mStack.PopBack();
			std::regex re(TokenExpressions[static_cast<std::uint32_t>(TokenType::Variable)]);
			std::smatch matches;
			StackEntry top = parser.mStack.Back();
			if (!parser.mStack.IsEmpty() && std::regex_search(top.mToken, matches, re))
			{
				parser.OutputToQueue({FunctionOperator, RpnToken::Operator});
				parser.OutputToQueue(top);
				parser.mStack.PopBack();
			}
		}
	}
}
