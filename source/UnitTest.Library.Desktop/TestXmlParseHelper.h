#pragma once

#include "IXmlParseHelper.h"

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Parsers::IXmlParserHelper IXmlParserHelper;
	typedef AnonymousEngine::HashMap<std::string, std::string> AttributeMap;

	class TestXmlParserHelper final : IXmlParserHelper
	{
	public:
		void Initialize() override;
		bool StartElementHandler(const std::string& name, AttributeMap attributes) override;
		bool EndElementHandler(const std::string& name) override;
		void CharDataHandler(const char* buffer, std::uint32_t length) override;
		IXmlParserHelper* Clone() override;
		~TestXmlParserHelper() = default;
	};
}
