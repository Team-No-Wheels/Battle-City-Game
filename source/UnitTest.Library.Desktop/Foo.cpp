#include "Pch.h"
#include "Foo.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(Foo)

	Foo::Foo() : mData(new std::uint32_t(0))
	{
	}

	Foo::Foo(std::uint32_t value) : mData(new std::uint32_t(value))
	{
	}

	Foo::Foo(const Foo& rhs) : mData(new std::uint32_t(*rhs.mData))
	{
	}

	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
		{
			*mData = *rhs.mData;
		}
		return *this;
	}

	bool Foo::operator==(const Foo& rhs) const
	{
		return (*mData == *rhs.mData);
	}

	std::uint32_t Foo::Data() const
	{
		return *mData;
	}

	Foo::~Foo()
	{
		delete mData;
	}

	std::string Foo::ToString() const
	{
		return std::to_string(*mData);
	}

	void Foo::FromString(const std::string& str)
	{
		*mData = std::stoi(str);
	}
}
