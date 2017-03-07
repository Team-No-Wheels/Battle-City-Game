#pragma once

#include "Attributed.h"

namespace UnitTestLibraryDesktop
{
	class AttributedFoo : public AnonymousEngine::Attributed
	{
	public:
		AttributedFoo();
		virtual ~AttributedFoo();

		AttributedFoo(const AttributedFoo& rhs);
		AttributedFoo(AttributedFoo&& rhs) noexcept;

		AttributedFoo& operator=(const AttributedFoo& rhs);
		AttributedFoo& operator=(AttributedFoo&& rhs) noexcept;
	private:
		std::int32_t mInt;
		float mFloat;

		ATTRIBUTED_DECLARATIONS()

		RTTI_DECLARATIONS(AttributedFoo, Attributed)
	};
}