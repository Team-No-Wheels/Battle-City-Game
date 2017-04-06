#pragma once

#include "ExpressionNode.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class OperatorExpressionNode : public ExpressionNode
		{
		public:
			OperatorExpressionNode(const std::string& op);
			Datum& Value() override;

		private:
			const std::string mOperator;
			Datum mValue;
		};
	}
}
