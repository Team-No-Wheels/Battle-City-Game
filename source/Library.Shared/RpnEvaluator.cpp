#include "RpnEvaluator.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iterator>
#include <sstream>

namespace AnonymousEngine
{
	namespace Parsers
	{
		HashMap<std::string, RpnEvaluator::OperatorType> RpnEvaluator::OperatorTypes = {
			{"()", OperatorType::Multi},
			{"[]", OperatorType::Binary},
			{".", OperatorType::Binary},
			{"!", OperatorType::Unary},
			{"*", OperatorType::Binary},
			{"/", OperatorType::Binary},
			{"%", OperatorType::Binary},
			{"-", OperatorType::Binary},
			{"+", OperatorType::Binary},
			{"<<", OperatorType::Binary},
			{">>", OperatorType::Binary},
			{"<", OperatorType::Binary},
			{">", OperatorType::Binary},
			{"<=", OperatorType::Binary},
			{">=", OperatorType::Binary},
			{"==", OperatorType::Binary},
			{"!=", OperatorType::Binary},
			{"&", OperatorType::Binary},
			{"^", OperatorType::Binary},
			{"|", OperatorType::Binary},
			{"&&", OperatorType::Binary},
			{"||", OperatorType::Binary},
			{"sin", OperatorType::Unary},
			{"cos", OperatorType::Unary},
			{"tan", OperatorType::Unary},
			{"atan", OperatorType::Unary},
			{"exp", OperatorType::Unary},
			{"log", OperatorType::Unary},
			{"log10", OperatorType::Unary},
			{"sqrt", OperatorType::Unary},
			{"isqrt", OperatorType::Unary},
			{"pow", OperatorType::Binary},
			{"max", OperatorType::Binary},
			{"min", OperatorType::Binary}
		};

		HashMap<RpnEvaluator::OperatorType, std::function<void(RpnEvaluator&, const std::string& operatorString, const Attributed&, Datum&)>> RpnEvaluator::MasterOperatorHandlers = {
			{OperatorType::Multi, MultiOperatorHandler},
			{OperatorType::Unary, UnaryOperatorHandler},
			{OperatorType::Binary, BinaryOperatorHandler}
		};

		HashMap<std::string, std::function<void(const Datum&, Datum&)>> RpnEvaluator::UnaryOperatorHandlers = {
			{"!", OperatorNot},
			{"sin", OperatorSin},
			{"cos", OperatorCos},
			{"tan", OperatorTan},
			{"atan", OperatorAtan},
			{"exp", OperatorExp},
			{"log", OperatorLog},
			{"log10", OperatorLog10},
			{"sqrt", OperatorSqrt},
			{"isqrt", OperatorIsqrt}
		};

		HashMap<std::string, std::function<void(const Datum&, const Datum&, Datum&)>> RpnEvaluator::BinaryOperatorHandlers = {
			{"[]", OperatorSubscript},
			{".", OperatorDot},
			{"*", OperatorMultiply},
			{"/", OperatorDivide},
			{"%", OperatorModulus},
			{"-", OperatorSubtract},
			{"+", OperatorAdd},
			{"<<", OperatorLeftShift},
			{">>", OperatorRightShift},
			{"<", OperatorLessThan},
			{">", OperatorGreaterThan},
			{"<=", OperatorLessThanOrEqual},
			{">=", OperatorGreaterThanOrEqual},
			{"==", OperatorEquals},
			{"!=", OperatorNotEquals},
			{"&", OperatorBitwiseAnd},
			{"^", OperatorBitwiseXor},
			{"|", OperatorBitwiseOr},
			{"&&", OperatorLogicalAnd},
			{"||", OperatorLogicalOr},
			{"pow", OperatorPow},
			{"max", OperatorMax},
			{"min", OperatorMin}
		};

