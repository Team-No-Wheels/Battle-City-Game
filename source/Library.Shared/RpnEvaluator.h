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

			struct OperatorSignature
			{
				OperatorType mOperatorType;
				Vector<Vector<RpnToken>> mSignatures;
			};

			/** Evaluate an RPN expression from the given scope and store the result in the given datum
			 *  @param rpnExpression The expression to evaluate
			 *  @param context The scope context in which the values are to be evaluated in
			 *  @param result An output parameter to store the evaluated result
			 */
			void EvaluateRPN(const std::string& rpnExpression, const Attributed& context, Datum& result);
		private:
			// The stack used for evaluation
			Vector<std::string> mStack;

			static void OperatorFunction(RpnEvaluator& evaluator, Datum& result);
			static void OperatorSubscript(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorDot(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorNot(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorMultiply(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorDivide(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorModulus(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorSubtract(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorAdd(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLeftShift(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorRightShift(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLessThan(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorGreaterThan(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLessThanOrEqual(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorGreaterThanOrEqual(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorEquals(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorNotEquals(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorBitwiseAnd(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorBitwiseXor(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorBitwiseOr(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorLogicalAnd(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorLogicalOr(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorSin(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorCos(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorTan(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorAtan(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorExp(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorLog(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorLog10(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorSqrt(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorIsqrt(RpnEvaluator& evaluator, const Datum& param1, Datum& result);
			static void OperatorPow(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorMax(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);
			static void OperatorMin(RpnEvaluator& evaluator, const Datum& param1, const Datum& param2, Datum& result);

			static HashMap<std::string, OperatorSignature> Signatures;
			static HashMap<std::string, std::function<void(RpnEvaluator&, Datum&)>> MultiOperatorHandlers;
			static HashMap<std::string, std::function<void(RpnEvaluator&, const Datum&, Datum&)>> UnaryOperatorHandlers;
			static HashMap<std::string, std::function<void(RpnEvaluator&, const Datum&, const Datum&, Datum&)>> BinaryOperatorHandlers;
		};
	}
}
