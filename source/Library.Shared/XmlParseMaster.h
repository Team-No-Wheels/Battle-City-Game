#pragma once

#include <cstdint>
#include "IXmlParseHelper.h"
#include "Vector.h"
#include "RTTI.h"
#include "SharedData.h"

struct XML_ParserStruct;

namespace AnonymousEngine
{
	namespace Parsers
	{
		/** This class handles XmlParsing workflow
		*/
		class XmlParseMaster final
		{
		public:
			/** Initializes the parser
			 */
			XmlParseMaster(SharedData& sharedData);
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
			 *  @param isFirstChunk Whether the current data is the first chunk from the xml
			 *  @param isLastChunk Whether the current data is the last chunk from the xml
			 */
			void Parse(const std::string& buffer, bool isFirstChunk = true, bool isLastChunk = true);
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

			/** Clear all parsing state so that the parse master is ready to parse new content
			 */
			void Reset();

		private:
			void Initialize();

			static void StartElementHandler(void* userData, const char* name, const char** attributes);
			static void EndElementHandler(void* userData, const char* name);
			static void CharDataHandler(void* userData, const char* buffer, int length);
			static std::string TrimString(const std::string& string);

			XML_ParserStruct* mParser;
			Vector<IXmlParserHelper*> mHelpers;
			IXmlParserHelper* mCurrentElementHelper;
			std::string mFilename;
			SharedData* mSharedData;

			bool mIsClone;

			static const std::string UTF8_ENCODING;
		};
	}
}