		HashMap<RpnToken, Datum::DatumType> RpnEvaluator::RpnTokenValueTypesToDatumTypes = {
			{RpnToken::Integer, Datum::DatumType::Integer},
			{RpnToken::Float, Datum::DatumType::Float},
			{RpnToken::String, Datum::DatumType::String}
		};

		const char RpnEvaluator::TokenSeparator = '`';

		void RpnEvaluator::EvaluateRPN(const std::string& rpnExpression, const Attributed& scope, Datum& result)
		{
			mStack.Clear();
			mStack.Reserve((rpnExpression.length() * 2) / 3);

			// Create token vector and reserve memory to hold the max possible amount of tokens from the given expression
			Vector<StackEntry> tokens;
			tokens.Reserve(rpnExpression.length() / 3);

			ExtractTokens(rpnExpression, tokens);
			for (auto& token : tokens)
			{
				if (token.mTokenType != RpnToken::Operator)
				{
					mStack.PushBack(token);
				}
				else
				{
					assert(OperatorTypes.ContainsKey(token.mToken));
					MasterOperatorHandlers[OperatorTypes[token.mToken]](*this, token.mToken, scope, result);
				}
			}
		}

		void RpnEvaluator::ExtractTokens(const std::string& rpnExpression, Vector<StackEntry>& tokens)
		{
			std::stringstream stream;
			stream.str(rpnExpression);
			std::string item;
			StackEntry entry;
			bool isToken = true;
			while (std::getline(stream, item, TokenSeparator))
			{
				if (isToken)
				{
					entry.mToken = item;
				}
				else
				{
					entry.mTokenType = static_cast<RpnToken>(std::stoul(item));
					tokens.PushBack(entry);
				}
				isToken = !isToken;
			}
		}

		const Datum& RpnEvaluator::GetParam(const StackEntry& entry, const Attributed& scope, bool& shouldDelete)
		{
			Datum* param1;
			shouldDelete = true;
			if (entry.mTokenType == RpnToken::Variable)
			{
				param1 = const_cast<Datum*>(scope.Search(entry.mToken));
				shouldDelete = false;
			}
			else
			{
				param1 = new Datum();
				param1->SetType(RpnTokenValueTypesToDatumTypes[entry.mTokenType]);
				param1->Resize(1U);
				param1->SetFromString(entry.mToken);
			}
			return (*param1);
		}

		void RpnEvaluator::MultiOperatorHandler(RpnEvaluator& evaluator, const std::string& operatorString, const Attributed& scope, Datum& result)
		{
			assert(UnaryOperatorHandlers.ContainsKey(operatorString) || BinaryOperatorHandlers.ContainsKey(operatorString));
			if (UnaryOperatorHandlers.ContainsKey(operatorString))
			{
				UnaryOperatorHandler(evaluator, operatorString, scope, result);
			}
			else
			{
				BinaryOperatorHandler(evaluator, operatorString, scope, result);
			}
		}

		void RpnEvaluator::UnaryOperatorHandler(RpnEvaluator& evaluator, const std::string& operatorString, const Attributed& scope, Datum& result)
		{
			const StackEntry& entry = evaluator.mStack.Back();
			bool shouldDelete;
			const Datum& param1 = GetParam(entry, scope, shouldDelete);
			UnaryOperatorHandlers[operatorString](param1, result);
			if (shouldDelete)
			{
				delete &param1;
			}
		}

		void RpnEvaluator::BinaryOperatorHandler(RpnEvaluator& evaluator, const std::string& operatorString, const Attributed& scope, Datum& result)
		{
			const StackEntry& entry1 = evaluator.mStack.Back();
			bool shouldDeleteParam1 = true;
			const Datum& param1 = GetParam(entry1, scope, shouldDeleteParam1);

			const StackEntry& entry2 = evaluator.mStack.Back();
			bool shouldDeleteParam2 = true;
			const Datum& param2 = GetParam(entry2, scope, shouldDeleteParam2);
				
			BinaryOperatorHandlers[operatorString](param1, param2, result);
			if (shouldDeleteParam1)
			{
				delete &param1;
			}
			if (shouldDeleteParam2)
			{
				delete &param2;
			}
		}

