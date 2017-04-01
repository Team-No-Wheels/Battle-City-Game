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

		ScopeSharedData::~ScopeSharedData()
		{
			delete mScope;
		}

		SharedData* ScopeSharedData::Create() const
		{
			return new ScopeSharedData();
		}

		void ScopeSharedData::Initialize()
		{
			SharedData::Initialize();
			delete mScope;
		}

		Scope* ScopeSharedData::ExtractScope()
		{
			Scope* scope = mScope;
			mScope = nullptr;
			return scope;
		}
	}
}
