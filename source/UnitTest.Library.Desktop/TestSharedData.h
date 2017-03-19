#pragma once

#include "XmlParseMaster.h"
#include <string>
#include "Vector.h"

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Parsers::XmlParseMaster::SharedData SharedData;

	class TestSharedData final : public SharedData
	{
	public:
		struct Category
		{
			std::string mName;
			std::string mGame;
		};

		struct Year
		{
			std::string mValue;
			AnonymousEngine::Vector<Category> mCategories;
		};

		TestSharedData();
		SharedData* Clone() const override;
	
	private:
		std::string mName;
		AnonymousEngine::Vector<Year> mYears;

		RTTI_DECLARATIONS(TestSharedData, SharedData)
	};
}
