#pragma once

#include <cstdint>
#include <string>
#include "RTTI.h"

namespace AnonymousEngine
{
	class Datum final
	{
	public:
		enum class DatumType
		{
			Unknown,
			Integer,
			Float,
			Vector,
			Matrix,
			String,
			RTTI
		};

		/** Constructs a new vector and sets the type.
		 *  @param type Type of the datum to create. Defaults to Unknown
		*/
		Datum(DatumType type = DatumType::Unknown);

		/** Copy constructor to construct a copy of vector
		 *  @param datum The other list to create copy from
		*/
		Datum(const Datum& datum);

		/** Sets the type of the current datum
		  * @param type The type to set for the current datum
		 */
		void SetType(DatumType type);

		/** Gets the current type of the datum
		  * @return Returns the current datum type
		 */
		DatumType Type();

		/** Assignment operator to copy all the values from another vector
		 * @param datum The other vector to copy from
		 * @return A new instance of vector which is a copy of the passed vector
		*/
		Datum& operator=(const Datum& datum);
		/** Assigns the given int value to the datum
		 * @param data The data to assign
		 * @return A reference to the current datum
		*/
		Datum& operator=(const std::int32_t data);
		/** Assigns the given float value to the datum
		 * @param data The data to assign
		 * @return A reference to the current datum
		*/
		Datum& operator=(const float data);
		/** Assigns the given string value to the datum
		 * @param data The data to assign
		 * @return A reference to the current datum
		*/
		Datum& operator=(const std::string& data);
		/** Assigns the given RTTI value to the datum
		 * @param data The data to assign
		 * @return A reference to the current datum
		*/
		Datum& operator=(const RTTI* data);

		/** Assigns the given int value to the datum at the specified index.
		 * Throws exception if index is out of range. index should be in the range [0, size)
		 * @param data The data to assign
		 * @param index The index to which the data is to be assigned.
		 * @return A reference to the current datum
		*/
		void Set(const std::int32_t data, const std::uint32_t index = 0);
		/** Assigns the given float value to the datum at the specified index.
		 * Throws exception if index is out of range. index should be in the range [0, size)
		 * @param data The data to assign
		 * @param index The index to which the data is to be assigned.
		 * @return A reference to the current datum
		*/
		void Set(const float data, const std::uint32_t index = 0);
		/** Assigns the given string value to the datum at the specified index.
		 * Throws exception if index is out of range. index should be in the range [0, size)
		 * @param data The data to assign
		 * @param index The index to which the data is to be assigned.
		 * @return A reference to the current datum
		*/
		void Set(const std::string& data, const std::uint32_t index = 0);
		/** Assigns the given RTTI value to the datum at the specified index.
		 * Throws exception if index is out of range. index should be in the range [0, size)
		 * @param data The data to assign
		 * @param index The index to which the data is to be assigned.
		 * @return A reference to the current datum
		*/
		void Set(const RTTI* data, const std::uint32_t index = 0);

		//template <typename T>
		//void Get<T>(const std::uint32_t index = 0);

		/** Push an int value to the end of the datum
		 * @param data The data item to push to the back of the datum
		 * @return A reference to the current data that is pushed
		*/
		void PushBack(const std::int32_t data);
		/** Push an float value to the end of the datum
		 * @param data The data item to push to the back of the datum
		 * @return A reference to the current data that is pushed
		*/
		void PushBack(const float data);
		/** Push an string value to the end of the datum
		 * @param data The data item to push to the back of the datum
		 * @return A reference to the current data that is pushed
		*/
		void PushBack(const std::string& data);
		/** Push an RTTI value to the end of the datum
		 * @param data The data item to push to the back of the datum
		 * @return A reference to the current data that is pushed
		*/
		void PushBack(const RTTI* data);

		/** Remove an item from the back of the vector
		 *  @return True if an item was popped, False otherwise
		*/
		bool PopBack();

		/** Check if the current datum and an int value is equal. If the datum is not a scalar, the result will be false
		 * @param data The int value to compare to
		*/
		bool operator==(const std::int32_t data);
		/** Check if the current datum and an float value is equal. If the datum is not a scalar, the result will be false
		 * @param data The float value to compare to
		*/
		bool operator==(const float data);
		/** Check if the current datum and an string value is equal. If the datum is not a scalar, the result will be false
		 * @param data The string value to compare to
		*/
		bool operator==(const std::string& data);
		/** Check if the current datum and an RTTI value is equal. If the datum is not a scalar, the result will be false
		 * @param data The RTTI value to compare to
		*/
		bool operator==(const RTTI* data);

		/** Check if the current datum and an int value is not equal. If the datum is not a scalar, the result will be false
		 * @param data The int value to compare to
		*/
		bool operator!=(const std::int32_t data);
		/** Check if the current datum and an float value is not equal. If the datum is not a scalar, the result will be false
		 * @param data The float value to compare to
		*/
		bool operator!=(const float data);
		/** Check if the current datum and an string value is not equal. If the datum is not a scalar, the result will be false
		 * @param data The string value to compare to
		*/
		bool operator!=(const std::string& data);
		/** Check if the current datum and an RTTI value is not equal. If the datum is not a scalar, the result will be false
		 * @param data The RTTI value to compare to
		*/
		bool operator!=(const RTTI* data);

		/** Set this datum to use an external int array
		 * @param data The pointer to the external data
		 * @param size The number of elements in the external data array
		 */
		void SetStorage(std::int32_t* data, std::uint32_t size);
		/** Set this datum to use an external float array
		 * @param data The pointer to the external data
		 * @param size The number of elements in the external data array
		 */
		void SetStorage(float* data, std::uint32_t size);
		/** Set this datum to use an external string array
		 * @param data The pointer to the external data
		 * @param size The number of elements in the external data array
		 */
		void SetStorage(std::string* data, std::uint32_t size);
		/** Set this datum to use an external RTTI pointer array
		 * @param data The pointer to the external data
		 * @param size The number of elements in the external data array
		 */
		void SetStorage(RTTI** data, std::uint32_t size);

		/** Parse the string to the current type and set the datum to the parsed data. Throws exception if type is not set
		 * @param stringData The string to parse the data from
		 * @param index The index in the current datum to which the parsed value is to be assigned. Defaults to zero
		 */
		void SetFromString(const std::string& stringData, std::uint32_t index = 0);
		/** Convert the current datum value to a string
		 * @return The string representation of the datum
		 */
		std::string ToString();

		/** Change the size of the current datum to the new size.
		 *  Expand the datum with default initialized values if the size is larger than the current
		 *  Truncate if the new size is less
		 *  @param newSize The new size of the datum
		 */
		void Resize(std::uint32_t newSize);

		/** Get the total number of items in the vector
		 * @return The number of items in the vector
		*/
		std::uint32_t Size() const;

		/** Reserves enough memory to allocate the given number of items or existing capacity whichever is the maximum
		 * @param capacity The capacity in number of elements to reserve
		*/
		void Reserve(std::uint32_t capacity);

		/** Clear all the items from the vector
		*/
		void Clear();

		/** Destroy the vector object, freeing all allocated resources
		*/
		~Datum();
	private:
		union DatumValue
		{
			std::int32_t* intValue;
			float* floatValue;
			RTTI* rttiPtrValue;
			void* voidPtr;
		};

		DatumType mType;
		DatumValue mData;
		std::uint32_t mSize;
		std::uint32_t mCapacity;

		// copies data from one list to another. Used in copy constructor and assignment operator
		void Copy(const Datum& rhs);
	};
}
