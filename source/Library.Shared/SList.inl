#ifndef ANONYMOUS_ENGINE_SLIST_HEADER
#include "SList.h"
#endif

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
	SList<T>& SList<T>::operator=(const SList<T>& list)
	{
		if (this != &list)
		{
			Copy(list);
		}
		return *this;
	}

	template<typename T>
	void SList<T>::PushFront(T data)
	{
		Node* node = new Node(mFront, data);
		if (mFront == nullptr)
		{
			mBack = node;
		}
		mFront = node;
		mSize++;
	}

	template<typename T>
	T SList<T>::PopFront()
	{
		if (mSize > 0)
		{
			Node* node = mFront;
			mFront = node->next;
			mSize--;
			if (mFront == nullptr)
			{
				mBack = nullptr;
			}

			T data = node->data;
			delete node;
			return data;
		}
		throw std::exception("Nothing to pop from front. The list is empty.");
	}

	template<typename T>
	void SList<T>::PushBack(T data)
	{
		Node* node = new Node(nullptr, data);
		if (mBack == nullptr)
		{
			mFront = node;
		}
		else
		{
			mBack->next = node;
		}
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
		// Since clear does all the necessary things required to free up resources, call clear
		Clear();
	}

	// This method is used by copy constructor and assignment operator to copy values from another list
	template<typename T>
	void SList<T>::Copy(const SList<T>& list)
	{
		for (Node* node = list.mFront; node != nullptr; node = node->next)
		{
			PushBack(node->data);
		}
	}
}
