#pragma once

#include <functional>
#include "Attributed.h"
#include "HashMap.h"
#include "RpnTypes.h"
#include "Vector.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		/** An RPN encoded expression evaluater
		 */
		class RpnEvaluator
		{
		public:
			enum class OperatorType
			{
				Multi,
				Unary,
				Binary
			};

			/** Evaluate an RPN expression from the given scope and store the result in the given datum
			 *  @param rpnExpression The expression to evaluate
			 *  @param context The scope context in which the values are to be evaluated in
			 *  @param shouldDelete An output parameter to store the result
			 */
			void EvaluateRPN(const std::string& rpnExpression, const Attributed& context, Datum& result);
		private:
			struct StackEntryWithDatum
			{
				StackEntry mEntry;
				Datum* mDatum;
			};

			// The stack used for evaluation
			Vector<StackEntryWithDatum> mStack;

			// Extract tokens with type from the expression
			static void ExtractTokens(const std::string& rpnExpression, Vector<StackEntry>& tokens);
			// Create / get a parameter datum from a stack entry
			static const Datum& GetParam(const StackEntryWithDatum& entryWithDatum, const Attributed& scope, bool& shouldDelete);

			// Main handlers for operator types
			static void MultiOperatorHandler(RpnEvaluator& evaluator, const std::string&, const Attributed&, Datum& result);
			static void UnaryOperatorHandler(RpnEvaluator& evaluator, const std::string&, const Attributed&, Datum& result);
			static void BinaryOperatorHandler(RpnEvaluator& evaluator, const std::string&, const Attributed&, Datum& result);

			// Handle supported operators
			static void OperatorSubscript(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorDot(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorNot(const Datum& param1, Datum& result);
			static void OperatorMultiply(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorDivide(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorModulus(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorSubtract(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorAdd(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLeftShift(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorRightShift(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLessThan(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorGreaterThan(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLessThanOrEqual(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorGreaterThanOrEqual(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorEquals(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorNotEquals(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorBitwiseAnd(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorBitwiseXor(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorBitwiseOr(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLogicalAnd(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLogicalOr(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorSin(const Datum& param1, Datum& result);
			static void OperatorCos(const Datum& param1, Datum& result);
			static void OperatorTan(const Datum& param1, Datum& result);
			static void OperatorAtan(const Datum& param1, Datum& result);
			static void OperatorExp(const Datum& param1, Datum& result);
			static void OperatorLog(const Datum& param1, Datum& result);
			static void OperatorLog10(const Datum& param1, Datum& result);
			static void OperatorSqrt(const Datum& param1, Datum& result);
			static void OperatorIsqrt(const Datum& param1, Datum& result);
			static void OperatorPow(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorMax(const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorMin(const Datum& param1, const Datum& param2, Datum& result);

			static HashMap<std::string, OperatorType> OperatorTypes;
			static HashMap<OperatorType, std::function<void(RpnEvaluator&, const std::string& operatorString, const Attributed&, Datum&)>> MasterOperatorHandlers;
			static HashMap<std::string, std::function<void(const Datum&, Datum&)>> UnaryOperatorHandlers;
			static HashMap<std::string, std::function<void(const Datum&, const Datum&, Datum&)>> BinaryOperatorHandlers;
			static HashMap<RpnToken, Datum::DatumType> RpnTokenValueTypesToDatumTypes;
			static const char TokenSeparator;
		};
	}
}
