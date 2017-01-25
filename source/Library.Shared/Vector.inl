#include "Vector.h"
#include <stdexcept>

namespace AnonymousEngine
{

#pragma region IteratorMethods

	template <typename T>
	typename Vector<T>::Iterator::Iterator() :
		mIndex(0), mOwner(nullptr)
	{
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mOwner == nullptr || mIndex >= mSize)
		{
			throw std::out_of_range("Iterator out of range");
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int unused)
	{
		Iterator it = *this;
		operator++();
		return it;
	}

	template <typename T>
	T& Vector<T>::Iterator::operator*() const
	{
		if (mOwner == nullptr || mIndex >= mSize)
		{
			throw std::out_of_range("Iterator out of range");
		}
		return mOwner->mData[mIndex];
	}

	template <typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mIndex == rhs.mIndex);
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	template <typename T>
	typename Vector<T>::Iterator::Iterator(const std::uint32_t index, Vector<T>* owner) :
		mIndex(index), mOwner(owner)
	{
		
	}
#pragma endregion 

#pragma region VectorMethods
	template <typename T>
	Vector<T>::Vector() :
		mData(nullptr), mSize(0), mCapacity(0), mStrategy(nullptr), mDefaultStrategy(new DefaultVectorCapacityStrategy())
	{
		mStrategy = mDefaultStrategy;
		Reserve(mCapacity + mStrategy(mSize, mCapacity));
	}

	template <typename T>
	Vector<T>::Vector(const Vector<T>& rhs) :
		Vector()
	{
		Copy(rhs);
	}

	template <typename T>	
	Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
	{
		if (*this != rhs)
		{
			Clear();
			Copy(rhs);
		}
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& data)
	{
		if (mSize == mCapacity)
		{
			Reserve(mCapacity + mStrategy(mSize, mCapacity));
		}
		mData[mSize++] = data;
	}

	template <typename T>
	bool Vector<T>::PopBack()
	{
		if (mSize > 0)
		{
			mData[--mSize].~T();
		}
	}

	template <typename T>
	T& Vector<T>::Front()
	{
		if (mSize > 0)
		{
			return mData[0];
		}
		throw std::out_of_range("Vector is empty");
	}

	template <typename T>
	const T& Vector<T>::Front() const
	{
		return const_cast<const T&>(const_cast<Vector*>(this)->Front());
	}

	template <typename T>
	T& Vector<T>::Back()
	{
		if (mSize > 0)
		{
			return mData[mSize - 1];
		}
		throw std::out_of_range("Vector is empty");
	}

	template <typename T>
	const T& Vector<T>::Back() const
	{
		return const_cast<const T&>(const_cast<Vector*>(this)->Back());
	}

	template <typename T>
	T& Vector<T>::operator[](std::uint32_t index)
	{
		if (index > mSize)
		{
			throw std::out_of_range("Index out of range");
		}
		return mData[index];
	}

	template <typename T>
	const T& Vector<T>::operator[](std::uint32_t index) const
	{
		return const_cast<const T&>(const_cast<Vector*>(this)->operator[](index));
	}

	template <typename T>
	T& Vector<T>::At(std::uint32_t index)
	{
		return this->operator[](index);
	}

	template <typename T>
	const T& Vector<T>::At(std::uint32_t index) const
	{
		return this->operator[](index);
	}

	template <typename T>
	std::uint32_t Vector<T>::Size() const
	{
		return mSize;
	}

	template <typename T>
	std::uint32_t Vector<T>::Capacity() const
	{
		return mCapacity;
	}

	template <typename T>
	bool Vector<T>::IsEmpty() const
	{
		return (mSize == 0);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator(0, this);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator(mSize+1, this);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& data) const
	{
		for (Iterator it = begin(); it != end(); ++it)
		{
			if (*it == data)
			{
				return it;
			}
		}
		return end();
	}

	template <typename T>
	bool Vector<T>::Remove(const T& data)
	{
		Iterator it = Find(data);
		if (it != end())
		{
			for(std::uint32_t i = it.mIndex; i < mSize - 1; ++i)
			{
				mData[i] = mData[i + 1];
			}
			--mSize;
			return true;
		}
		return false;
	}

	template <typename T>
	bool Vector<T>::Remove(const typename Vector<T>::Iterator& first, const typename Vector<T>::Iterator& last)
	{
		if (first.mOwner != last.mOwner != this)
		{
			throw std::invalid_argument("Iterator is not an iterator to this list");
		}

		if (first.mIndex >= 0 && last.mIndex > first.mIndex && last.mIndex < mSize)
		{
			std::uint32_t copyFromIndex = last.mIndex;
			std::uint32_t itemsToCopy = mSize - last.mIndex;
			for (std::uint32_t i = first.mIndex; i < itemsToCopy; ++i)
			{
				mData[i] = mData[copyFromIndex++];
			}
			for (std::uint32_t i = first.mIndex + itemsToCopy; i < mSize; ++i)
			{
				mData[i].~T();
			}
			--mSize;
			return true;
		}
		return false;
	}

	template <typename T>
	void Vector<T>::Reserve(std::uint32_t capacity)
	{
		if (capacity > mCapacity)
		{
			mData = static_cast<T*>(realloc(mData, sizeof(T) * mCapacity));
			mCapacity = capacity;
		}
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		for (T& value : *this)
		{
			value.~T();
		}
		free(mData);
		mSize = 0;
		mCapacity = 0;
	}

	template <typename T>
	void Vector<T>::IncrementStrategy(const CapacityStrategy* strategy)
	{
		if (strategy == nullptr)
		{
			mStrategy = mDefaultStrategy;
		}
		else
		{
			mStrategy = strategy;
		}
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		for (std::uint32_t i = 0; i < mSize; i++)
		{
			mData[i].~T();
		}
		delete [] mData;
		delete mDefaultStrategy;
	}

	template <typename T>
	void AnonymousEngine::Vector<T>::Copy(const Vector<T>& rhs)
	{
		Reserve(rhs.mCapacity);
		for (std::uint32_t i = 0; i < rhs.mSize; i++)
		{
			PushBack(rhs[i]);
		}
	}
#pragma endregion
}
