#include "Pch.h"
#include "Bar.h"

namespace UnitTestLibraryDesktop
{
	Bar::Bar() :
		mData(nullptr)
	{
	}

	Bar::Bar(std::uint32_t value) :
		mData(new std::uint32_t(value))
	{
	}

	Bar::Bar(const Bar& rhs) :
		mData(new std::uint32_t(*rhs.mData))
	{
	}

	Bar& Bar::operator=(const Bar& rhs)
	{
		if (this != &rhs)
		{
			*mData = *rhs.mData;
		}
		return *this;
	}

	bool Bar::operator==(const Bar& rhs) const
	{
		return (*mData == *rhs.mData);
	}

	bool Bar::operator!=(const Bar& rhs) const
	{
		return !(*this == rhs);
	}

	std::uint32_t Bar::Data() const
	{
		return *mData;
	}

	Bar::~Bar()
	{
		delete mData;
	}
}
