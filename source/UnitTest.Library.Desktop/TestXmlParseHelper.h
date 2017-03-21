#pragma once

#include "IXmlParseHelper.h"
#include <functional>
#include "TestSharedData.h"

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Parsers::IXmlParserHelper IXmlParserHelper;
	typedef AnonymousEngine::Parsers::SharedData SharedData;
	typedef AnonymousEngine::HashMap<std::string, std::string> AttributeMap;
	typedef const AnonymousEngine::HashMap<std::string, std::function<void(class TestXmlParserHelper&, const AttributeMap&)>> TagHandlerMap;

	class TestXmlParserHelper final : public IXmlParserHelper
	{
	public:
		TestXmlParserHelper() = default;
		void Initialize() override;
		bool StartElementHandler(SharedData& sharedData, const std::string& name, const AttributeMap& attributes) override;
		bool EndElementHandler(SharedData& sharedData, const std::string& name) override;
		void CharDataHandler(SharedData& sharedData, const std::string& buffer) override;
		IXmlParserHelper* Clone() override;
		~TestXmlParserHelper() = default;

	private:
		struct ParsingStackDataElement
		{
			std::string mElementName;
			AnonymousEngine::Scope* mScope;
			ParsingStackDataElement(std::string elementName, AnonymousEngine::Scope* scope = nullptr);
		};

		AnonymousEngine::Vector<ParsingStackDataElement> mStack;

		static AnonymousEngine::Vector<std::string> SupportedTags;

		RTTI_DECLARATIONS(TestXmlParserHelper, IXmlParserHelper)
	};
}
