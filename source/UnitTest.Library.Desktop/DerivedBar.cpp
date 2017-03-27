#include "Pch.h"
#include "DerivedBar.h"

namespace UnitTestLibraryDesktop
{
	DerivedBar::DerivedBar() :
		mIsAllocated(false)
	{
	}

	DerivedBar::DerivedBar(std::uint32_t value) :
		Bar(value), mIsAllocated(true)
	{
	}

	DerivedBar::DerivedBar(const DerivedBar& rhs) :
		Bar(rhs), mIsAllocated(true)
	{
	}

	DerivedBar& DerivedBar::operator=(const DerivedBar& rhs)
	{
		Bar::operator=(rhs);
		mIsAllocated = rhs.mIsAllocated;
		return *this;
	}

	bool DerivedBar::operator==(const DerivedBar& rhs) const
	{
		return (Bar::operator==(rhs) && (mIsAllocated == rhs.mIsAllocated));
	}

	bool DerivedBar::operator!=(const DerivedBar& rhs) const
	{
		return !(*this == rhs);
	}

	std::uint32_t DerivedBar::IsAllocated() const
	{
		return mIsAllocated;
	}

	using namespace AnonymousEngine;
	// Compiler warns for unreachable code here even though this is perfectly fine since it is a macro
	#pragma warning(suppress: 4702)
	CONCRETE_FACTORY_DEFINITIONS(Bar, DerivedBar);
}
