#pragma once

#include "XmlParseMaster.h"
#include <string>
#include "HashMap.h"
#include "Vector.h"
#include "Scope.h"

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Parsers::SharedData SharedData;

	class TestSharedData final : public SharedData
	{
	public:
		TestSharedData();
		~TestSharedData();
		SharedData* Clone() const override;

		AnonymousEngine::Scope*& AwardWinners();
	private:
		AnonymousEngine::Scope* mAwardWinners;

	public:
		typedef AnonymousEngine::HashMap<std::string, AnonymousEngine::Vector<struct Category>> DataMap;

		RTTI_DECLARATIONS(TestSharedData, SharedData)
	};
}
