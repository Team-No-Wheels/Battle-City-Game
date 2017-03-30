#pragma once

#include "RTTI.h"
#include "Factory.h"

namespace UnitTestLibraryDesktop
{
	class Foo : public AnonymousEngine::RTTI
	{
	public:
		Foo();
		Foo(std::uint32_t value);
		Foo(const Foo& rhs);
		Foo& operator=(const Foo& rhs);
		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;

		std::uint32_t Data() const;

		virtual ~Foo();
	private:
		std::uint32_t* mData;

		RTTI_DECLARATIONS(Foo, RTTI)

		bool Equals(const AnonymousEngine::RTTI * rhs) const;
		std::string ToString() const override;
		void FromString(const std::string& str) override;
	};

	using namespace AnonymousEngine;
	CONCRETE_FACTORY_DECLARATIONS(RTTI, Foo);
}
