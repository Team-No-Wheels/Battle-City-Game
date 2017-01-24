#include "Vector.h"

namespace AnonymousEngine
{

#pragma region IteratorMethods

	template <typename T>
	Vector<T>::Iterator::Iterator() : mIndex(0), mOwner(nullptr)
	{
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int unused)
	{
		return Iterator();
	}

	template <typename T>
	T& Vector<T>::Iterator::operator*() const
	{
		return mOwner->mBuffer[mIndex];
	}

	template <typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return false;
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return false;
	}

	template <typename T>
	Vector<T>::Iterator::Iterator(std::uint32_t* index, const Vector<T>* owner)
	{
		mOwner = owner;
		mIndex = index;
	}

	template <typename T>
	Vector<T>::Vector() : mBuffer(static_cast<T*>(malloc(sizeof(T) * mCapacity))), mSize(0), mCapacity(3)
	{
	}

	template <typename T>
	Vector<T>::Vector(const Vector<T>& vector) :
		mBuffer(static_cast<T*>(malloc(sizeof(T) * vector.mCapacity))), mSize(vector.mSize), mCapacity(vector.mCapacity)
	{
		for (std::uint32_t i = 0; i < mCapacity; i++)
		{
			new (mBuffer[i])(vector.mBuffer[i]);
		}
	}

	template <typename T>	
	Vector<T>& Vector<T>::operator=(const Vector<T>& vector)
	{
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& data)
	{
		
	}

	template <typename T>
	bool Vector<T>::PopBack()
	{
		
	}

	template <typename T>
	T& Vector<T>::Front()
	{
		
	}

	template <typename T>
	const T& Vector<T>::Front() const
	{
		
	}

	template <typename T>
	T& Vector<T>::Back()
	{
		
	}

	template <typename T>
	const T& Vector<T>::Back() const
	{
		
	}

	template <typename T>
	T& Vector<T>::operator[](std::uint32_t index)
	{
		
	}

	template <typename T>
	const T& Vector<T>::operator[](std::uint32_t index) const
	{
		
	}

	template <typename T>
	T& Vector<T>::At(std::uint32_t index)
	{
		
	}

	template <typename T>
	std::uint32_t Vector<T>::Size() const
	{
		
	}

	template <typename T>
	std::uint32_t Vector<T>::Capacity() const
	{
		
	}

	template <typename T>
	bool Vector<T>::IsEmpty() const
	{
		
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& data) const
	{
		
	}

	template <typename T>
	bool Vector<T>::Remove(const T& data)
	{
		
	}

	template <typename T>
	bool Vector<T>::Remove(const typename Vector<T>::Iterator& first, const typename Vector<T>::Iterator& last)
	{
		
	}

	template <typename T>
	void Vector<T>::Reserve(std::uint32_t capacity)
	{
		
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		
	}

	template <typename T>
	void Vector<T>::IncrementStrategy(std::function<std::uint32_t(std::uint32_t, std::uint32_t)> strategyFunctor)
	{
		
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		for (std::uint32_t i = 0; i < mSize; i++)
		{
			mBuffer[i].~T();
		}
		delete [] mBuffer;
	}
}
