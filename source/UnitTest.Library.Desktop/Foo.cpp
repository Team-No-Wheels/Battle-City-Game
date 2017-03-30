#include "Pch.h"
#include "Foo.h"
#include "Factory.h"

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

	bool Foo::operator!=(const Foo& rhs) const
	{
		return !(*this == rhs);
	}

	std::uint32_t Foo::Data() const
	{
		return *mData;
	}

	Foo::~Foo()
	{
		delete mData;
	}

	bool Foo::Equals(const AnonymousEngine::RTTI * rhs) const
	{
		if (this == rhs)
		{
			return true;
		}

		if (rhs == nullptr)
		{
			return false;
		}

		const Foo* foo = rhs->As<Foo>();
		if (foo != nullptr)
		{
			return operator==(*foo);
		}
		return false;
	}

	std::string Foo::ToString() const
	{
		return std::to_string(*mData);
	}

	void Foo::FromString(const std::string& str)
	{
		*mData = std::stoul(str);
	}
	
	using namespace AnonymousEngine;
	// Compiler warns for unreachable code here even though this is perfectly fine since it is a macro
	#pragma warning(suppress: 4702)
	CONCRETE_FACTORY_DEFINITIONS(RTTI, Foo);
}
