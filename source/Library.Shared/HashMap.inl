#include <utility>

namespace AnonymousEngine
{
#pragma region HashmapIteratorMethods

	template <typename TKey, typename TData, typename THashFunctor>
	HashMap<TKey, TData, THashFunctor>::Iterator::Iterator() :
		mIndex(0), mChainIterator(ChainIterator()), mOwner(nullptr)
	{
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator& HashMap<TKey, TData, THashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::invalid_argument("Uninitialized iterator");
		}

		if (*this == end())
		{
			throw std::out_of_range("iterator out of range");
		}

		if (++mChainIterator == end())
		{
			for (++mIndex; mIndex < mOwner->mData.Size(); ++mIndex)
			{
				if (mOwner->mData[mIndex].Size() > 0)
				{
					mChainIterator = mOwner->mData[mIndex].begin();
				}
			}
		}
		return (*this);
	}
	
	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::Iterator::operator++(int)
	{
		Iterator it = (*this);
		operator++();
		return it;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::EntryType& HashMap<TKey, TData, THashFunctor>::Iterator::operator*() const
	{
		if (*this == mOwner->end())
		{
			throw std::out_of_range("iterator out of range");
		}
		return *mChainIterator;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::EntryType& HashMap<TKey, TData, THashFunctor>::Iterator::operator->() const
	{
		return operator*();
	}

	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner) && (mIndex == rhs.mIndex) && (mChainIterator == rhs.mChainIterator);
	}

	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	template <typename TKey, typename TData, typename THashFunctor>
	HashMap<TKey, TData, THashFunctor>::Iterator::Iterator(const std::uint32_t index, const ChainIterator it, HashMap* owner) :
		mIndex(index), mChainIterator(it), mOwner(owner)
	{
	}

#pragma endregion

#pragma region HashMapMethods
	template <typename TKey, typename TData, typename THashFunctor>
	HashMap<TKey, TData, THashFunctor>::HashMap(std::uint32_t buckets) :
		mData(BucketType(buckets)), mSize(0U), mBegin(Iterator())
	{
		// push default constructed lists into all slots in the vector
		for (std::uint32_t i = 0; i < buckets; ++i)
		{
			mData.PushBack(ChainType());
		}
		mBegin = end();
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::Find(const TKey& key) const
	{
		std::uint32_t index = CalculateIndex(key);
		ChainType chain = mData[index];
		for (auto it = chain.begin(); it != chain.end(); ++it)
		{
			if ((*it).first == key)
			{
				return Iterator(index, it, const_cast<HashMap*>(this));
			}
		}
		return end();
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::Insert(EntryType& entry)
	{
		Iterator it = Find(entry.first);
		if (it == end())
		{
			it = InsertEntry(entry.first, entry.second);
			++mSize;
		}
		return it;
	}
	/*
	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::Remove(const TKey& key)
	{
		Iterator it = Find(key);
		if (it != end())
		{
			mData[it.mIndex].Remove(*it);
			return true;
		}
		return false;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	TData& HashMap<TKey, TData, THashFunctor>::operator[](const TKey& key)
	{
		Iterator it = Find(key);
		if (it != end())
		{
			TData data;
			it = InsertEntry(key, data);
		}
		return it->second;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	const TData& HashMap<TKey, TData, THashFunctor>::operator[](const TKey& key) const
	{
		return *Find(key);
	}*/

	template <typename TKey, typename TData, typename THashFunctor>
	std::uint32_t HashMap<TKey, TData, THashFunctor>::Size() const
	{
		return mSize;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::ContainsKey(const TKey& key)
	{
		return (Find(key) != end());
	}

	template <typename TKey, typename TData, typename THashFunctor>
	void HashMap<TKey, TData, THashFunctor>::Clear()
	{
		for (auto& chainObject : mData)
		{
			mData.Clear();
		}
		mBegin = end();
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::begin() const
	{
		return mBegin;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::end() const
	{
		return Iterator(mData.Size(), mData[mData.Size() - 1].end(), const_cast<HashMap*>(this));
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::InsertEntry(TKey& key, TData& data)
	{
		std::uint32_t index = CalculateIndex(key);
		ChainIterator it = mData[index].PushBack(std::make_pair(key, data));
		if (index < mBegin.mIndex)
		{
			mBegin = Iterator(index, mData[index].begin(), this);
		}
		return Iterator(index, it, this);
	}

	template <typename TKey, typename TData, typename THashFunctor>
	std::uint32_t HashMap<TKey, TData, THashFunctor>::CalculateIndex(const TKey& key) const
	{
		static THashFunctor hashFunctor;
		return (hashFunctor(key) % mData.Size());
	}
#pragma endregion
}
