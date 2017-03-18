#pragma once

#include <string>
#include "HashMap.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class IXmlParserHelper
		{
		public:
			virtual void Initialize() = 0;
			virtual bool StartElementHandler(const std::string& name, HashMap<std::string, std::string> attributes) = 0;
			virtual bool EndElementHandler(const std::string& name) = 0;
			virtual void CharDataHandler(const char* buffer, std::uint32_t length) = 0;
			virtual IXmlParserHelper* Clone() = 0;
			virtual ~IXmlParserHelper() = default;
		};
	}
}
