#pragma once

#include "AttributedFoo.h"

namespace UnitTestLibraryDesktop
{
	class AttributedBar : public AttributedFoo
	{
	public:
		AttributedBar();
		virtual ~AttributedBar() = default;

		AttributedBar(const AttributedBar& rhs);
		AttributedBar(AttributedBar&& rhs) noexcept;

		AttributedBar& operator=(const AttributedBar& rhs);
		AttributedBar& operator=(AttributedBar&& rhs) noexcept;
	private:
		std::int32_t mInt;
		float mFloat;
		std::string mString;
		glm::vec4 mVec4;
		glm::mat4 mMat4;
		Scope* mNestedScope;

		void Copy(const AttributedBar& rhs);
		void Move(AttributedBar& rhs);
		void FixupPrescribedAttributes();

		ATTRIBUTED_DECLARATIONS()

		RTTI_DECLARATIONS(AttributedBar, AttributedFoo)
	};
}
