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
		*/
		void operator=(const SList<T>& list);

		/** Push an item to the front of the list
		 *	@param data The data item to push in the front of the list	 
		*/
		void PushFront(T& data);
		/** Pop an item from the front of the list
		*	@return The data item that is removed from the front of the list
		*/
		T& PopFront();
		/** Pop an item to the back of the list
		*	@param data The data item to push in the back of the list
		*/
		void PushBack(T& data);

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
			Node(Node* next, T& data) : next(next), data(data)
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

namespace Library
{
	template<typename T>
	SList<T>::SList() : mFront(nullptr), mBack(nullptr), mSize(0)
	{}

	template<typename T>
	SList<T>::SList(const SList<T>& list) : mFront(nullptr), mBack(nullptr), mSize(list.mSize)
	{
		Copy(list);
	}

	template<typename T>
	void SList<T>::operator=(const SList<T>& list)
	{
		if (this != list)
		{
			Copy(list);
		}
	}

	template<typename T>
	void SList<T>::PushFront(T& data)
	{
		Node* node = new Node(mFront, data);
		mFront = node;
		mSize++;
	}

	template<typename T>
	T& SList<T>::PopFront()
	{
		if (mSize > 0)
		{
			Node* node = mFront;
			mFront = node->next;
			mSize--;
			return node;
		}
		throw std::exception("Nothing to pop from front. The list is empty.");
	}

	template<typename T>
	void SList<T>::PushBack(T& data)
	{
		Node* node = new Node(nullptr, data);
		mBack->next = node;
		mBack = node;
		mSize++;
	}

	template<typename T>
	T& SList<T>::Front()
	{
		if (mFront == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return mFront->data;
	}

	template<typename T>
	const T& SList<T>::Front() const
	{
		if (mFront == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return static_cast<const T&>(mFront->data);
	}

	template<typename T>
	T& SList<T>::Back()
	{
		if (mBack == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return mBack->data;
	}

	template<typename T>
	const T& SList<T>::Back() const
	{
		if (mBack == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return static_cast<const T&>(mBack->data);
	}

	template<typename T>
	std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	bool SList<T>::IsEmpty() const
	{
		return (mFront == nullptr);
	}

	template<typename T>
	void SList<T>::Clear()
	{
		if (mSize == 1)
		{
			delete mFront;
		}
		else if (mSize > 1)
		{
			Node* node = mFront;
			for (Node* nextNode = node->next; nextNode != nullptr; nextNode = nextNode->next)
			{
				delete node;
				node = nextNode;
			}
			delete node;
		}
		mFront = mBack = nullptr;
		mSize = 0;
	}

	template<typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template<typename T>
	void SList<T>::Copy(const SList<T>& list)
	{
		for (Node* node = list.mFront; node != nullptr; node = node->next)
		{
			PushBack(node->data);
		}
	}
}
