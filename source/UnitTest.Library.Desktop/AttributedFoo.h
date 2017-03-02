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
		int   mInt;
		float mFloat;

		ATTRIBUTED_DECLARATIONS()

		RTTI_DECLARATIONS(AttributedFoo, Attributed)
	};
}