#include "Pch.h"
#include "AttributedFoo.h"

namespace UnitTestLibraryDesktop
{
	ATTRIBUTED_DEFINITIONS(AttributedFoo)

	RTTI_DEFINITIONS(AttributedFoo)

	AttributedFoo::AttributedFoo() :
		mInt(0), mFloat(0.0f), mNestedScope(new Scope())
	{
		AddExternalAttribute("mInt", &mInt, 1);
		AddExternalAttribute("mFloat", &mFloat, 1);
		AddExternalAttribute("mString", &mString, 1);
		AddExternalAttribute("mVec4", &mVec4, 1);
		AddExternalAttribute("mMat4", &mMat4, 1);
		AddNestedScope("mNestedScope", *mNestedScope);

		AddExternalAttribute("mIntArray", mIntArray, ArraySize);
		AddExternalAttribute("mFloatArray", mFloatArray, ArraySize);
		AddExternalAttribute("mStringArray", mStringArray, ArraySize);
		AddExternalAttribute("mVec4Array", mVec4Array, ArraySize);
		AddExternalAttribute("mMat4Array", mMat4Array, ArraySize);
		AddExternalAttribute("mRTTIArray", mRTTIArray, ArraySize);
		ValidateAllPrescribedAttributesAreAdded();
	}

	AttributedFoo::AttributedFoo(const AttributedFoo& rhs) :
		Attributed(rhs)
	{
		Copy(rhs);
	}

	AttributedFoo::AttributedFoo(AttributedFoo&& rhs) noexcept :
		Attributed(std::move(rhs)), mInt(rhs.mInt), mFloat(rhs.mFloat), mNestedScope(nullptr)
	{
		Move(rhs);
	}

	AttributedFoo& AttributedFoo::operator=(const AttributedFoo& rhs)
	{
		if (this != &rhs)
		{
			Attributed::operator=(rhs);
			Copy(rhs);
		}
		return *this;
	}

	AttributedFoo& AttributedFoo::operator=(AttributedFoo&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Attributed::operator=(std::move(rhs));
			Move(rhs);
		}
		return *this;
	}

	bool AttributedFoo::operator==(const AttributedFoo& rhs) const
	{
		return (Attributed::operator==(rhs));
	}

	bool AttributedFoo::operator!=(const AttributedFoo& rhs) const
	{
		return !(*this == rhs);
	}

	void AttributedFoo::Copy(const AttributedFoo& rhs)
	{
		mInt = rhs.mInt;
		mFloat = rhs.mFloat;
		mString = rhs.mString;
		mVec4 = rhs.mVec4;
		mMat4 = rhs.mMat4;
		memcpy(mIntArray, rhs.mIntArray, sizeof(std::int32_t) * ArraySize);
		memcpy(mFloatArray, rhs.mFloatArray, sizeof(float) * ArraySize);
		for(std::uint32_t index = 0; index < ArraySize; ++index)
		{
			mStringArray[index] = rhs.mStringArray[index];
			mVec4Array[index] = rhs.mVec4Array[index];
			mMat4Array[index] = rhs.mMat4Array[index];
		}
		memcpy(mRTTIArray, rhs.mRTTIArray, sizeof(RTTI*) * ArraySize);
		FixupPrescribedAttributes();
	}

	void AttributedFoo::Move(AttributedFoo& rhs)
	{
		mInt = rhs.mInt;
		mFloat = rhs.mFloat;
		mString = std::move(rhs.mString);
		mVec4 = std::move(rhs.mVec4);
		mMat4 = std::move(rhs.mMat4);
		memmove(mIntArray, rhs.mIntArray, sizeof(std::int32_t) * ArraySize);
		memmove(mFloatArray, rhs.mFloatArray, sizeof(float) * ArraySize);
		for (std::uint32_t index = 0; index < ArraySize; ++index)
		{
			mStringArray[index] = std::move(rhs.mStringArray[index]);
			mVec4Array[index] = std::move(rhs.mVec4Array[index]);
			mMat4Array[index] = std::move(rhs.mMat4Array[index]);
		}
		memmove(mRTTIArray, rhs.mRTTIArray, sizeof(RTTI*) * ArraySize);
		FixupPrescribedAttributes();
	}

	void AttributedFoo::FixupPrescribedAttributes()
	{
		(*this)["this"].Set(this);
		(*this)["mInt"].SetStorage(&mInt, 1);
		(*this)["mFloat"].SetStorage(&mFloat, 1);
		(*this)["mString"].SetStorage(&mString, 1);
		(*this)["mVec4"].SetStorage(&mVec4, 1);
		(*this)["mMat4"].SetStorage(&mMat4, 1);
		mNestedScope = &(*this)["mNestedScope"].Get<Scope>();
		(*this)["mIntArray"].SetStorage(mIntArray, ArraySize);
		(*this)["mFloatArray"].SetStorage(mFloatArray, ArraySize);
		(*this)["mStringArray"].SetStorage(mStringArray, ArraySize);
		(*this)["mVec4Array"].SetStorage(mVec4Array, ArraySize);
		(*this)["mMat4Array"].SetStorage(mMat4Array, ArraySize);
		(*this)["mRTTIArray"].SetStorage(mRTTIArray, ArraySize);
	}

	void AttributedFoo::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		prescribedAttributeNames.PushBack("mInt");
		prescribedAttributeNames.PushBack("mFloat");
		prescribedAttributeNames.PushBack("mString");
		prescribedAttributeNames.PushBack("mVec4");
		prescribedAttributeNames.PushBack("mMat4");
		prescribedAttributeNames.PushBack("mNestedScope");
		prescribedAttributeNames.PushBack("mIntArray");
		prescribedAttributeNames.PushBack("mFloatArray");
		prescribedAttributeNames.PushBack("mStringArray");
		prescribedAttributeNames.PushBack("mVec4Array");
		prescribedAttributeNames.PushBack("mMat4Array");
		prescribedAttributeNames.PushBack("mRTTIArray");
	}
}
