#include "SharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(SharedData)

		SharedData::SharedData() :
			mParser(nullptr), mDepth(0)
		{
		}

		SharedData* SharedData::Create() const
		{
			return new SharedData();
		}

		void SharedData::Initialize()
		{
			mDepth = 0;
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
			if (mDepth == 0)
			{
				throw std::runtime_error("Decrement depth called when depth is 0");
			}
			--mDepth;
		}

		std::uint32_t SharedData::Depth() const
		{
			return mDepth;
		}
	}
}
