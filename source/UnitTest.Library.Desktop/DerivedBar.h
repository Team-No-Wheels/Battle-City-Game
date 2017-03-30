#pragma once

#include "Bar.h"
#include "Factory.h"

namespace UnitTestLibraryDesktop
{
	class DerivedBar : public Bar
	{
	public:
		DerivedBar();
		DerivedBar(std::uint32_t value);
		DerivedBar(const DerivedBar& rhs);
		DerivedBar& operator=(const DerivedBar& rhs);
		bool operator==(const DerivedBar& rhs) const;
		bool operator!=(const DerivedBar& rhs) const;

		std::uint32_t IsAllocated() const;

		virtual ~DerivedBar() = default;
	private:
		bool mIsAllocated;
	};

	using namespace AnonymousEngine;
	CONCRETE_FACTORY_DECLARATIONS(Bar, DerivedBar);
}
