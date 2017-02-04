#include <utility>

namespace AnonymousEngine
{
#pragma region HashmapIteratorMethods
	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator& HashMap<TKey, TData, THashFunctor>::Iterator::operator++()
	{
		if (mIndex < mData.Size())
		{
			if (mChainIterator == mData[mIndex].end())
			{
				++mIndex;
				if (mIndex < mData.Size())
				{
					mChainIterator = mData[mIndex].begin();
				}
			}
			else
			{
				++mChainIterator;
			}
		}
		return *this;
	}
	
	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::Iterator::operator++(int)
	{
		Iterator it = ++(*this);
		return it;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::EntryType& HashMap<TKey, TData, THashFunctor>::Iterator::operator*() const
	{
		if (mIndex < mData.Size() && mChainIterator != mData[mIndex].end())
		{
			return *mChainIterator;
		}
		throw std::out_of_range("Iterator out of range");
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::EntryType& HashMap<TKey, TData, THashFunctor>::Iterator::operator->() const
	{
		return operator*();
	}

	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mChainIterator == rhs.mChainIterator) && (mIndex == rhs.mIndex);
	}

	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	template <typename TKey, typename TData, typename THashFunctor>
	HashMap<TKey, TData, THashFunctor>::Iterator::Iterator(std::uint32_t index, ChainIterator& it) :
		mIndex(index), mChainIterator(it)
	{
	}
#pragma endregion

#pragma region HashMapMethods
	template <typename TKey, typename TData, typename THashFunctor>
	HashMap<TKey, TData, THashFunctor>::HashMap(std::uint32_t buckets = 13U) :
		mSize(0U)
	{
		mData.Reserve(buckets);
		ChainType chainTypeObject;
		for (std::uint32_t i = 0; i < buckets; ++i)
		{
			mData.PushBack(chainTypeObject);
		}
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::Find(const TKey& key) const
	{
		std::uint32_t index = CalculateIndex(key);
		ChainType chain = mData[index];
		for (const auto& it = chain.begin(); it != chain.end(); ++it)
		{
			if (it->first == key)
			{
				return Iterator(index, it);
			}
		}
		return end();
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::Insert(const EntryType& entry)
	{
		Iterator it = Find(entry.first);
		if (it == end())
		{
			it = InsertEntry(entry.first, entry.second);
		}
		return it;
	}

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
	}

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
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::begin() const
	{
		for (std::uint32_t index = 0; index < mData.Size(); ++index)
		{
			if (mData[index].Size() > 0)
			{
				return Iterator(index, mData[index].begin());
			}
		}
		return Iterator(0, mData[0].begin());
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::end() const
	{
		return Iterator(mData.Size(), mData[mData.Size() - 1].end());
	}

	template <typename TKey, typename TData, typename THashFunctor>
	std::uint32_t HashMap<TKey, TData, THashFunctor>::CalculateIndex(const TKey& key)
	{
		static THashFunctor hashFunctor;
		return (hashFunctor(key) % mData.Size());
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::Iterator HashMap<TKey, TData, THashFunctor>::InsertEntry(TKey& key, TData& data)
	{
		std::uint32_t index = CalculateIndex(key);
		ChainIterator it;
		it = mData[index].PushBack(std::make_pair<TKey, TData>(key, TData()));
		return Iterator(index, it);
	}
#pragma endregion
}
