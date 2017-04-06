#include "OperatorExpressionNode.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		OperatorExpressionNode::OperatorExpressionNode(const std::string& op) :
			mOperator(op)
		{
		}

		Datum& OperatorExpressionNode::Value()
		{
			//TODO evaluate
			return mValue;
		}
	}
}
