#pragma once

#include <cstdint>
#include <string>

namespace AnonymousEngine
{
	/** This class contains hash functions that can be used to define HashFunctors
	 */
	class HashFunctions
	{
	public:
		/** Calculate hash given an array of bytes and length of the array
		 *  @param data The byte array pointer
		 *  @param length The length of the byte array
		 *  @return The hash value for the given data
		 */
		static std::uint32_t SuperFastHash(const std::int8_t* data, std::uint32_t length);
	};

	/** The template class for DefaultHashFunctor
	 */
	template <typename T>
	class DefaultHashFunctor
	{
	public:
		/** This function returns the hash value for a given data
		 *  @param data The data for which hash has to be calculated
		 *  @return The calculated hash value
		 */
		std::uint32_t operator()(const T& data) const;
	};

	/** The template specialization of DefaultHashFunctor for char*
	*/
	template <>
	class DefaultHashFunctor<char*>
	{
	public:
		/** This function returns the hash value for a given data
		*  @param data The data for which hash has to be calculated
		*  @return The calculated hash value
		*/
		std::uint32_t operator()(const char* data) const;
	};

	/** The template specialization of DefaultHashFunctor for const char*
	*/
	template <>
	class DefaultHashFunctor<const char*>
	{
	public:
		/** This function returns the hash value for a given data
		*  @param data The data for which hash has to be calculated
		*  @return The calculated hash value
		*/
		std::uint32_t operator()(const char* data) const;
	};

	/** The template specialization of DefaultHashFunctor for std::string
	*/
	template <>
	class DefaultHashFunctor<std::string>
	{
	public:
		/** This function returns the hash value for a given data
		*  @param data The data for which hash has to be calculated
		*  @return The calculated hash value
		*/
		std::uint32_t operator()(const std::string& data) const;
	};

	/** The template specialization of DefaultHashFunctor for const std::string
	*/
	template <>
	class DefaultHashFunctor<const std::string>
	{
	public:
		/** This function returns the hash value for a given data
		*  @param data The data for which hash has to be calculated
		*  @return The calculated hash value
		*/
		std::uint32_t operator()(const std::string& data) const;
	};
}

#include "HashFunctors.inl"
