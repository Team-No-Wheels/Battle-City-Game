#pragma once

#include "Attributed.h"

namespace UnitTestLibraryDesktop
{
	class AttributedFoo : public AnonymousEngine::Attributed
	{
	public:
		AttributedFoo();
		virtual ~AttributedFoo();

	private:
		std::int32_t   mInt;
		float mFloat;

		ATTRIBUTED_DECLARATIONS()

		RTTI_DECLARATIONS(AttributedFoo, Attributed)
	};
}