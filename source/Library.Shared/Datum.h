#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "RTTI.h"

namespace AnonymousEngine
{
	class Scope;

	class Datum final
	{
	public:
		enum class DatumType
		{
			Unknown,
			Integer,
			Float,
			String,
			Vector,
			Matrix,
			Scope,
			RTTI,
			MaxTypes
		};

		/** Constructs a new vector and sets the type.
		 *  @param type Type of the datum to create. Defaults to Unknown
		 */
		explicit Datum(DatumType type = DatumType::Unknown);

		/** Copy constructor to construct a copy of vector
		 *  @param rhs The other datum to create copy from
		 */
		Datum(const Datum& rhs);

		/** Move constructor to construct a vector and move the data from the other
		 *  @param rhs The other datum to move data from
		 */
		Datum(Datum&& rhs) noexcept;

		/** Sets the type of the current datum
		 *  @param type The type to set for the current datum
		 */
		void SetType(DatumType type);

		/** Gets the current type of the datum
		 *  @return Returns the current datum type
		 */
		DatumType Type() const;

		/** Copy assignment operator to copy all the values from another datum
		 *  @param rhs The other datum to copy from
		 *  @return A new instance of datum which is a copy of the passed datum
		 */
		Datum& operator=(const Datum& rhs);
		/** Move assignment operator to move all the values from another datum
		 *  @param rhs The other datum to move from
		 *  @return A reference to the current datum which has the new data
		 */
		Datum& operator=(Datum&& rhs) noexcept;

		/** Assigns the given int value to the datum
		 *  @param data The data to assign
		 *  @return A reference to the current datum
		 */
		Datum& operator=(const std::int32_t& data);
		/** Assigns the given float value to the datum
		 *  @param data The data to assign
		 *  @return A reference to the current datum
		 */
		Datum& operator=(const float& data);
		/** Assigns the given string value to the datum
		 *  @param data The data to assign
		 *  @return A reference to the current datum
		 */
		Datum& operator=(const std::string& data);
		/** Assigns the given vec4 value to the datum
		 *  @param data The data to assign
		 *  @return A reference to the current datum
		 */
		Datum& operator=(const glm::vec4& data);
		/** Assigns the given mat4 value to the datum
		 *  @param data The data to assign
		 *  @return A reference to the current datum
		 */
		Datum& operator=(const glm::mat4& data);
		/** Assigns the given Scope value to the datum
		 *  @param data The data to assign
		 *  @return A reference to the current datum
		 */
		Datum& operator=(Scope& data);
		/** Assigns the given RTTI value to the datum
		 *  @param data The data to assign
		 *  @return A reference to the current datum
		 */
		Datum& operator=(RTTI* data);

		/** Assigns the given int value to the datum at the specified index.
		 *  Throws exception if index is out of range. index should be in the range [0, size)
		 *  @param data The data to assign
		 *  @param index The index to which the data is to be assigned.
		 *  @return A reference to the current datum
		 */
		void Set(const std::int32_t data, const std::uint32_t index = 0);
		/** Assigns the given float value to the datum at the specified index.
		 *  Throws exception if index is out of range. index should be in the range [0, size)
		 *  @param data The data to assign
		 *  @param index The index to which the data is to be assigned.
		 *  @return A reference to the current datum
		 */
		void Set(const float data, const std::uint32_t index = 0);
		/** Assigns the given string value to the datum at the specified index.
		 *  Throws exception if index is out of range. index should be in the range [0, size)
		 *  @param data The data to assign
		 *  @param index The index to which the data is to be assigned.
		 *  @return A reference to the current datum
		 */
		void Set(const std::string& data, const std::uint32_t index = 0);
		/** Assigns the given vec4 value to the datum at the specified index.
		 *  Throws exception if index is out of range. index should be in the range [0, size)
		 *  @param data The data to assign
		 *  @param index The index to which the data is to be assigned.
		 *  @return A reference to the current datum
		 */
		void Set(const glm::vec4& data, const std::uint32_t index = 0);
		/** Assigns the given mat4 value to the datum at the specified index.
		 *  Throws exception if index is out of range. index should be in the range [0, size)
		 *  @param data The data to assign
		 *  @param index The index to which the data is to be assigned.
		 *  @return A reference to the current datum
		 */
		void Set(const glm::mat4& data, const std::uint32_t index = 0);
		/** Assigns the given Scope value to the datum at the specified index.
		 *  Throws exception if index is out of range. index should be in the range [0, size)
		 *  @param data The data to assign
		 *  @param index The index to which the data is to be assigned.
		 *  @return A reference to the current datum
		 */
		void Set(Scope& data, const std::uint32_t index = 0);
		/** Assigns the given RTTI value to the datum at the specified index.
		 *  Throws exception if index is out of range. index should be in the range [0, size)
		 *  @param data The data to assign
		 *  @param index The index to which the data is to be assigned.
		 *  @return A reference to the current datum
		 */
		void Set(RTTI* data, const std::uint32_t index = 0);

