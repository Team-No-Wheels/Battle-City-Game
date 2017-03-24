#pragma once

#include "XmlParseMaster.h"
#include "HashMap.h"
#include "Vector.h"
#include "Scope.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class ScopeSharedData final : public SharedData
		{
		public:
			/** Initialize the shared data
			 */
			ScopeSharedData();
			/** Deallocate resources
			 */
			~ScopeSharedData() = default;
			/** Create a new instance which has exact same state as this object. The new object should be explicitly
			 *  deleted by the user
			 */
			SharedData* Clone() const override;

			/** Initialize the state of this data object
			 */
			void Initialize() override;

			/** The scope data which will be populated with the result of parsing
			 */
			Scope* mScope;

			friend class StandardTypesParseHelper;

			RTTI_DECLARATIONS(ScopeSharedData, SharedData)
		};
	}
}
