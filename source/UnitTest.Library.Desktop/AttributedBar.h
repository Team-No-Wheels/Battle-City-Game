#pragma once

#include "AttributedFoo.h"

namespace UnitTestLibraryDesktop
{
	class AttributedBar : public AttributedFoo
	{
	public:
		enum class TestScenario
		{
			Success,
			ValidateAttributeFail,
			ValidateAllAttributesFail
		};

		explicit AttributedBar(TestScenario scenario = TestScenario::Success);
		virtual ~AttributedBar() = default;

		AttributedBar(const AttributedBar& rhs);
		AttributedBar(AttributedBar&& rhs) noexcept;

		AttributedBar& operator=(const AttributedBar& rhs);
		AttributedBar& operator=(AttributedBar&& rhs) noexcept;

		bool operator==(const AttributedBar& rhs) const;
		bool operator!=(const AttributedBar& rhs) const;

		std::int32_t mIntBar;
		float mFloatBar;
		std::string mStringBar;
		glm::vec4 mVec4Bar;
		glm::mat4 mMat4Bar;
		Scope* mNestedScopeBar;

	private:
		void Copy(const AttributedBar& rhs);
		void Move(AttributedBar& rhs);
		void FixupPrescribedAttributes();

		ATTRIBUTED_DECLARATIONS(AttributedBar, AttributedFoo)
	};
}
