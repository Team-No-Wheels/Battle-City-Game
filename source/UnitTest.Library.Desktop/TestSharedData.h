#pragma once

#include "XmlParseMaster.h"
#include <string>
#include "HashMap.h"
#include "Vector.h"

namespace UnitTestLibraryDesktop
{
	typedef AnonymousEngine::Parsers::XmlParseMaster::SharedData SharedData;

	class TestSharedData final : public SharedData
	{
	public:
		TestSharedData();
		SharedData* Clone() const override;

		void SetYear(std::uint32_t year);
		void AppendCategoryToYear(const std::string& name, const std::string& game);


	private:
		struct Category
		{
			std::string mName;
			std::string mGame;

			Category(const std::string& name, const std::string& game) :
				mName(name), mGame(game)
			{
			}
		};

		std::string mName;
		AnonymousEngine::HashMap<std::uint32_t, AnonymousEngine::Vector<struct Category>> mAwardsOverYears;
		std::uint32_t mCurrentYear;

	public:
		typedef AnonymousEngine::HashMap<std::uint32_t, AnonymousEngine::Vector<struct Category>> DataMap;

		RTTI_DECLARATIONS(TestSharedData, SharedData)
	};
}
