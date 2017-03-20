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
		mCurrentElementName = name;
		if (SupportedTags.Find(name) != SupportedTags.end())
		{
			AnonymousEngine::Scope* scope = new AnonymousEngine::Scope();
			mStack.PushBack(scope);
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
			AnonymousEngine::Scope* scope = mStack.Back();
			mStack.PopBack();
			sharedData.DecrementDepth();
			if (sharedData.Depth() > 0)
			{
				mStack.Back()->Adopt(*scope, mCurrentElementName);
			}
			else
			{
				TestSharedData* testSharedData = sharedData.As<TestSharedData>();
				testSharedData->AwardWinners() = scope;
			}
			//mCurrentElementName = scope->GetParentKey();
			mCurrentElementName.clear();
			return true;
		}
		mCurrentElementName.clear();
		return false;
	}

	void TestXmlParserHelper::CharDataHandler(SharedData& sharedData, const std::string& buffer)
	{
		if (!sharedData.Is(TestSharedData::TypeIdClass()))
		{
			return;
		}
		if (SupportedTags.Find(mCurrentElementName) == SupportedTags.end())
		{
			auto& top = mStack.Back();
			top->Append(mCurrentElementName) = buffer;
		}
	}

	IXmlParserHelper* TestXmlParserHelper::Clone()
	{
		TestXmlParserHelper* helper = new TestXmlParserHelper();
		return helper;
	}
}
