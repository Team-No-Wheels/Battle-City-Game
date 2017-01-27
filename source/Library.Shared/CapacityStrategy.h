#pragma once

#include <cstdint>

namespace AnonymousEngine
{
	/** Interface for implementing custom capacity increment strategy for the Vector container
	 */
	class CapacityStrategy
	{
	public:
		/** Construct a capacity strategy with default initialization
		 */
		CapacityStrategy() = default;
		/** Clear any allocated resources
		*/
		virtual ~CapacityStrategy() = default;
		/** Provide a capacity increment value given the current size and current capacity of the vector
		 *  @param size The current size of the vector
		 *  @param capacity The current capacity of the vector
		 *  @return The increment by which capacity should be incremented
		 */
		virtual std::uint32_t operator()(std::uint32_t size, std::uint32_t capacity) const = 0;
	};
}
