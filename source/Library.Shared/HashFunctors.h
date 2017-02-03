#pragma once

#include <cstdint>
#include <string>

namespace AnonymousEngine
{
	class HashFunctions
	{
	public:
		static std::uint32_t SuperFastHash(const std::int8_t* data, std::uint32_t length);
	};

	template <typename T>
	class DefaultHashFunctor
	{
	public:
		std::uint32_t operator()(const T& data) const;
	};

	template <>
	class DefaultHashFunctor<char*>
	{
	public:
		std::uint32_t operator()(const char*& data) const;
	};

	template <>
	class DefaultHashFunctor<const char*>
	{
	public:
		std::uint32_t operator()(const char*& data) const;
	};

	template <>
	class DefaultHashFunctor<std::string>
	{
	public:
		std::uint32_t operator()(const std::string& data) const;
	};

	template <>
	class DefaultHashFunctor<const std::string>
	{
	public:
		std::uint32_t operator()(const std::string& data) const;
	};
}

#include "HashFunctors.inl"
