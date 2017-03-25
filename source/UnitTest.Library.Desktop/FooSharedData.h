#pragma once

#include "XmlParseMaster.h"
#include <string>
#include "HashMap.h"
#include "Vector.h"
#include "Scope.h"

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Parsers::SharedData SharedData;

	class FooSharedData final : public SharedData
	{
	public:
		FooSharedData();
		~FooSharedData() = default;
		SharedData* Clone() const override;

		void Initialize() override;

		// any allocated data is not deleted by this class
		AnonymousEngine::Scope* mAwardWinners;

		typedef AnonymousEngine::HashMap<std::string, AnonymousEngine::Vector<struct Category>> DataMap;

		RTTI_DECLARATIONS(FooSharedData, SharedData)
	};
}