		void RpnEvaluator::OperatorSubscript(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param2.Type() == Datum::DatumType::Integer);
			std::int32_t index = param2.Get<std::int32_t>();
			switch (param1.Type())
			{
			case Datum::DatumType::Integer:
				result = param1.Get<std::int32_t>(index);
				break;
			case Datum::DatumType::Float:
				result = param1.Get<float>(index);
				break;
			case Datum::DatumType::String:
				result = param1.Get<std::string>(index);
				break;
			case Datum::DatumType::Vector:
				result = param1.Get<glm::vec4>(index);
				break;
			case Datum::DatumType::Matrix:
				result = param1.Get<glm::mat4>(index);
				break;
			case Datum::DatumType::Scope:
				result = const_cast<Scope&>(param1.Get<Scope>(index));
				break;
			case Datum::DatumType::RTTI:
				result = param1.Get<RTTI*>(index);
				break;
			default:
				break;
			}
		}

		void RpnEvaluator::OperatorDot(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Scope);
			assert(param2.Type() == Datum::DatumType::String);
			result = param1.Get<Scope>()[param2.Get<std::string>()];
		}

		void RpnEvaluator::OperatorNot(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			result.SetType(param1.Type());
			result.Resize(1U);
			result.Set(!param1.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorMultiply(const Datum& param1, const Datum& param2, Datum& result)
		{
			if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Integer)
			{
				result = (param1.Get<std::int32_t>() * param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<std::int32_t>() * param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Integer)
			{
				result = (param1.Get<float>() * param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<float>() * param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Vector || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<glm::vec4>() * param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Vector)
			{
				result = (param1.Get<float>() * param2.Get<glm::vec4>());
			}
			else if (param1.Type() == Datum::DatumType::Vector || param2.Type() == Datum::DatumType::Vector)
			{
				result = (param1.Get<glm::vec4>() * param2.Get<glm::vec4>());
			}
			else if (param1.Type() == Datum::DatumType::Matrix || param2.Type() == Datum::DatumType::Vector)
			{
				result = (param1.Get<glm::mat4>() * param2.Get<glm::vec4>());
			}
			else if (param1.Type() == Datum::DatumType::Vector || param2.Type() == Datum::DatumType::Matrix)
			{
				result = (param1.Get<glm::vec4>() * param2.Get<glm::mat4>());
			}
			else if (param1.Type() == Datum::DatumType::Matrix || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<glm::mat4>() * param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Matrix)
			{
				result = (param1.Get<float>() * param2.Get<glm::mat4>());
			}
			else
			{
				assert(false);
			}
		}

		void RpnEvaluator::OperatorDivide(const Datum& param1, const Datum& param2, Datum& result)
		{
			if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Integer)
			{
				result = (param1.Get<std::int32_t>() / param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<std::int32_t>() / param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Integer)
			{
				result = (param1.Get<float>() / param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<float>() / param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Vector || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<glm::vec4>() / param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Vector)
			{
				result = (param1.Get<float>() / param2.Get<glm::vec4>());
			}
			else if (param1.Type() == Datum::DatumType::Vector || param2.Type() == Datum::DatumType::Vector)
			{
				result = (param1.Get<glm::vec4>() / param2.Get<glm::vec4>());
			}
			else if (param1.Type() == Datum::DatumType::Matrix || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<glm::mat4>() / param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Matrix)
			{
				result = (param1.Get<float>() / param2.Get<glm::mat4>());
			}
			else
			{
				assert(false);
			}
		}

		void RpnEvaluator::OperatorModulus(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			assert(param2.Type() == Datum::DatumType::Integer);
			result = (param1.Get<std::int32_t>() % param2.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorSubtract(const Datum& param1, const Datum& param2, Datum& result)
		{
			if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Integer)
			{
				result = (param1.Get<std::int32_t>() - param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<std::int32_t>() - param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Integer)
			{
				result = (param1.Get<float>() - param2.Get<std::int32_t>());
			}
			else if(param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<float>() - param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Vector)
			{
				result = (param1.Get<float>() - param2.Get<glm::vec4>());
			}
			else if (param1.Type() == Datum::DatumType::Vector || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<glm::vec4>() - param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Matrix || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<glm::mat4>() - param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Matrix)
			{
				result = (param1.Get<float>() - param2.Get<glm::mat4>());
			}
			else
			{
				assert(false);
			}
		}

		void RpnEvaluator::OperatorAdd(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float ||
				(param1.Type() == param2.Type() && param1.Type() == Datum::DatumType::String));
			assert(param2.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float ||
				param2.Type() == Datum::DatumType::String);

			if (param1.Type() == param2.Type() && param1.Type() == Datum::DatumType::String)
			{
				result = (param1.Get<std::string>() + param2.Get<std::string>());
			}
			else if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Integer)
			{
				result = (param1.Get<std::int32_t>() + param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<std::int32_t>() + param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Integer)
			{
				result = (param1.Get<float>() + param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<float>() + param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Vector)
			{
				result = (param1.Get<float>() + param2.Get<glm::vec4>());
			}
			else if (param1.Type() == Datum::DatumType::Vector || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<glm::vec4>() + param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Matrix || param2.Type() == Datum::DatumType::Float)
			{
				result = (param1.Get<glm::mat4>() + param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Matrix)
			{
				result = (param1.Get<float>() + param2.Get<glm::mat4>());
			}
			else
			{
				assert(false);
			}
		}

		void RpnEvaluator::OperatorLeftShift(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			assert(param2.Type() == Datum::DatumType::Integer);
			result = (param1.Get<std::int32_t>() << param2.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorRightShift(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			assert(param2.Type() == Datum::DatumType::Integer);
			result = (param1.Get<std::int32_t>() >> param2.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorLessThan(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			assert(param2.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(param1.Get<std::int32_t>() < param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float)
			{
				result = static_cast<std::int32_t>(param1.Get<std::int32_t>() < param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(param1.Get<float>() < param2.Get<std::int32_t>());
			}
			else
			{
				result = static_cast<std::int32_t>(param1.Get<float>() < param2.Get<float>());
			}
		}

		void RpnEvaluator::OperatorGreaterThan(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			assert(param2.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(param1.Get<std::int32_t>() > param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float)
			{
				result = static_cast<std::int32_t>(param1.Get<std::int32_t>() > param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(param1.Get<float>() > param2.Get<std::int32_t>());
			}
			else
			{
				result = static_cast<std::int32_t>(param1.Get<float>() > param2.Get<float>());
			}
		}

		void RpnEvaluator::OperatorLessThanOrEqual(const Datum& param1, const Datum& param2, Datum& result)
		{
			OperatorGreaterThan(param1, param2, result);
			result.Set(!result.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorGreaterThanOrEqual(const Datum& param1, const Datum& param2, Datum& result)
		{
			OperatorLessThan(param1, param2, result);
			result.Set(!result.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorEquals(const Datum& param1, const Datum& param2, Datum& result)
		{
			if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(param1.Get<std::int32_t>() == param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float)
			{
				result = static_cast<std::int32_t>(param1.Get<std::int32_t>() == param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(param1.Get<float>() == param2.Get<std::int32_t>());
			}
			else if (param1.Type() == Datum::DatumType::Float || param2.Type() == Datum::DatumType::Float)
			{
				result = static_cast<std::int32_t>(param1.Get<float>() == param2.Get<float>());
			}
			else if (param1.Type() == Datum::DatumType::Vector || param2.Type() == Datum::DatumType::Vector)
			{
				result = static_cast<std::int32_t>(param1.Get<glm::vec4>() == param2.Get<glm::vec4>());
			}
			else if (param1.Type() == Datum::DatumType::Matrix || param2.Type() == Datum::DatumType::Matrix)
			{
				result = static_cast<std::int32_t>(param1.Get<glm::mat4>() == param2.Get<glm::mat4>());
			}
			else
			{
				assert(false);
			}
		}

		void RpnEvaluator::OperatorNotEquals(const Datum& param1, const Datum& param2, Datum& result)
		{
			OperatorEquals(param1, param2, result);
			result.Set(!result.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorBitwiseAnd(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			assert(param2.Type() == Datum::DatumType::Integer);
			result = (param1.Get<std::int32_t>() & param2.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorBitwiseXor(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			assert(param2.Type() == Datum::DatumType::Integer);
			result = (param1.Get<std::int32_t>() ^ param2.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorBitwiseOr(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			assert(param2.Type() == Datum::DatumType::Integer);
			result = (param1.Get<std::int32_t>() | param2.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorLogicalAnd(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			assert(param2.Type() == Datum::DatumType::Integer);
			result = (param1.Get<std::int32_t>() && param2.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorLogicalOr(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer);
			assert(param2.Type() == Datum::DatumType::Integer);
			result = (param1.Get<std::int32_t>() || param2.Get<std::int32_t>());
		}

		void RpnEvaluator::OperatorSin(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(sin(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(sin(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorCos(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(cos(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(cos(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorTan(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(tan(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(tan(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorAtan(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(atan(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(atan(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorExp(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(exp(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(exp(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorLog(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(log(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(log(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorLog10(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(log10(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(log10(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorSqrt(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(sqrt(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(sqrt(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorIsqrt(const Datum& param1, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<float>(1/sqrt(param1.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(1/sqrt(param1.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorPow(const Datum& param1, const Datum& param2, Datum& result)
		{
			assert(param1.Type() == Datum::DatumType::Integer || param1.Type() == Datum::DatumType::Float);
			assert(param2.Type() == Datum::DatumType::Integer || param2.Type() == Datum::DatumType::Float);
			if (param1.Type() == Datum::DatumType::Integer && param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(pow(param1.Get<std::int32_t>(), param2.Get<std::int32_t>()));
			}
			else if(param1.Type() == Datum::DatumType::Integer && param1.Type() == Datum::DatumType::Float)
			{
				result = static_cast<float>(pow(param1.Get<std::int32_t>(), param2.Get<float>()));
			}
			else if (param1.Type() == Datum::DatumType::Integer && param1.Type() == Datum::DatumType::Float)
			{
				result = static_cast<float>(pow(param1.Get<float>(), param2.Get<std::int32_t>()));
			}
			else
			{
				result = static_cast<float>(pow(param1.Get<float>(), param2.Get<float>()));
			}
		}

		void RpnEvaluator::OperatorMax(const Datum& param1, const Datum& param2, Datum& result)
		{
			if (param1.Type() == Datum::DatumType::Integer && param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(std::max(param1.Get<std::int32_t>(), param2.Get<std::int32_t>()));
			}
			else if (param1.Type() == Datum::DatumType::Float && param1.Type() == Datum::DatumType::Float)
			{
				result = static_cast<float>(std::max(param1.Get<float>(), param2.Get<float>()));
			}
			else
			{
				assert(false);
			}
		}

		void RpnEvaluator::OperatorMin(const Datum& param1, const Datum& param2, Datum& result)
		{
			if (param1.Type() == Datum::DatumType::Integer && param1.Type() == Datum::DatumType::Integer)
			{
				result = static_cast<std::int32_t>(std::min(param1.Get<std::int32_t>(), param2.Get<std::int32_t>()));
			}
			else if (param1.Type() == Datum::DatumType::Float && param1.Type() == Datum::DatumType::Float)
			{
				result = static_cast<float>(std::min(param1.Get<float>(), param2.Get<float>()));
			}
			else
			{
				assert(false);
			}
		}
	}
}
