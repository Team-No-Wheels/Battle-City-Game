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

		XmlParseMaster::XmlParseMaster(SharedData& sharedData) :
			mParser(XML_ParserCreate(UTF8_ENCODING.c_str())), mCurrentElementHelper(nullptr), mSharedData(&sharedData), mIsClone(false)
		{
			mSharedData->mParser = this;
			XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
			XML_SetCharacterDataHandler(mParser, CharDataHandler);
			XML_SetUserData(mParser, mSharedData);
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
			XmlParseMaster* parser = new XmlParseMaster(*mSharedData->Clone());
			for (const auto& helper : mHelpers)
			{
				parser->AddHelper(*(helper->Clone()));
			}
			parser->mCurrentElementHelper = nullptr;
			parser->mFilename = mFilename;
			parser->mIsClone = true;
			return parser;
		}

		void XmlParseMaster::AddHelper(IXmlParserHelper& helper)
		{
			if (mIsClone)
			{
				throw std::runtime_error("Can't add helpers to a cloned parser");
			}
			for (const auto& h : mHelpers)
			{
				if (h->TypeIdInstance() == helper.TypeIdInstance())
				{
					throw std::runtime_error("A helper of the same type is already added to the parser");
				}
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

		void XmlParseMaster::Parse(const std::string& buffer, bool isFirstChunk, bool isLastChunk)
		{
			if (isFirstChunk)
			{
				Initialize();
			}
			XML_Parse(mParser, buffer.c_str(), static_cast<std::uint32_t>(buffer.size()), isLastChunk);
		}

		void XmlParseMaster::ParseFromFile(const std::string& filename)
		{
			mFilename = filename;
			std::ifstream in(filename);
			if (!in.is_open())
			{
				throw std::runtime_error(std::string("Unable to read xml file. filename = ").append(filename));
			}
			std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
			Parse(contents);
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
			sharedData.mParser = this;
			XML_SetUserData(mParser, &sharedData);
		}

		void XmlParseMaster::Reset()
		{
			Initialize();
			mFilename.clear();
			mCurrentElementHelper = nullptr;
			XML_ParserReset(mParser, UTF8_ENCODING.c_str());
		}

		void XmlParseMaster::Initialize()
		{
			mSharedData->Initialize();
			for (auto& helper : mHelpers)
			{
				helper->Initialize();
			}
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
