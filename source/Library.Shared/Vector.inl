#include <algorithm>
#include "DefaultVectorCapacityStrategy.h"

namespace AnonymousEngine
{
#pragma region IteratorMethods

	template <typename T>
	Vector<T>::Iterator::Iterator() :
		mIndex(0), mOwner(nullptr)
	{
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mOwner == nullptr || mIndex == mOwner->mSize)
		{
			throw std::out_of_range("Iterator out of range");
		}
		++mIndex;
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator it = *this;
		operator++();
		return it;
	}

	template <typename T>
	T& Vector<T>::Iterator::operator*() const
	{
		if (mOwner == nullptr || mIndex == mOwner->mSize)
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
	Vector<T>::Iterator::Iterator(const std::uint32_t index, Vector<T>* owner) :
		mIndex(index), mOwner(owner)
	{
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::end() const
	{
		return (mOwner != nullptr) ? mOwner->end() : Iterator();
	}

#pragma endregion

#pragma region VectorMethods

	template <typename T>
	const std::uint32_t Vector<T>::DefaultCapacity = 3U;

	template <typename T>
	Vector<T>::Vector(std::uint32_t capacity) :
		mData(nullptr), mSize(0), mCapacity(0), mStrategy(nullptr), mDefaultStrategy(new DefaultVectorCapacityStrategy())
	{
		mStrategy = mDefaultStrategy;
		Reserve(capacity);
	}

	template <typename T>
	Vector<T>::Vector(const std::initializer_list<T>& items) :
		Vector((std::max)(static_cast<std::uint32_t>(items.size()), DefaultCapacity))
	{
		for (const auto& item : items)
		{
			PushBack(item);
		}
	}

	template <typename T>
	Vector<T>::Vector(const Vector& rhs) :
		Vector()
	{
		Copy(rhs);
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Copy(rhs);
		}
		return (*this);
	}

	template <typename T>
	Vector<T>::Vector(Vector&& rhs) noexcept :
		mDefaultStrategy(new DefaultVectorCapacityStrategy())
	{
		Move(rhs);
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			Move(rhs);
		}
		return (*this);
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
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& data)
	{
		if (mSize == mCapacity)
		{
			Reserve(mCapacity + (*mStrategy)(mSize, mCapacity));
		}
		new (&mData[mSize]) T(data);
		return Iterator(mSize++, this);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(T&& data)
	{
		if (mSize == mCapacity)
		{
			Reserve(mCapacity + (*mStrategy)(mSize, mCapacity));
		}
		new (&mData[mSize]) T(std::move(data));
		return Iterator(mSize++, this);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(const Vector& vector)
	{
		if (mSize + vector.Size() > mCapacity)
		{
			Reserve(mSize + vector.Size());
		}
		Iterator it(mSize, this);

		for (const auto& data : vector)
		{
			new (&mData[mSize++]) T(data);
		}
		return it;
	}

	template <typename T>
	bool Vector<T>::PopBack()
	{
		if (mSize > 0)
		{
			mData[--mSize].~T();
			return true;
		}
		return false;
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
	bool Vector<T>::operator==(const Vector& rhs) const
	{
		if (mSize != rhs.mSize)
		{
			return false;
		}
		for (std::uint32_t index = 0; index < mSize; ++index)
		{
			if (mData[index] != rhs.mData[index])
			{
				return false;
			}
		}
		return true;
	}

	template <typename T>
	bool Vector<T>::operator!=(const Vector& rhs) const
	{
		return !(*this == rhs);
	}

	template <typename T>
	T& Vector<T>::operator[](std::uint32_t index)
	{
		if (index >= mSize)
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
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator(0, const_cast<Vector<T>*>(this));
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator(mSize, const_cast<Vector<T>*>(this));
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::IteratorAt(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			return end();
		}
		return Iterator(index, const_cast<Vector<T>*>(this));
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
			Iterator first = it++;
			return Remove(first, it);
		}
		return false;
	}

	template <typename T>
	bool Vector<T>::Remove(const typename Vector<T>::Iterator& first, const typename Vector<T>::Iterator& last)
	{
		if (first.mOwner != this || first.mOwner != last.mOwner)
		{
			throw std::invalid_argument("Iterator is not an iterator to this list");
		}

		if (first.mIndex >= 0 && last.mIndex > first.mIndex && last.mIndex <= mSize)
		{
			for (std::uint32_t i = first.mIndex; i < last.mIndex; i++)
			{
				mData[i].~T();
			}
			memmove(&mData[first.mIndex], &mData[last.mIndex], (mSize - last.mIndex) * sizeof(T));
			mSize -= (last.mIndex - first.mIndex);
			return true;
		}
		return false;
	}

	template <typename T>
	void Vector<T>::Reserve(std::uint32_t capacity)
	{
		if (capacity > mCapacity)
		{
			mData = static_cast<T*>(realloc(mData, sizeof(T) * capacity));
			mCapacity = capacity;
		}
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		for (std::uint32_t i = 0; i < mSize; i++)
		{
			mData[i].~T();
		}
		free(reinterpret_cast<void*>(mData));
		mData = nullptr;
		mSize = 0;
		mCapacity = 0;
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
		delete mDefaultStrategy;
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
	void AnonymousEngine::Vector<T>::Copy(const Vector<T>& rhs)
	{
		Reserve(rhs.mCapacity);
		for (std::uint32_t i = 0; i < rhs.mSize; i++)
		{
			PushBack(rhs.mData[i]);
		}
	}

	template <typename T>
	void AnonymousEngine::Vector<T>::Move(Vector<T>& rhs)
	{
		mData = rhs.mData;
		mSize = rhs.mSize;
		mCapacity = rhs.mCapacity;
		if (rhs.mStrategy == rhs.mDefaultStrategy)
		{
			mStrategy = mDefaultStrategy;
		}
		else
		{
			mStrategy = rhs.mStrategy;
		}
		
		rhs.mData = nullptr;
		rhs.mSize = 0;
		rhs.mCapacity = 0;
		rhs.mStrategy = rhs.mDefaultStrategy;
	}

#pragma endregion
}
