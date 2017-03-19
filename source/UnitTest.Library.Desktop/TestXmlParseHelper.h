#pragma once

#include "IXmlParseHelper.h"
#include <functional>
#include "TestSharedData.h"

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Parsers::IXmlParserHelper IXmlParserHelper;
	typedef AnonymousEngine::HashMap<std::string, std::string> AttributeMap;
	typedef const AnonymousEngine::HashMap<std::string, std::function<void(class TestXmlParserHelper&, const AttributeMap&)>> TagHandlerMap;

	class TestXmlParserHelper final : IXmlParserHelper
	{
	public:
		TestXmlParserHelper();
		void Initialize(SharedData& sharedData) override;
		bool StartElementHandler(const std::string& name, const AttributeMap& attributes) override;
		bool EndElementHandler(const std::string& name) override;
		void CharDataHandler(const char* buffer, std::uint32_t length) override;
		IXmlParserHelper* Clone() override;
		~TestXmlParserHelper() = default;

	private:
		void ValidateInitialization() const;
		static void HandleAwardElement(TestXmlParserHelper& instance, const AttributeMap& attributes);
		static void HandleYearElement(TestXmlParserHelper& instance, const AttributeMap& attributes);
		static void HandleCategoriesElement(TestXmlParserHelper& instance, const AttributeMap& attributes);
		static void HandleCategoryElement(TestXmlParserHelper& instance, const AttributeMap& attributes);

		TestSharedData* mData;
		static TagHandlerMap TagHandlers;
	};
}
