#include "SharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(SharedData)

		SharedData::SharedData() : mParser(nullptr), mDepth(0)
		{
		}

		SharedData* SharedData::Clone() const
		{
			SharedData* sharedData = new SharedData();
			sharedData->mDepth = mDepth;
			sharedData->mParser = mParser;
			return sharedData;
		}

		void SharedData::SetXmlParseMaster(XmlParseMaster& parser)
		{
			mParser = &parser;
		}

		XmlParseMaster* SharedData::GetXmlParseMaster() const
		{
			return mParser;
		}

		void SharedData::IncrementDepth()
		{
			++mDepth;
		}

		void SharedData::DecrementDepth()
		{
			--mDepth;
		}

		std::uint32_t SharedData::Depth() const
		{
			return mDepth;
		}
	}
}
