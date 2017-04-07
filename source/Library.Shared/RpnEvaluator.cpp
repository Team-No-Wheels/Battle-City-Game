#include "RpnEvaluator.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		HashMap<std::string, RpnEvaluator::OperatorSignature> RpnEvaluator::Signatures = {
			{"()",{OperatorType::Multi,{}}},
			{"[]",{OperatorType::Binary,{{RpnToken::Variable, RpnToken::Variable, RpnToken::Integer}}}},
			{".",{OperatorType::Binary,{{RpnToken::Variable, RpnToken::Variable, RpnToken::Variable}}}},
			{"!",{OperatorType::Unary,{{RpnToken::Integer, RpnToken::Integer}}}},
			{"*",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Float, RpnToken::Integer, RpnToken::Float},{RpnToken::Float, RpnToken::Float, RpnToken::Integer}}}},
			{"/",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Float, RpnToken::Integer, RpnToken::Float},{RpnToken::Float, RpnToken::Float, RpnToken::Integer}}}},
			{"%",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer}}}},
			{"-",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Float, RpnToken::Integer, RpnToken::Float},{RpnToken::Float, RpnToken::Float, RpnToken::Integer}}}},
			{"+",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Float, RpnToken::Integer, RpnToken::Float},{RpnToken::Float, RpnToken::Float, RpnToken::Integer},{RpnToken::String, RpnToken::String, RpnToken::String}}}},
			{"<<",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer}}}},
			{">>",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer}}}},
			{"<",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Integer, RpnToken::Integer, RpnToken::Float},{RpnToken::Integer, RpnToken::Float, RpnToken::Integer},{RpnToken::Integer, RpnToken::String, RpnToken::String}}}},
			{">",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Integer, RpnToken::Integer, RpnToken::Float},{RpnToken::Integer, RpnToken::Float, RpnToken::Integer},{RpnToken::Integer, RpnToken::String, RpnToken::String}}}},
			{"<=",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Integer, RpnToken::Integer, RpnToken::Float},{RpnToken::Integer, RpnToken::Float, RpnToken::Integer},{RpnToken::Integer, RpnToken::String, RpnToken::String}}}},
			{">=",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Integer, RpnToken::Integer, RpnToken::Float},{RpnToken::Integer, RpnToken::Float, RpnToken::Integer},{RpnToken::Integer, RpnToken::String, RpnToken::String}}}},
			{"==",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Integer, RpnToken::Integer, RpnToken::Float},{RpnToken::Integer, RpnToken::Float, RpnToken::Integer},{RpnToken::Integer, RpnToken::String, RpnToken::String}}}},
			{"!=",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Integer, RpnToken::Integer, RpnToken::Float},{RpnToken::Integer, RpnToken::Float, RpnToken::Integer},{RpnToken::Integer, RpnToken::String, RpnToken::String}}}},
			{"&",{OperatorType::Unary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer}}}},
			{"^",{OperatorType::Unary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer}}}},
			{"|",{OperatorType::Unary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer}}}},
			{"&&",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer}}}},
			{"||",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer}}}},
			{"sin",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"cos",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"tan",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"atan",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"exp",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"log",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"log10",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"sqrt",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"isqrt",{OperatorType::Unary,{{RpnToken::Float, RpnToken::Float},{RpnToken::Float, RpnToken::Integer}}}},
			{"pow",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Float, RpnToken::Float, RpnToken::Integer},{RpnToken::Float, RpnToken::Integer, RpnToken::Float}}}},
			{"max",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Float, RpnToken::Integer, RpnToken::Float},{RpnToken::Float, RpnToken::Float, RpnToken::Integer},{RpnToken::Float, RpnToken::Float, RpnToken::Float}}}},
			{"min",{OperatorType::Binary,{{RpnToken::Integer, RpnToken::Integer, RpnToken::Integer},{RpnToken::Float, RpnToken::Integer, RpnToken::Float},{RpnToken::Float, RpnToken::Float, RpnToken::Integer},{RpnToken::Float, RpnToken::Float, RpnToken::Float}}}}
		};

		HashMap<std::string, std::function<void(RpnEvaluator&, Datum&)>> RpnEvaluator::MultiOperatorHandlers = {
			{"()", OperatorFunction}
		};

		HashMap<std::string, std::function<void(RpnEvaluator&, const Datum&, Datum&)>> RpnEvaluator::UnaryOperatorHandlers = {
			{"!", OperatorNot},
			{"&", OperatorBitwiseAnd},
			{"^", OperatorBitwiseXor},
			{"|", OperatorBitwiseOr},
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

		HashMap<std::string, std::function<void(RpnEvaluator&, const Datum&, const Datum&, Datum&)>> RpnEvaluator::BinaryOperatorHandlers = {
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
			{"&&", OperatorLogicalAnd},
			{"||", OperatorLogicalOr},
			{"pow", OperatorPow},
			{"max", OperatorMax},
			{"min", OperatorMin}
		};

		void RpnEvaluator::EvaluateRPN(const std::string&, const Attributed&, Datum&)
		{
			
		}

		void RpnEvaluator::OperatorFunction(RpnEvaluator&, Datum&)
		{
		}

		void RpnEvaluator::OperatorSubscript(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{
		}

		void RpnEvaluator::OperatorDot(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorNot(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorMultiply(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorDivide(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorModulus(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorSubtract(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorAdd(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorLeftShift(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorRightShift(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorLessThan(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorGreaterThan(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorLessThanOrEqual(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorGreaterThanOrEqual(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorEquals(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorNotEquals(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorBitwiseAnd(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorBitwiseXor(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorBitwiseOr(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorLogicalAnd(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorLogicalOr(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorSin(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorCos(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorTan(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorAtan(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorExp(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorLog(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorLog10(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorSqrt(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorIsqrt(RpnEvaluator&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorPow(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorMax(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}

		void RpnEvaluator::OperatorMin(RpnEvaluator&, const Datum&, const Datum&, Datum&)
		{}
	}
}
