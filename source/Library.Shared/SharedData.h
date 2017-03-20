#pragma once
#include "RTTI.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class XmlParseMaster;

		/** This class stores the data that is the result of a parse operation.
		*  The class is meant to be derived from to define functionality for
		*  storing various data formats
		*/
		class SharedData : public AnonymousEngine::RTTI
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
	}
}
