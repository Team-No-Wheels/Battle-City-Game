#include "XmlParseMaster.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
#pragma region SharedData Methods

		XmlParseMaster::SharedData::SharedData() : mParser(nullptr), mDepth(0)
		{
		}

		XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone()
		{
			return this;
		}

		void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster& parser)
		{
			parser;
		}

		XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster()
		{
			return mParser;
		}

		void XmlParseMaster::SharedData::IncrementDepth()
		{
		}

		void XmlParseMaster::SharedData::DecrementDepth()
		{
		}

		std::uint32_t XmlParseMaster::SharedData::Depth()
		{
			return mDepth;
		}

#pragma endregion

		XmlParseMaster::XmlParseMaster()
		{
		}

		XmlParseMaster::~XmlParseMaster()
		{
		}

		XmlParseMaster* XmlParseMaster::Clone()
		{
			return this;
		}

		void XmlParseMaster::AddHelper(IXmlParserHelper& helper)
		{
			helper;
		}

		void XmlParseMaster::RemoveHelper(IXmlParserHelper& helper)
		{
			helper;
		}

		void XmlParseMaster::Parse(const char* buffer, std::uint32_t length, bool isLastChunk)
		{
			buffer;
			length;
			isLastChunk;
		}

		void XmlParseMaster::ParseFromFile(std::string& filename)
		{
			mFilename = filename;
		}

		std::string XmlParseMaster::GetFileName()
		{
			return mFilename;
		}

		XmlParseMaster::SharedData* XmlParseMaster::GetSharedData()
		{
			return mSharedData;
		}

		void XmlParseMaster::SetSharedData(SharedData& sharedData)
		{
			sharedData;
		}

		void XmlParseMaster::StartElementHandler()
		{
		}

		void XmlParseMaster::EndElementHandler()
		{
		}

		void XmlParseMaster::CharDataHandler()
		{
		}
	}
}
