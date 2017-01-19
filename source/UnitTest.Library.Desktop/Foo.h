#pragma once

namespace UnitTestLibraryDesktop
{
	class Foo
	{
	public:
		Foo();
		Foo(std::uint32_t value);
		Foo(const Foo& rhs);
		Foo& operator=(const Foo& rhs);
		bool operator==(const Foo& rhs) const;

		std::uint32_t Data() const;

		~Foo();
	private:
		std::uint32_t* mData;
	};
}
