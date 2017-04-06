#pragma once

#include "Datum.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		/** Each node in the expression tree needs to implement the value method
		 */
		class ExpressionNode
		{
		public:
			/** Returns the value of the node
			 *  @return The value of the node as a datum
			 */
			virtual Datum& Value() = 0;
			
			/** Free allocated resources
			 */
			virtual ~ExpressionNode() = default;
		};
	}
}