		/** Get the data stored in the datum at the given index
		 *  @param index The index of the data to be retrieved
		 *  @return A reference to the data at the given index
		 */
		template<typename T>
		T& Get(const std::uint32_t index = 0);

		/** Get the data stored in the datum at the given index
		 *  @param index The index of the data to be retrieved
		 *  @return A constant reference to the data at the given index
		 */
		template<typename T>
		const T& Get(const std::uint32_t index = 0) const;

		/** Push an int value to the end of the datum
		 *  @param data The data item to pupsh to the back of the datum
		 *  @return A reference to the current data that is pushed
		 */
		void PushBack(const std::int32_t data);
		/** Push an float value to the end of the datum
		 *  @param data The data item to push to the back of the datum
		 *  @return A reference to the current data that is pushed
		 */
		void PushBack(const float data);
		/** Push an string value to the end of the datum
		 *  @param data The data item to push to the back of the datum
		 *  @return A reference to the current data that is pushed
		 */
		void PushBack(const std::string& data);
		/** Push an vec4 value to the end of the datum
		 *  @param data The data item to push to the back of the datum
		 *  @return A reference to the current data that is pushed
		 */
		void PushBack(const glm::vec4& data);
		/** Push an mat4 value to the end of the datum
		 *  @param data The data item to push to the back of the datum
		 *  @return A reference to the current data that is pushed
		 */
		void PushBack(const glm::mat4& data);
		/** Push a Scope value to the end of the datum
		 *  @param data The data item to push to the back of the datum
		 *  @return A reference to the current data that is pushed
		 */
		void PushBack(Scope& data);
		/** Push an RTTI value to the end of the datum
		 *  @param data The data item to push to the back of the datum
		 *  @return A reference to the current data that is pushed
		 */
		void PushBack(RTTI* data);

		/** Remove an item from the back of the vector
		 *  @return True if an item was popped, False otherwise
		 */
		bool PopBack();

		/** Check if the current datum is equal to another datum.
		 *  @param data The datum value to compare to
		 */
		bool operator==(const Datum& data) const;
		/** Check if the current datum and an int value is equal. If the datum is not a scalar, the result will be false
		 *  @param data The int value to compare to
		 */
		bool operator==(const std::int32_t data) const;
		/** Check if the current datum and an float value is equal. If the datum is not a scalar, the result will be false
		 *  @param data The float value to compare to
		 */
		bool operator==(const float data) const;
		/** Check if the current datum and an string value is equal. If the datum is not a scalar, the result will be false
		 *  @param data The string value to compare to
		 */
		bool operator==(const std::string& data) const;
		/** Check if the current datum and an vec4 value is equal. If the datum is not a scalar, the result will be false
		 *  @param data The string value to compare to
		 */
		bool operator==(const glm::vec4& data) const;
		/** Check if the current datum and an mat4 value is equal. If the datum is not a scalar, the result will be false
		 *  @param data The string value to compare to
		 */
		bool operator==(const glm::mat4& data) const;
		/** Check if the current datum and a Scope value is equal. If the datum is not a scalar, the result will be false
		 *  @param data The Scope value to compare to
		 */
		bool operator==(const Scope& data) const;
		/** Check if the current datum and an RTTI value is equal. If the datum is not a scalar, the result will be false
		 *  @param data The RTTI value to compare to
		 */
		bool operator==(const RTTI* data) const;

		/** Check if the current datum is not equal to another datum.
		 *  @param data The datum value to compare to
		 */
		bool operator!=(const Datum& data) const;
		/** Check if the current datum and an int value is not equal. If the datum is not a scalar, the result will be false
		 *  @param data The int value to compare to
		 */
		bool operator!=(const std::int32_t data) const;
		/** Check if the current datum and an float value is not equal. If the datum is not a scalar, the result will be false
		 *  @param data The float value to compare to
		 */
		bool operator!=(const float data) const;
		/** Check if the current datum and an string value is not equal. If the datum is not a scalar, the result will be false
		 *  @param data The string value to compare to
		 */
		bool operator!=(const std::string& data) const;
		/** Check if the current datum and an vec4 value is not equal. If the datum is not a scalar, the result will be false
		 *  @param data The string value to compare to
		 */
		bool operator!=(const glm::vec4& data) const;
		/** Check if the current datum and an mat4 value is not equal. If the datum is not a scalar, the result will be false
		 *  @param data The string value to compare to
		 */
		bool operator!=(const glm::mat4& data) const;
		/** Check if the current datum and a Scope value is not equal. If the datum is not a scalar, the result will be false
		 *  @param data The Scope value to compare to
		 */
		bool operator!=(const Scope& data) const;
		/** Check if the current datum and an RTTI value is not equal. If the datum is not a scalar, the result will be false
		 *  @param data The RTTI value to compare to
		 */
		bool operator!=(const RTTI* data) const;

