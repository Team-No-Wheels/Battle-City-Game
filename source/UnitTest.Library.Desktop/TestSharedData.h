#pragma once

#include "XmlParseMaster.h"
#include <string>
#include "HashMap.h"
#include "Vector.h"
#include "Scope.h"

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Parsers::XmlParseMaster::SharedData SharedData;

	class TestSharedData final : public SharedData
	{
	public:
		TestSharedData() = default;
		SharedData* Clone() const override;

		std::string& CurrentElementName();
		AnonymousEngine::Scope& AwardWinners();
		AnonymousEngine::Vector<AnonymousEngine::Scope*>& GetStack();
	private:
		AnonymousEngine::Scope* mAwardWinners;
		std::string mCurrentElementName;
		AnonymousEngine::Vector<AnonymousEngine::Scope*> mStack;

	public:
		typedef AnonymousEngine::HashMap<std::string, AnonymousEngine::Vector<struct Category>> DataMap;

		RTTI_DECLARATIONS(TestSharedData, SharedData)
	};
}
