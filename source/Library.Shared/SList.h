#pragma once

#include "Pch.h"

namespace Library
{
	/** A single linked list container
	*/
	template <typename T>
	class SList
	{
	public:
		/** Constructs a new single linked list
		*/
		explicit SList();

		/** Copy constructor to construct a linked list copy of another list
		 *	@param list The other list to create copy from
		*/
		SList(const SList<T>& list);

		/** Assignment operator to construct a linked list copy of another list
		 *	@param list The other list to create copy from
		 *	@return A new instance of list which is a copy of the passed list
		*/
		SList<T>& operator=(const SList<T>& list);

		/** Push an item to the front of the list
		 *	@param data The data item to push in the front of the list	 
		*/
		void PushFront(const T& data);

		/** Remove an item from the front of the list
		*/
		void PopFront();

		/** Pop an item to the back of the list
		*	@param data The data item to push in the back of the list
		*/
		void PushBack(const T& data);

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

	private:
		// Node structure representing each item in the list
		struct Node
		{
			// Pointer to next node in the list
			Node* next;
			// The actual data element that is stored in the list
			T data;

			// Construct a node from a next pointer and a data item
			Node(Node* next, const T& data) : next(next), data(data)
			{
			}
		};

		// Pointer to the first element in the list
		Node* mFront;
		// Pointer to the last element in the list
		Node* mBack;
		// Number of elements in the list
		std::uint32_t mSize;

		// Private method to create a copy of another list
		inline void Copy(const SList<T>& list);
	};
}

#include "SList.inl"
