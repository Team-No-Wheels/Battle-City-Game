#include "XmlParseMaster.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include "expat.h"
#include "IXmlParseHelper.h"
#include "HashMap.h"
#include "SharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		const std::string XmlParseMaster::UTF8_ENCODING = "UTF-8";

		XmlParseMaster::XmlParseMaster() :
			mParser(XML_ParserCreate(UTF8_ENCODING.c_str())), mCurrentElementHelper(nullptr), mSharedData(nullptr), mIsClone(false)
		{
			XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(mParser, CharDataHandler);
		}

		XmlParseMaster::~XmlParseMaster()
		{
			XML_ParserFree(mParser);
			if (mIsClone)
			{
				for(auto helper : mHelpers)
				{
					delete helper;
				}
				delete mSharedData;
			}
		}

		XmlParseMaster* XmlParseMaster::Clone() const
		{
			XmlParseMaster* parser = new XmlParseMaster();
			for (const auto& helper : mHelpers)
			{
				parser->AddHelper(*(helper->Clone()));
			}
			parser->mCurrentElementHelper = nullptr;
			parser->mFilename = mFilename;
			parser->mSharedData = mSharedData->Clone();
			parser->mSharedData->SetXmlParseMaster(*parser);
			parser->mIsClone = true;
			return parser;
		}

		void XmlParseMaster::AddHelper(IXmlParserHelper& helper)
		{
			if (mIsClone)
			{
				throw std::runtime_error("Can't add helpers to a cloned parser");
			}
			mHelpers.PushBack(&helper);
		}

		void XmlParseMaster::RemoveHelper(IXmlParserHelper& helper)
		{
			if (mIsClone)
			{
				throw std::runtime_error("Can't remove helpers from a cloned parser");
			}
			mHelpers.Remove(&helper);
		}

		void XmlParseMaster::Parse(const std::string& buffer, bool isLastChunk)
		{
			XML_Parse(mParser, buffer.c_str(), static_cast<std::uint32_t>(buffer.size()), isLastChunk);
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
				Parse(contents, true);
			}
		}

		std::string XmlParseMaster::GetFileName() const
		{
			return mFilename;
		}

		SharedData* XmlParseMaster::GetSharedData() const
		{
			return mSharedData;
		}

		void XmlParseMaster::SetSharedData(SharedData& sharedData)
		{
			this->mSharedData = &sharedData;
			XML_SetUserData(mParser, &sharedData);
		}

		void XmlParseMaster::StartElementHandler(void *userData, const XML_Char *name, const XML_Char **attributes)
		{
			SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
			XmlParseMaster* parseMaster = sharedData->GetXmlParseMaster();

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
				if (helper->StartElementHandler(*sharedData, tagName, attributeMap))
				{
					parseMaster->mCurrentElementHelper = helper;
					break;
				}
			}
		}

		void XmlParseMaster::EndElementHandler(void *userData, const XML_Char *name)
		{
			SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
			XmlParseMaster* parseMaster = sharedData->GetXmlParseMaster();
			for (auto& helper : parseMaster->mHelpers)
			{
				std::string tagName(name);
				std::transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);
				if (helper->EndElementHandler(*sharedData, tagName))
				{
					parseMaster->mCurrentElementHelper = nullptr;
					break;
				}
			}
		}

		void XmlParseMaster::CharDataHandler(void* userData, const XML_Char* buffer, int length)
		{
			SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
			XmlParseMaster* parseMaster = sharedData->GetXmlParseMaster();
			std::string bufferData = TrimString(std::string(buffer, length));
			if (parseMaster->mCurrentElementHelper != nullptr && bufferData.size() > 0)
			{
				parseMaster->mCurrentElementHelper->CharDataHandler(*sharedData, std::string(buffer, length));
			}
		}

		std::string XmlParseMaster::TrimString(const std::string& string)
		{
			auto front = std::find_if_not(string.begin(), string.end(), [] (std::int32_t character) { return std::isspace(character); });
			auto back = std::find_if_not(string.rbegin(), string.rend(), [](std::int32_t character) { return std::isspace(character); }).base();
			return ((back <= front) ? std::string() : std::string(front, back));
		}
	}
}
