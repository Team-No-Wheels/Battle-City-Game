#include "Pch.h"
#include "TestXmlParseHelper.h"
#include "XmlParseMaster.h"

namespace UnitTestLibraryDesktop
{
	TagHandlerMap TestXmlParserHelper::TagHandlers = {
		{"award", HandleAwardElement},
		{"year", HandleYearElement},
		{"categories", HandleCategoriesElement},
		{"category", HandleCategoryElement}
	};

	TestXmlParserHelper::TestXmlParserHelper() :
		mData(nullptr)
	{
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
		if (TagHandlers.ContainsKey(name))
		{
			mData->IncrementDepth();
			TagHandlers[name](*this, attributes);
			return true;
		}
		return false;
	}

	bool TestXmlParserHelper::EndElementHandler(const std::string& name)
	{
		ValidateInitialization();
		if (TagHandlers.ContainsKey(name))
		{
			mData->DecrementDepth();
			return true;
		}
		return false;
	}

	void TestXmlParserHelper::CharDataHandler(const char*, std::uint32_t)
	{
		ValidateInitialization();
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

	void TestXmlParserHelper::HandleAwardElement(TestXmlParserHelper&, const AttributeMap&)
	{
	}

	void TestXmlParserHelper::HandleYearElement(TestXmlParserHelper& instance, const AttributeMap& attributes)
	{
		instance.mData->SetYear(std::stoi(attributes["year"]));
	}

	void TestXmlParserHelper::HandleCategoriesElement(TestXmlParserHelper&, const AttributeMap&)
	{
	}

	void TestXmlParserHelper::HandleCategoryElement(TestXmlParserHelper& instance, const AttributeMap& attributes)
	{
		instance.mData->AppendCategoryToYear(attributes["name"], attributes["game"]);
	}
}
