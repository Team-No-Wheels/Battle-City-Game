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

	TestXmlParserHelper::TestXmlParserHelper() :
		mData(nullptr)
	{
	}

	TestXmlParserHelper::~TestXmlParserHelper()
	{
		if (mData != nullptr && mData->AwardWinners() != nullptr)
		{
			delete mData->AwardWinners();
		}
	}

	void TestXmlParserHelper::Initialize(SharedData& sharedData)
	{
		if (sharedData.Is(TestSharedData::TypeIdClass()))
		{
			mData = static_cast<TestSharedData*>(&sharedData);
		}
		else
		{
			throw std::runtime_error("Incorrect shared data type passed to initialize");
		}
	}

	bool TestXmlParserHelper::StartElementHandler(const std::string& name, const AttributeMap& attributes)
	{
		ValidateInitialization();
		mData->CurrentElementName() = name;
		if (SupportedTags.Find(name) != SupportedTags.end())
		{
			AnonymousEngine::Scope* scope = new AnonymousEngine::Scope();
			mData->GetStack().PushBack(scope);
			mData->IncrementDepth();
			attributes;
			/*for (const auto& attribute : attributes)
			{
				scope->Append(attribute.first) = attribute.second;
			}*/
			return true;
		}
		return false;
	}

	bool TestXmlParserHelper::EndElementHandler(const std::string& name)
	{
		ValidateInitialization();
		bool didHandle = false;
		if (SupportedTags.Find(name) != SupportedTags.end())
		{
			auto& stack = mData->GetStack();
			AnonymousEngine::Scope* scope = stack.Back();
			stack.PopBack();
			mData->DecrementDepth();
			if (mData->Depth() > 0)
			{
				stack.Back()->Adopt(*scope, mData->CurrentElementName());
			}
			else
			{
				mData->AwardWinners() = scope;
			}
			didHandle = true;
		}
		mData->CurrentElementName().clear();
		return didHandle;
	}

	void TestXmlParserHelper::CharDataHandler(const char* buffer, std::uint32_t length)
	{
		ValidateInitialization();
		if (SupportedTags.Find(mData->CurrentElementName()) == SupportedTags.end())
		{
			auto& top = mData->GetStack().Back();
			top->Append(mData->CurrentElementName()) = std::string(buffer, length);
		}
	}

	IXmlParserHelper* TestXmlParserHelper::Clone()
	{
		TestXmlParserHelper* helper = new TestXmlParserHelper();
		helper->mData = mData;
		return helper;
	}

	void TestXmlParserHelper::ValidateInitialization() const
	{
		if (mData == nullptr)
		{
			throw std::runtime_error("Data is not initialized");
		}
	}
}
