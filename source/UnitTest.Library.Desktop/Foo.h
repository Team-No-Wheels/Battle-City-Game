#pragma once

#include "RTTI.h"

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

		std::uint32_t Data() const;

		virtual ~Foo();
	private:
		std::uint32_t* mData;

		RTTI_DECLARATIONS(Foo, RTTI)

		std::string ToString() const override;
		void FromString(const std::string& str) override;
	};
}
