#pragma once

#include "XmlParseMaster.h"
#include "WorldState.h"
#include "Scope.h"
#include "Attributed.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class WorldSharedData final : public SharedData
		{
		public:
			/** Initialize the shared data
			 */
			WorldSharedData() = default;
			/** Deallocate resources
			 */
			~WorldSharedData() = default;
			/** Create a new instance which has exact same state as this object. The new object should be explicitly
			 *  deleted by the user
			 */
			SharedData* Clone() const override;

			/** Initialize the state of this data object
			 */
			void Initialize() override;

			/** The current attributed class that is being populated
			 */
			Attributed* mAttributed;

			/** Keeps track of the parent list tag if the parsing is currently inside a list
			 */
			std::string mListTag;

			friend class WorldParserHelper;

			RTTI_DECLARATIONS(WorldSharedData, SharedData)
		};
	}
}
