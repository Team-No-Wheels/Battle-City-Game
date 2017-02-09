#pragma once

namespace AnonymousEngine
{
	/** This class is used by containers like hashmap to compare two items
	 *  This default implementation simply uses the equality operator on the objects
	 *  Specializations can be added for other types as required
	 */
	template <typename T>
	class DefaultCompare
	{
	public:
		/** Checks if lhs is logically equivalent to rhs
		 *  @param lhs The left hand side of the equality
		 *  @param rhs The right hand side of the equality
		 *  @return Boolean indicating whether left hand side is logically equivalent to right hand side
		 */
		bool operator()(const T& lhs, const T& rhs) const;
	};

	/** Specialization for const char* comparison
	*/
	template <>
	class DefaultCompare<const char*>
	{
	public:
		/** Checks if lhs is logically equivalent to rhs
		*  @param lhs The left hand side of the equality
		*  @param rhs The right hand side of the equality
		*  @return Boolean indicating whether left hand side is logically equivalent to right hand side
		*/
		bool operator()(const char* lhs, const char* rhs) const;
	};
}

#include "Compare.inl"
