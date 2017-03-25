#include "IXmlParseHelper.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(IXmlParserHelper)

		void IXmlParserHelper::Initialize()
		{
		}

		void IXmlParserHelper::CharDataHandler(SharedData&, const std::string&)
		{
			// Default implementation if a helper doesn't want to handle char data
		}
	}
}
