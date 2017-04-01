#pragma once

#include <string>
#include "HashMap.h"
#include "SharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class IXmlParserHelper : public RTTI
		{
		public:
			/** Initialize the helper's state
			 */
			virtual void Initialize();

			/** Method to handle start of an element
			 *  @param name The name of the element
			 *  @param attributes A map of attribute names to values
			 *  @return Whether or not this helper handled the element start
			 */
			virtual bool StartElementHandler(SharedData& sharedData, const std::string& name, const HashMap<std::string, std::string>& attributes) = 0;

			/** Method to handle end of an element
			 *  @param name The name of the element
			 *  @return Whether or not this helper handled the element end
			 */
			virtual bool EndElementHandler(SharedData& sharedData, const std::string& name) = 0;

			/** Method to handle the character data inside an element
			 *  @param buffer A string buffer containing the char data
			 */
			virtual void CharDataHandler(SharedData& sharedData, const std::string& buffer);

			/** Creates a new helper of this type
			 */
			virtual IXmlParserHelper* Create() = 0;

			/** Destructor to deallocate any memory
			 */
			virtual ~IXmlParserHelper() = default;

			RTTI_DECLARATIONS(IXmlParserHelper, RTTI)
		};
	}
}
