#pragma once

#include <cstdint>
#include "IXmlParseHelper.h"
#include "Vector.h"
#include "Attributed.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class XmlParseMaster
		{
		public:
			class SharedData : public RTTI
			{
			public:
				SharedData();
				virtual SharedData* Clone();

				void SetXmlParseMaster(XmlParseMaster& parser);
				XmlParseMaster* GetXmlParseMaster();

				void IncrementDepth();
				void DecrementDepth();
				std::uint32_t Depth();

			private:
				XmlParseMaster* mParser;
				std::uint32_t mDepth;

				RTTI_DECLARATIONS(SharedData, RTTI)
			};

			XmlParseMaster();
			~XmlParseMaster();
			XmlParseMaster* Clone();
			void AddHelper(IXmlParserHelper& helper);
			void RemoveHelper(IXmlParserHelper& helper);
			void Parse(const char* buffer, std::uint32_t length, bool isLastChunk);
			void ParseFromFile(std::string& filename);
			std::string GetFileName();
			SharedData* GetSharedData();
			void SetSharedData(SharedData& sharedData);
		
		private:
			void StartElementHandler();
			void EndElementHandler();
			void CharDataHandler();

			Vector<IXmlParserHelper> mHelpers;
			std::string mFilename;
			SharedData* mSharedData;
		};
	}
}
