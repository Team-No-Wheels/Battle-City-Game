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
			~ScopeSharedData();
			/** Create a new instance which has exact same state as this object. The new object should be explicitly
			 *  deleted by the user
			 */
			SharedData* Create() const override;

			/** Initialize the state of this data object
			 */
			void Initialize() override;

			/** Get the contained scope. This call transfers ownership of the memory to the user
			 *  @return The contained scope
			 */
			Scope* ExtractScope();

		private:
			/** The scope data which will be populated with the result of parsing
			 */
			Scope* mScope;

			friend class ScopeParseHelper;

			RTTI_DECLARATIONS(ScopeSharedData, SharedData)
		};
	}
}
