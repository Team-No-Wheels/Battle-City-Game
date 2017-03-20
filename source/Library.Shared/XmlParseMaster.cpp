#include "XmlParseMaster.h"
#include <fstream>
#include "expat.h"
#include "IXmlParseHelper.h"
#include "HashMap.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		#pragma region SharedDataDefinitions

		RTTI_DEFINITIONS(XmlParseMaster::SharedData)

		XmlParseMaster::SharedData::SharedData() : mParser(nullptr), mDepth(0)
		{
		}

		XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone() const
		{
			SharedData* sharedData =  new SharedData();
			sharedData->mDepth = mDepth;
			sharedData->mParser = mParser;
			return sharedData;
		}

		void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster& parser)
		{
			mParser = &parser;
		}

		XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster() const
		{
			return mParser;
		}

		void XmlParseMaster::SharedData::IncrementDepth()
		{
			++mDepth;
		}

		void XmlParseMaster::SharedData::DecrementDepth()
		{
			--mDepth;
		}

		std::uint32_t XmlParseMaster::SharedData::Depth() const
		{
			return mDepth;
		}

		#pragma endregion

		#pragma region XmlParseMasterDefinitions

		const std::string XmlParseMaster::UTF8_ENCODING = "UTF-8";

		XmlParseMaster::XmlParseMaster() :
			mParser(XML_ParserCreate(UTF8_ENCODING.c_str())), mCurrentElementHelper(nullptr)
		{
			XML_SetUserData(mParser, this);
			XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(mParser, CharDataHandler);
		}

		XmlParseMaster::~XmlParseMaster()
		{
			XML_ParserFree(mParser);
		}

		XmlParseMaster* XmlParseMaster::Clone() const
		{
			XmlParseMaster* parser = new XmlParseMaster();
			parser->mParser = mParser;
			parser->mHelpers = mHelpers;
			parser->mCurrentElementHelper = mCurrentElementHelper;
			parser->mFilename = mFilename;
			parser->mSharedData = mSharedData->Clone();
			parser->mSharedData->SetXmlParseMaster(*parser);
			return parser;
		}

		void XmlParseMaster::AddHelper(IXmlParserHelper& helper)
		{
			mHelpers.PushBack(&helper);
		}

		void XmlParseMaster::RemoveHelper(IXmlParserHelper& helper)
		{
			mHelpers.Remove(&helper);
		}

		void XmlParseMaster::Parse(const char* buffer, std::uint32_t length, bool isLastChunk)
		{
			XML_Parse(mParser, buffer, length, isLastChunk);
		}

		void XmlParseMaster::ParseFromFile(const std::string& filename)
		{
			mFilename = filename;
			std::ifstream in(filename);
			if (in.is_open())
			{
				std::string contents;
				in.seekg(0, std::ios::end);
				contents.resize(static_cast<std::uint32_t>(in.tellg()));
				in.seekg(0, std::ios::beg);
				in.read(&contents[0], contents.size());
				in.close();
				Parse(contents.c_str(), static_cast<std::uint32_t>(contents.size()), true);
			}
		}

		std::string XmlParseMaster::GetFileName() const
		{
			return mFilename;
		}

		XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
		{
			return mSharedData;
		}

		void XmlParseMaster::SetSharedData(SharedData& sharedData)
		{
			this->mSharedData = &sharedData;
		}

		void XmlParseMaster::StartElementHandler(void *userData, const XML_Char *name, const XML_Char **attributes)
		{
			XmlParseMaster* parseMaster = reinterpret_cast<XmlParseMaster*>(userData);

			// prepare name and attribute data for helpers
			HashMap<std::string, std::string> attributeMap;
			for (std::uint32_t i = 0; attributes[i] != nullptr; i += 2)
			{
				std::string attribute(attributes[i]);
				std::transform(attribute.begin(), attribute.end(), attribute.begin(), ::tolower);
				attributeMap[attribute] = attributes[i + 1];
			}

			// walk the helper chain to handle the responsibility
			for (auto& helper : parseMaster->mHelpers)
			{
				std::string tagName(name);
				std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
				if (helper->StartElementHandler(tagName, attributeMap))
				{
					parseMaster->mCurrentElementHelper = helper;
					break;
				}
			}
		}

		void XmlParseMaster::EndElementHandler(void *userData, const XML_Char *name)
		{
			XmlParseMaster* parseMaster = reinterpret_cast<XmlParseMaster*>(userData);
			for (auto& helper : parseMaster->mHelpers)
			{
				std::string tagName(name);
				std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
				if (helper->EndElementHandler(tagName))
				{
					parseMaster->mCurrentElementHelper = nullptr;
					break;
				}
			}
		}

		void XmlParseMaster::CharDataHandler(void* userData, const XML_Char* buffer, int length)
		{
			XmlParseMaster* parseMaster = reinterpret_cast<XmlParseMaster*>(userData);
			if (parseMaster->mCurrentElementHelper != nullptr)
			{
				parseMaster->mCurrentElementHelper->CharDataHandler(buffer, length);
			}
		}

		#pragma endregion
	}
}
