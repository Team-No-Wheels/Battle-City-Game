#pragma once

namespace AnonymousEngine
{
	template<typename T>
	T& Datum::Get(const std::uint32_t)
	{
		return *reinterpret_cast<T*>(mData.voidPtr);
	}

	template <>
	inline std::int32_t& Datum::Get<std::int32_t>(const std::uint32_t index)
	{
		ValidateIndex(index);
		return mData.intValue[index];
	}

	template <>
	inline float& Datum::Get<float>(const std::uint32_t index)
	{
		ValidateIndex(index);
		return mData.floatValue[index];
	}

	template <>
	inline std::string& Datum::Get<std::string>(const std::uint32_t index)
	{
		ValidateIndex(index);
		return mData.strValue[index];
	}

	template <>
	inline glm::mat4& Datum::Get<glm::mat4>(const std::uint32_t index)
	{
		ValidateIndex(index);
		return mData.matValue[index];
	}

	template <>
	inline glm::vec4& Datum::Get<glm::vec4>(const std::uint32_t index)
	{
		ValidateIndex(index);
		return mData.vecValue[index];
	}

	template <>
	inline RTTI*& Datum::Get<RTTI*>(const std::uint32_t index)
	{
		ValidateIndex(index);
		return mData.rttiPtrValue[index];
	}

	template<typename T>
	const T& Datum::Get(const std::uint32_t) const
	{
		return const_cast<const Datum*>(this)->Get<T>();
	}

	template <>
	inline const std::int32_t& Datum::Get<std::int32_t>(const std::uint32_t index) const
	{
		return const_cast<const Datum*>(this)->Get<std::int32_t>(index);
	}

	template <>
	inline const float& Datum::Get<float>(const std::uint32_t index) const
	{
		return const_cast<const Datum*>(this)->Get<float>(index);
	}

	template <>
	inline const std::string& Datum::Get<std::string>(const std::uint32_t index) const
	{
		return const_cast<const Datum*>(this)->Get<std::string>(index);
	}

	template <>
	inline const glm::mat4& Datum::Get<glm::mat4>(const std::uint32_t index) const
	{
		return const_cast<const Datum*>(this)->Get<glm::mat4>(index);
	}

	template <>
	inline const glm::vec4& Datum::Get<glm::vec4>(const std::uint32_t index) const
	{
		return const_cast<const Datum*>(this)->Get<glm::vec4>(index);
	}

	template <>
	inline RTTI* const& Datum::Get<RTTI*>(const std::uint32_t index) const
	{
		return const_cast<const Datum*>(this)->Get<RTTI*>(index);
	}
}
