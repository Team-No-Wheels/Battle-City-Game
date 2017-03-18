#include "Pch.h"
#include "TestXmlParseHelper.h"

namespace UnitTestLibraryDesktop
{
	void TestXmlParserHelper::Initialize()
	{
		
	}

	bool TestXmlParserHelper::StartElementHandler(const std::string& name, AttributeMap attributes)
	{
		name;
		attributes;
		return true;
	}

	bool TestXmlParserHelper::EndElementHandler(const std::string& name)
	{
		name;
		return true;
	}

	void TestXmlParserHelper::CharDataHandler(const char* buffer, std::uint32_t length)
	{
		buffer;
		length;
	}

	IXmlParserHelper* TestXmlParserHelper::Clone()
	{
		return this;
	}
}