		/** Remove a scope from the current datum
		 *  @param scope The scope to be removed
		 *  @return A boolean indicating whether the element was removed or not
		 */
		bool Remove(Scope& scope);

		/** Set this datum to use an external int array
		 *  @param data The pointer to the external data
		 *  @param size The number of elements in the external data array
		 */
		void SetStorage(std::int32_t* data, std::uint32_t size);
		/** Set this datum to use an external float array
		 *  @param data The pointer to the external data
		 *  @param size The number of elements in the external data array
		 */
		void SetStorage(float* data, std::uint32_t size);
		/** Set this datum to use an external string array
		 *  @param data The pointer to the external data
		 *  @param size The number of elements in the external data array
		 */
		void SetStorage(std::string* data, std::uint32_t size);
		/** Set this datum to use an external vec4 array
		 *  @param data The pointer to the external data
		 *  @param size The number of elements in the external data array
		 */
		void SetStorage(glm::vec4* data, std::uint32_t size);
		/** Set this datum to use an external mat4 array
		 *  @param data The pointer to the external data
		 *  @param size The number of elements in the external data array
		 */
		void SetStorage(glm::mat4* data, std::uint32_t size);
		/** Set this datum to use an external Scope pointer array
		 *  @param data The pointer to the external data
		 *  @param size The number of elements in the external data array
		 */
		void SetStorage(Scope** data, std::uint32_t size);
		/** Set this datum to use an external RTTI pointer array
		 *  @param data The pointer to the external data
		 *  @param size The number of elements in the external data array
		 */
		void SetStorage(RTTI** data, std::uint32_t size);

		/** Parse the string to the current type and set the datum to the parsed data. Throws exception if type is not set
		 *  @param stringData The string to parse the data from
		 *  @param index The index in the current datum to which the parsed value is to be assigned. Defaults to zero
		 */
		void SetFromString(const std::string& stringData, std::uint32_t index = 0);
		/** Convert the current datum value at the given index to a string
		 *  @param index The index of the data to be converted to string
		 *  @return The string representation of the datum
		 */
		std::string ToString(std::uint32_t index = 0) const;

		/** Change the size of the current datum to the new size.
		 *  Expand the datum with default initialized values if the size is larger than the current
		 *  Truncate if the new size is less
		 *  @param newSize The new size of the datum
		 */
		void Resize(std::uint32_t newSize);

		/** Get the total number of items in the vector
		 *  @return The number of items in the vector
		 */
		std::uint32_t Size() const;

		/** Clear all the items from the vector
		 */
		void Clear();

		/** Destroy the vector object, freeing all allocated resources
		 */
		~Datum();

		union DatumValue
		{
			std::int32_t* intValue;
			float* floatValue;
			glm::mat4* matValue;
			glm::vec4* vecValue;
			std::string* strValue;
			Scope** scopeValue;
			RTTI** rttiPtrValue;
			void* voidPtr;
		};

	private:
		DatumType mType;
		DatumValue mData;
		std::uint32_t mSize;
		bool mIsExternal;

		static const std::uint32_t TypeSizes[static_cast<uint32_t>(DatumType::MaxTypes)];
		static const std::function<void(DatumValue&, std::uint32_t)> DefaultConstructors[static_cast<uint32_t>(DatumType::MaxTypes)];
		static const std::function<void(DatumValue&, std::uint32_t)> Destructors[static_cast<uint32_t>(DatumType::MaxTypes)];
		static const std::function<bool(const DatumValue&, const DatumValue&, std::uint32_t)> Comparators[static_cast<uint32_t>(DatumType::MaxTypes)];
		static const std::function<void(DatumValue&, const DatumValue&, std::uint32_t)> Cloners[static_cast<uint32_t>(DatumType::MaxTypes)];
		static const std::function<void(const std::string&, DatumValue&, std::uint32_t)> Deserializers[static_cast<uint32_t>(DatumType::MaxTypes)];
		static const std::function<std::string(const DatumValue&, std::uint32_t)> Serializers[static_cast<uint32_t>(DatumType::MaxTypes)];

		// Checks if the passed type can be assigned to current datum. Throw exception otherwise
		inline void ValidateType(DatumType type) const;

		// Check if the passed in index is within range
		inline void ValidateIndex(std::uint32_t index) const;

		// Check if current datum is external and throw exception
		inline void RaiseExceptionOnExternal() const;

		// Sets the type and resizes if not external type
		inline void InitializeScalar(DatumType type);

		// Copies data from one datum to another. Used in copy constructor and copy assignment operator
		inline void Copy(const Datum& rhs);

		// Moves data from one datum to another. Used in move constructor and move assignment operator
		inline void Move(Datum& rhs);

		// Common method to set external storage based on type
		inline void SetExternalStorage(void* externalData, std::uint32_t size, DatumType type);
	};
}

#include "Datum.inl"
