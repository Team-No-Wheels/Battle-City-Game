#pragma once

#include <cstdint>
#include "CapacityStrategy.h"

namespace AnonymousEngine
{
	template <typename T>
	class Vector
	{
	public:
		class Iterator
		{
		public:
			/** Default constructor. Initializes an empty iterator which doesn't point to anything
			*/
			Iterator();

			/** Initializes an iterator from the values of another iterator
			*   @param rhs The iterator from which values are to be copied
			*/
			Iterator(const Iterator& rhs) = default;

			/** Copies the values from another iterator to this iterator
			*  @param rhs The iterator from which the values are to be copied
			*/
			Iterator& operator=(const Iterator& rhs) = default;

			/** Advances the iterator to the next location in the container
			*  @returns The current iterator which now points to the next location in the container
			*/
			Iterator& operator++();

			/** Give an iterator which points to the current location in the container and advances the iterator to the next
			*  location in the container
			*  @param unused This paremeter is not used. It is used by C++ compiler for identifying post increment from pre increment
			*/
			Iterator operator++(int unused);

			/** Get the current value in the container that the iterator points to
			*   @returns A constant reference to the value that the iterator points to
			*/
			T& operator*() const;

			/** Check if two iterators are equal
			*   @returns A boolean indicating whether the two iterators are equal
			*/
			bool operator==(const Iterator& rhs) const;

			/** Check if two iterators are not equal
			*   @returns A boolean indicating whether the two iterators are not equal
			*/
			bool operator!=(const Iterator& rhs) const;
		private:
			std::uint32_t mIndex;
			Vector<T>* mOwner;

			Iterator(const std::uint32_t index, Vector<T>* owner);
			friend Vector<T>;
		};

		/** Constructs a new vector
		*/
		Vector();

		/** Copy constructor to construct a copy of vector
		*	@param vector The other list to create copy from
		*/
		Vector(const Vector<T>& vector);

		/** Assignment operator to copy all the values from another vector
		*	@param vector The other vector to copy from
		*	@return A new instance of vector which is a copy of the passed vector
		*/
		Vector<T>& operator=(const Vector<T>& vector);

		/** Push an item to the back of the vector
		*	@param data The data item to push to the back of the vector
		*	@return An iterator to the current data that is pushed
		*/
		void PushBack(const T& data);

		/** Remove an item from the back of the vector
		*/
		bool PopBack();

		/** Get the item at the front of the vector
		*	@return The item at the front of the vector
		*/
		T& Front();

		/** Get the item at the front of the vector. Constant version
		*	@return The item at the front of the vector
		*/
		const T& Front() const;

		/** Get the item at the back of the vector
		*	@return The item at the front of the vector
		*/
		T& Back();

		/** Get the item at the back of the vector. Constant version
		*	@return The item at the front of the vector
		*/
		const T& Back() const;

		/** Get the total number of items in the vector
		*	@return The number of items in the vector
		*/
		std::uint32_t Size() const;

		/** Get the total number of items that can be stored in the vector without reallocating memory
		*	@return The total number of items that can be stored in the vector without reallocating memory
		*/
		std::uint32_t Capacity() const;

		/** Check whether the vector is empty or not
		*	@return Whether the vector is empty
		*/
		bool IsEmpty() const;

		/** Get the item at the given index
		*  @param index The index from which the data is to be retrieved
		*  @return The data at the given index
		*/
		T& operator[](std::uint32_t index);

		/** Get the item at the given index. This is the constant version
		*  @param index The index from which the data is to be retrieved
		*  @return The data at the given index
		*/
		const T& operator[](std::uint32_t index) const;

		/** Get the beginning of the container
		*   @returns An iterator pointing to the start of the container
		*/
		Iterator begin() const;

		/** Get the end of the container
		*   @returns An iterator poiting to the end of the container
		*/
		Iterator end() const;

		/** Search for a value in the vector and return an iterator to it
		*   @param data The value to search for
		*   @returns Iterator to the first element that matched. Returns end() otherwise
		*/
		Iterator Find(const T& data) const;

		/** Removes the first occurence of the given data from the vector
		*   @param data The data value to be removed
		*   @return A boolean indicating whether an element was removed or not
		*/
		bool Remove(const T& data);

		/** Removes all the elements in the vector starting from first (inclusive) till last (exclusive)
		*   @param first An Iterator pointing to the first element in the range to be removed
		*   @param last  An Iterator pointing to one next to the last element in the range to be removed
		*   @return A boolean indicating whether an element was removed or not
		*/
		bool Remove(const Iterator& first, const Iterator& last);

		/** Reserves enough memory to allocate the given number of items or existing capacity whichever is the maximum
		*   @param capacity The capacity in number of elements to reserve
		*/
		void Reserve(std::uint32_t capacity);

		/** Clear all the items from the vector
		*/
		void Clear();

		/** Destroy the vector object, freeing all allocated resources
		*/
		~Vector();
	private:
		T* mData;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		const CapacityStrategy* mStrategy;
		const CapacityStrategy* mDefaultStrategy;

		// copies data from one list to another. Used in copy constructor and assignment operator
		void Copy(const Vector<T>& rhs);

		//friend Iterator;
	};
}

#include "Vector.inl"
