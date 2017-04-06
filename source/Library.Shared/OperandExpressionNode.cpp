#include "OperandExpressionNode.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		OperandExpressionNode::OperandExpressionNode(const Datum&& value) :
			mValue(std::move(value))
		{
		}

		Datum& OperandExpressionNode::Value()
		{
			return mValue;
		}
	}
}
