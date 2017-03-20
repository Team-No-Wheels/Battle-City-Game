#pragma once

#include <cstdint>
#include "expat.h"
#include "RTTI.h"
#include "Vector.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class IXmlParserHelper;

		/** This class handles XmlParsing workflow
		 */
		class XmlParseMaster final
		{
		public:
			/** This class stores the data that is the result of a parse operation.
			 *  The class is meant to be derived from to define functionality for
			 *  storing various data formats
			 */
			class SharedData : public RTTI
			{
			public:
				/** Initializes a default constructed object of shared data
				 */
				SharedData();
				/** Creates a new instance of SharedData which shares all state information from the current one
				 *  The caller should take responsibility of freeing the memory of the new instance
				 *  @return The cloned instance
				 */
				virtual SharedData* Clone() const;
				/** Release any resource acquisitions
				 */
				virtual ~SharedData() = default;

				/** Delete copy constructor since only clone is supported
				 */
				SharedData(const SharedData& rhs) = delete;
				/** Delete copy assignment since only clone is supported
				 */
				SharedData& operator=(const SharedData& rhs) = delete;

				/** Update the parser which is using this SharedData instance
				 *  @param parser The parser which is using this shared data instance
				 */
				void SetXmlParseMaster(XmlParseMaster& parser);
				/** Get the parser which is using this shared data instance
				 *  @return The address of the parser which is using this shared data instance
				 */
				XmlParseMaster* GetXmlParseMaster() const;

				/** Increments the depth of the element tree being parsed by one
				 */
				void IncrementDepth();
				/** Decrements the depth of the element tree being parsed by one
				 */
				void DecrementDepth();
				/** Get the depth of the current element being processed in the element tree
				 */
				std::uint32_t Depth() const;

			private:
				XmlParseMaster* mParser;
				std::uint32_t mDepth;

				RTTI_DECLARATIONS(SharedData, RTTI)
			};

			/** Initializes the parser
			 */
			XmlParseMaster();
			/** Releases any allocated resources by the parser
			 */
			~XmlParseMaster();
			/** Creates a new instance of XmlParseMaster which has all the states of this instance
			 *  The caller should take responsibility of freeing the memory of the new instance
			 *  @return The cloned instance
			 */
			XmlParseMaster* Clone() const;

			/** Delete copy constructor since clone method is the only supported operator
			 */
			XmlParseMaster(const XmlParseMaster& rhs) = delete;
			/** Delete copy assignment operator since clone method is the only supported operator
			*/
			XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;
			
			/** Adds a helper to the list of available helpers in the parser
			 *  @param helper The new helper to add to the parser
			 */
			void AddHelper(IXmlParserHelper& helper);
			/** Removes a helper from the list of available helpers in the parser
			 *  @param helper The new helper to add to the parser
			 */
			void RemoveHelper(IXmlParserHelper& helper);
			
			/** Parse an xml passed as a C-style character buffer
			 *  @param buffer The buffer of characters read from the xml
			 *  @param length Number of characters in the buffer
			 *  @param isLastChunk Whether the current data is the last chunk from the xml
			 */
			void Parse(const char* buffer, std::uint32_t length, bool isLastChunk);
			/** Parse an xml from a file
			 *  @param filename The name of the xml file
			 */
			void ParseFromFile(const std::string& filename);
			
			/** Get the current file name
			 *  @return The current file being processed
			 */
			std::string GetFileName() const;
			/** Get the shared data that is being updated by the parsing
			 *  @return The current shared data being updated
			 */
			SharedData* GetSharedData() const;
			/** Set the shared data instance to be updated during the parse
			 *  @param sharedData A reference to the shared data object to be updated
			 */
			void SetSharedData(SharedData& sharedData);

		private:
			static void StartElementHandler(void* userData, const XML_Char* name, const XML_Char** attributes);
			static void EndElementHandler(void* userData, const XML_Char* name);
			static void CharDataHandler(void* userData, const XML_Char* buffer, int length);
			static std::string TrimString(const std::string& string);

			XML_Parser mParser;
			Vector<IXmlParserHelper*> mHelpers;
			IXmlParserHelper* mCurrentElementHelper;
			std::string mFilename;
			SharedData* mSharedData;

			static const std::string UTF8_ENCODING;
		};
	}
}
