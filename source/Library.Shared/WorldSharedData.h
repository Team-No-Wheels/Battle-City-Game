#pragma once

#include "XmlParseMaster.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class WorldSharedData final : public SharedData
		{
		public:
			/** Initialize the shared data
			 */
			WorldSharedData();
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

			/** The scope data which will be populated with the result of parsing
			 */
			Containers::World* mWorld;

			friend class WorldParserHelper;

			RTTI_DECLARATIONS(WorldSharedData, SharedData)
		};
	}
}
