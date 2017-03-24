#include "Pch.h"
#include "FooXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "FooSharedData.h"

namespace UnitTestLibraryDesktop
{

	RTTI_DEFINITIONS(FooXmlParserHelper)

	AnonymousEngine::Vector<std::string> FooXmlParserHelper::SupportedTags = {
		"award",
		"year",
		"categories",
		"category"
	};

	void FooXmlParserHelper::Initialize()
	{
		mStack.Clear();
	}

	bool FooXmlParserHelper::StartElementHandler(SharedData& sharedData, const std::string& name, const AttributeMap& attributes)
	{
		if (!sharedData.Is(FooSharedData::TypeIdClass()))
		{
			return false;
		}
		mStack.PushBack(name);
		if (SupportedTags.Find(name) != SupportedTags.end())
		{
			AnonymousEngine::Scope* scope = new AnonymousEngine::Scope();
			mStack.Back().mScope = scope;
			for (const auto& attribute : attributes)
			{
				scope->Append(attribute.first) = attribute.second;
			}
			return true;
		}
		return false;
	}

	bool FooXmlParserHelper::EndElementHandler(SharedData& sharedData, const std::string& name)
	{
		if (!sharedData.Is(FooSharedData::TypeIdClass()))
		{
			return false;
		}
		if (SupportedTags.Find(name) != SupportedTags.end())
		{
			ParsingStackDataElement element = mStack.Back();
			mStack.PopBack();
			if (sharedData.Depth() > 1)
			{
				mStack.Back().mScope->Adopt(*(element.mScope), element.mElementName);
			}
			else
			{
				FooSharedData* testSharedData = sharedData.As<FooSharedData>();
				testSharedData->mAwardWinners = element.mScope;
			}
			return true;
		}
		return false;
	}

	void FooXmlParserHelper::CharDataHandler(SharedData&, const std::string& buffer)
	{
		if (SupportedTags.Find(mStack.Back().mElementName) == SupportedTags.end())
		{
			ParsingStackDataElement charDataElement = mStack.Back();
			mStack.PopBack();
			mStack.Back().mScope->Append(charDataElement.mElementName) = buffer;
		}
	}

	IXmlParserHelper* FooXmlParserHelper::Clone()
	{
		FooXmlParserHelper* helper = new FooXmlParserHelper();
		helper->mStack = mStack;
		return helper;
	}

	FooXmlParserHelper::ParsingStackDataElement::ParsingStackDataElement(std::string elementName, AnonymousEngine::Scope* scope) :
		mElementName(elementName), mScope(scope)
	{
	}
}
