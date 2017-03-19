#pragma once

#include <cstdint>
#include "expat.h"
#include "IXmlParseHelper.h"
#include "Vector.h"
#include "Attributed.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class XmlParseMaster final
		{
		public:
			class SharedData : public RTTI
			{
			public:
				SharedData();
				virtual SharedData* Clone() const;
				virtual ~SharedData() = default;

				SharedData(const SharedData& rhs) = delete;
				SharedData& operator=(const SharedData& rhs) = delete;

				void SetXmlParseMaster(XmlParseMaster& parser);
				XmlParseMaster* GetXmlParseMaster() const;

				void IncrementDepth();
				void DecrementDepth();
				std::uint32_t Depth() const;

			private:
				XmlParseMaster* mParser;
				std::uint32_t mDepth;

				RTTI_DECLARATIONS(SharedData, RTTI)
			};

			XmlParseMaster();
			~XmlParseMaster() = default;
			XmlParseMaster* Clone() const;

			XmlParseMaster(const XmlParseMaster& rhs) = delete;
			XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;
			
			void AddHelper(IXmlParserHelper& helper);
			void RemoveHelper(IXmlParserHelper& helper);
			
			void Parse(const char* buffer, std::uint32_t length, bool isLastChunk);
			void ParseFromFile(const std::string& filename);
			
			std::string GetFileName() const ;
			SharedData* GetSharedData() const;
			void SetSharedData(SharedData& sharedData);

		private:
			static void StartElementHandler(void* userData, const XML_Char* name, const XML_Char** attributes);
			static void EndElementHandler(void* userData, const XML_Char* name);
			static void CharDataHandler(void* userData, const XML_Char* buffer, int length);

			XML_Parser mParser;
			Vector<IXmlParserHelper*> mHelpers;
			IXmlParserHelper* mCurrentElementHelper;
			std::string mFilename;
			SharedData* mSharedData;

			static const std::string UTF8_ENCODING;
		};
	}
}
