#pragma once

#include "Attributed.h"

namespace UnitTestLibraryDesktop
{
	const std::uint32_t ArraySize = 5;

	class AttributedFoo : public AnonymousEngine::Attributed
	{
	public:
		AttributedFoo();
		virtual ~AttributedFoo() = default;

		AttributedFoo(const AttributedFoo& rhs);
		AttributedFoo(AttributedFoo&& rhs) noexcept;

		AttributedFoo& operator=(const AttributedFoo& rhs);
		AttributedFoo& operator=(AttributedFoo&& rhs) noexcept;

		bool operator==(const AttributedFoo& rhs) const;
		bool operator!=(const AttributedFoo& rhs) const;

		std::int32_t mInt;
		float mFloat;
		std::string mString;
		glm::vec4 mVec4;
		glm::mat4 mMat4;
		Scope* mNestedScope;
		RTTI* mRtti;

	private:
		std::int32_t mIntArray[ArraySize];
		std::int32_t mFloatArray[ArraySize];
		std::int32_t mStringArray[ArraySize];
		std::int32_t mVec4Array[ArraySize];
		std::int32_t mMat4Array[ArraySize];
		std::int32_t mRTTIArray[ArraySize];

		void Copy(const AttributedFoo& rhs);
		void Move(AttributedFoo& rhs);
		void FixupPrescribedAttributes();

		ATTRIBUTED_DECLARATIONS(AttributedFoo)

		RTTI_DECLARATIONS(AttributedFoo, AnonymousEngine::Attributed)
	};
}
