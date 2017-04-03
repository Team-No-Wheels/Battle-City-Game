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
		AnonymousEngine::Datum* mDatum;
		RTTI* mRtti;

	private:
		std::int32_t mIntArray[ArraySize];
		float mFloatArray[ArraySize];
		std::string mStringArray[ArraySize];
		glm::vec4 mVec4Array[ArraySize];
		glm::mat4 mMat4Array[ArraySize];
		RTTI* mRTTIArray[ArraySize];

		void Copy(const AttributedFoo& rhs);
		void Move(AttributedFoo& rhs);
		void FixupPrescribedAttributes();

		ATTRIBUTED_DECLARATIONS(AttributedFoo, AnonymousEngine::Attributed)
	};
}
