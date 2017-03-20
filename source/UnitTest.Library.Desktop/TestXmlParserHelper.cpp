#include "Pch.h"
#include "TestXmlParseHelper.h"
#include "XmlParseMaster.h"

namespace UnitTestLibraryDesktop
{
	AnonymousEngine::Vector<std::string> TestXmlParserHelper::SupportedTags = {
		"award",
		"year",
		"categories",
		"category"
	};

	TestXmlParserHelper::TestXmlParserHelper()
	{
	}

	TestXmlParserHelper::~TestXmlParserHelper()
	{
	}

	void TestXmlParserHelper::Initialize()
	{
	}

	bool TestXmlParserHelper::StartElementHandler(SharedData& sharedData, const std::string& name, const AttributeMap& attributes)
	{
		if (!sharedData.Is(TestSharedData::TypeIdClass()))
		{
			return false;
		}
		mStack.PushBack(name);
		if (SupportedTags.Find(name) != SupportedTags.end())
		{
			AnonymousEngine::Scope* scope = new AnonymousEngine::Scope();
			mStack.Back().mScope = scope;
			sharedData.IncrementDepth();
			for (const auto& attribute : attributes)
			{
				scope->Append(attribute.first) = attribute.second;
			}
			return true;
		}
		return false;
	}

	bool TestXmlParserHelper::EndElementHandler(SharedData& sharedData, const std::string& name)
	{
		if (!sharedData.Is(TestSharedData::TypeIdClass()))
		{
			return false;
		}
		if (SupportedTags.Find(name) != SupportedTags.end())
		{
			ParsingStackDataElement element = mStack.Back();
			mStack.PopBack();
			sharedData.DecrementDepth();
			if (sharedData.Depth() > 0)
			{
				mStack.Back().mScope->Adopt(*(element.mScope), element.mElementName);
			}
			else
			{
				TestSharedData* testSharedData = sharedData.As<TestSharedData>();
				testSharedData->AwardWinners() = element.mScope;
			}
			return true;
		}
		return false;
	}

	void TestXmlParserHelper::CharDataHandler(SharedData& sharedData, const std::string& buffer)
	{
		if (!sharedData.Is(TestSharedData::TypeIdClass()))
		{
			return;
		}
		if (SupportedTags.Find(mStack.Back().mElementName) == SupportedTags.end())
		{
			ParsingStackDataElement& charDataElement = mStack.Back();
			mStack.PopBack();
			mStack.Back().mScope->Append(charDataElement.mElementName) = buffer;
		}
	}

	IXmlParserHelper* TestXmlParserHelper::Clone()
	{
		TestXmlParserHelper* helper = new TestXmlParserHelper();
		return helper;
	}

	TestXmlParserHelper::ParsingStackDataElement::ParsingStackDataElement(std::string elementName, AnonymousEngine::Scope* scope) :
		mElementName(elementName), mScope(scope)
	{
	}
}
