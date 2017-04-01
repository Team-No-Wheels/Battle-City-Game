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
			WorldSharedData();
			/** Deallocate resources
			 */
			~WorldSharedData();
			/** Create a new instance which has exact same state as this object. The new object should be explicitly
			 *  deleted by the user
			 */
			SharedData* Create() const override;

			/** Initialize the state of this data object
			 */
			void Initialize() override;

			/** Get the contained attributed. This call transfers ownership of the memory to the user
			 *  @return The contained attributed
			 */
			Containers::World* ExtractWorld();
		private:

			/** The current attributed class that is being populated
			 */
			Attributed* mAttributed;

			/** The stack for parsers to keep track of the element hierrarchy
			 */
			Vector<std::string> mElementStack;
			
			/* The list of vectors for parsing a matrix
			 */
			Vector<Datum> mMatrixVectors;

			/** The current matrix being processed
			 */
			std::string mMatrixName;

			friend class WorldParserHelper;

			RTTI_DECLARATIONS(WorldSharedData, SharedData)
		};
	}
}
