#pragma once

#include <cstdint>

namespace AnonymousEngine
{
	/** A single linked list container
	*/
	template <typename T>
	class SList
	{
		// Node structure representing each item in the list
		struct Node
		{
			// Pointer to next node in the list
			Node* mNext;
			// The actual data element that is stored in the list
			T mData;

			// Construct a node from a next pointer and a data item
			Node(Node* next, const T& data);
			// Delete default and copy constructors and assignment operator
			Node() = delete;
			Node(const Node& node) = delete;
			Node& operator=(const Node& node) = delete;
		};
	public:
		/** Iterator for SList class
		*/
		class Iterator
		{
		public:
			/** Default constructor. Initializes an empty iterator which doesn't point to anything
			*/
			Iterator();

			/** Initializes an iterator from the values of another iterator
			*  @param rhs The iterator from which values are to be copied
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
			*/
			Iterator operator++(int);

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
			Node* mNode;
			const SList<T>* mOwner;

			Iterator(Node* node, const SList<T>* owner);
			friend SList<T>;
		};

		/** Constructs a new single linked list
		*/
		explicit SList();

		/** Copy constructor to construct a linked list copy of another list
		 *	@param list The other list to create copy from
		*/
		SList(const SList<T>& list);

		/** Assignment operator to copy all the values from another list
		 *	@param list The other list to copy from
		 *	@return A new instance of list which is a copy of the passed list
		*/
		SList<T>& operator=(const SList<T>& list);

		/** Push an item to the front of the list
		 *	@param data The data item to push in the front of the list
		 *	@return An iterator to the current data that is pushed
		*/
		Iterator PushFront(const T& data);

		/** Remove an item from the front of the list
		*/
		void PopFront();

		/** Push an item to the back of the list
		*	@param data The data item to push to the back of the list
		*	@return An iterator to the current data that is pushed
		*/
		Iterator PushBack(const T& data);

		/** Get the item at the front of the list
		*	@return The item at the front of the list
		*/
		T& Front();

		/** Get the item at the front of the list. This is the const version
		*	@return The item at the front of the list
		*/
		const T& Front() const;

		/** Get the item at the back of the list
		*	@return The item at the back of the list
		*/
		T& Back();

		/** Get the item at the back of the list. This is the const version
		*	@return The item at the back of the list
		*/
		const T& Back() const;

		/** Get the total number of items in the list
		*	@return The number of items in the list
		*/
		std::uint32_t Size() const;

		/** Check whether the list is empty or not
		*	@return Whether the list is empty
		*/
		bool IsEmpty() const;

		/** Clear all the items from the linked list
		*/
		void Clear();

		/** Destroy the linked list object, freeing all allocated resources
		*/
		~SList();

		/** Get the beginning of the container
		*   @returns An iterator pointing to the start of the container
		*/
		Iterator begin() const;

		/** Get the end of the container
		*   @returns An iterator poiting to the end of the container
		*/
		Iterator end() const;

		/** Search for a value in the list and return an iterator to it
		*   @param value The value to search for
		*   @returns Iterator to the first element that matched. Returns end() otherwise
		*/
		Iterator Find(const T& value) const;

		/** Insert the given value at a specified location
		*   @param data The data to insert
		*   @param it The iterator which points to the location after which the data is to be inserted
		*   @return An iterator that points to the new data that was inserted
		*/
		Iterator InsertAfter(const T& data, const Iterator& it);

		/** Removes the first occurence of the given data from the list
		*   @param data The data value to be removed
		*   @return A boolean indicating whether an element was removed or not
		*/
		bool Remove(const T& data);

	private:
		// Private method to create a copy of another list
		inline void Copy(const SList<T>& list);

		// Pointer to the first element in the list
		Node* mFront;
		// Pointer to the last element in the list
		Node* mBack;
		// Number of elements in the list
		std::uint32_t mSize;
	};
}

#include "SList.inl"
