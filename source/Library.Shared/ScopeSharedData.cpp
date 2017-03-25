#include "ScopeSharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(ScopeSharedData)

		ScopeSharedData::ScopeSharedData() :
			mScope(nullptr)
		{	
		}

		SharedData* ScopeSharedData::Clone() const
		{
			ScopeSharedData* data = new ScopeSharedData();
			data->mDepth = mDepth;
			data->mParser = mParser;
			data->mScope = (mScope == nullptr) ? nullptr : new AnonymousEngine::Scope(*mScope);
			return data;
		}

		void ScopeSharedData::Initialize()
		{
			SharedData::Initialize();
			mScope = nullptr;
		}
	}
}
