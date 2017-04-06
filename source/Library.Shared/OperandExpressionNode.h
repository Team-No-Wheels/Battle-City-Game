#pragma once

#include "ExpressionNode.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class OperandExpressionNode : public ExpressionNode
		{
		public:
			OperandExpressionNode(const Datum&& datum);
			Datum& Value() override;
		private:
			Datum mValue;
		};
	}
}
