#pragma once

namespace UnitTestLibraryDesktop
{
	class Bar
	{
	public:
		Bar();
		Bar(std::uint32_t value);
		Bar(const Bar& rhs);
		Bar& operator=(const Bar& rhs);
		bool operator==(const Bar& rhs) const;
		bool operator!=(const Bar& rhs) const;

		std::uint32_t Data() const;

		virtual ~Bar();
	private:
		std::uint32_t* mData;
	};
}
