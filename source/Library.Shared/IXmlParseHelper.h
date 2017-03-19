#pragma once

#include <string>
#include "HashMap.h"
#include "XmlParseMaster.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class IXmlParserHelper
		{
		public:
			/** Initialize the helper's state by giving the reference to the data to modify
			 *  @param sharedData The data object which should be updated with the result of parsing
			 */
			virtual void Initialize(XmlParseMaster::SharedData& sharedData) = 0;

			/** Method to handle start of an element
			 *  @param name The name of the element
			 *  @param attributes A map of attribute names to values
			 *  @return Whether or not this helper handled the element start
			 */
			virtual bool StartElementHandler(const std::string& name, const HashMap<std::string, std::string>& attributes) = 0;

			/** Method to handle end of an element
			 *  @param name The name of the element
			 *  @return Whether or not this helper handled the element end
			 */
			virtual bool EndElementHandler(const std::string& name) = 0;

			/** Method to handle the character data inside an element
			 *  @param buffer A character buffer containing the data
			 *  @param length Number of characters in the buffer
			 */
			virtual void CharDataHandler(const char* buffer, std::uint32_t length) = 0;

			/** Clones this helper and returns another helper instance with the same state
			 */
			virtual IXmlParserHelper* Clone() = 0;

			/** Destructor to deallocate any memory
			 */
			virtual ~IXmlParserHelper() = default;
		};
	}
}
