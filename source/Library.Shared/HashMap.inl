#include <utility>

namespace AnonymousEngine
{
#pragma region HashmapIteratorMethods

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::Iterator() :
		mIndex(0), mOwner(nullptr)
	{}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator& HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::invalid_argument("Uninitialized iterator");
		}

		if (*this == mOwner->end())
		{
			throw std::out_of_range("iterator out of range");
		}

		if (++mChainIterator == mChainIterator.end())
		{
			for (++mIndex; mIndex < mOwner->mData.Size(); ++mIndex)
			{
				if (mOwner->mData[mIndex].Size() > 0)
				{
					mChainIterator = mOwner->mData[mIndex].begin();
					break;
				}
			}
			if (mIndex == mOwner->mData.Size())
			{
				*this = end();
			}
		}
		return (*this);
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::operator++(int)
	{
		Iterator it = (*this);
		operator++();
		return it;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::EntryType& HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::operator*()
	{
		if (mOwner == nullptr)
		{
			throw std::invalid_argument("Uninitialized iterator");
		}

		if (*this == mOwner->end())
		{
			throw std::out_of_range("iterator out of range");
		}
		return *mChainIterator;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	const typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::EntryType& HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::operator*() const
	{
		return const_cast<const EntryType&>(const_cast<const typename HashMap::Iterator*>(this)->operator*());
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::EntryType* HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::operator->()
	{
		return &operator*();
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	const typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::EntryType* HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::operator->() const
	{
		return &operator*();
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	bool HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner) && (mIndex == rhs.mIndex) && (mChainIterator == rhs.mChainIterator);
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	bool HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::Iterator(const std::uint32_t index, const ChainIterator& it, HashMap* owner) :
		mIndex(index), mChainIterator(it), mOwner(owner)
	{}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator::end() const
	{
		return (mOwner != nullptr) ? mOwner->end() : Iterator();
	}

#pragma endregion

#pragma region HashMapMethods
	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	HashMap<TKey, TData, THashFunctor, TCompareFunctor>::HashMap(std::uint32_t buckets) :
		mData(BucketType(buckets)), mSize(0U)
	{
		if (buckets == 0)
		{
			throw std::invalid_argument("Buckets can't be zero");
		}

		// push default constructed lists into all slots in the vector
		for (std::uint32_t i = 0; i < buckets; ++i)
		{
			mData.PushBack(ChainType());
		}
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	HashMap<TKey, TData, THashFunctor, TCompareFunctor>::HashMap(const std::initializer_list<EntryType>& entries) :
		HashMap()
	{
		for (const auto& entry : entries)
		{
			Insert(entry);
		}
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	HashMap<TKey, TData, THashFunctor, TCompareFunctor>::HashMap(HashMap&& rhs) noexcept
	{
		Move(rhs);
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	HashMap<TKey, TData, THashFunctor, TCompareFunctor>& HashMap<TKey, TData, THashFunctor, TCompareFunctor>::HashMap::operator=(HashMap&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			Move(rhs);
		}
		return *this;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Find(const TKey& key) const
	{
		std::uint32_t index = CalculateIndex(key);
		static DefaultCompare<const TKey> compare;
		const ChainType& chain = mData[index];
		for (auto it = chain.begin(); it != chain.end(); ++it)
		{
			if (compare((*it).first, key))
			{
				return Iterator(index, it, const_cast<HashMap*>(this));
			}
		}
		return end();
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Insert(const EntryType& entry)
	{
		bool hasInserted;
		return Insert(entry, hasInserted);
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Insert(const EntryType& entry, bool& hasInserted)
	{
		Iterator it = Find(entry.first);
		hasInserted = false;
		if (it == end())
		{
			it = InsertEntry(entry.first, entry.second);
			hasInserted = true;
		}
		return it;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	bool HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Remove(const TKey& key)
	{
		Iterator it = Find(key);
		if (it != end())
		{
			mData[it.mIndex].Remove(*it);
			--mSize;
			return true;
		}
		return false;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	TData& HashMap<TKey, TData, THashFunctor, TCompareFunctor>::operator[](const TKey& key)
	{
		Iterator it = Find(key);
		if (it == end())
		{
			it = InsertEntry(key, TData());
		}
		return it->second;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	const TData& HashMap<TKey, TData, THashFunctor, TCompareFunctor>::operator[](const TKey& key) const
	{
		Iterator it = Find(key);
		if (it == end())
		{
			throw std::invalid_argument("Key not found");
		}
		return it->second;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	bool HashMap<TKey, TData, THashFunctor, TCompareFunctor>::operator==(const HashMap& rhs) const
	{
		if (mSize != rhs.mSize)
		{
			return false;
		}

		for (const auto& entry : *this)
		{
			if (!rhs.ContainsKey(entry.first))
			{
				return false;
			}

			if (!((*this)[entry.first] == rhs[entry.first]))
			{
				return false;
			}
		}
		return true;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	bool HashMap<TKey, TData, THashFunctor, TCompareFunctor>::operator!=(const HashMap& rhs) const
	{
		return !(*this == rhs);
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	std::uint32_t HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Size() const
	{
		return mSize;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	bool HashMap<TKey, TData, THashFunctor, TCompareFunctor>::ContainsKey(const TKey& key) const
	{
		return (Find(key) != end());
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	void HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Clear()
	{
		for (auto& chainObject : mData)
		{
			chainObject.Clear();
		}
		mSize = 0;
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator HashMap<TKey, TData, THashFunctor, TCompareFunctor>::begin() const
	{
		
		for (std::uint32_t index = 0; index < mData.Size(); ++index)
		{
			if (mData[index].Size() > 0)
			{
				return Iterator(index, mData[index].begin(), const_cast<HashMap*>(this));
			}
		}
		return end();
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator HashMap<TKey, TData, THashFunctor, TCompareFunctor>::end() const
	{
		std::uint32_t index = (mSize == 0) ? 0 : mData.Size() - 1;
		return Iterator(mData.Size(), mData[index].end(), const_cast<HashMap*>(this));
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	typename HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Iterator HashMap<TKey, TData, THashFunctor, TCompareFunctor>::InsertEntry(const TKey& key, const TData& data)
	{
		std::uint32_t index = CalculateIndex(key);
		ChainIterator it = mData[index].PushBack(std::make_pair(key, data));
		++mSize;
		return Iterator(index, it, this);
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	std::uint32_t HashMap<TKey, TData, THashFunctor, TCompareFunctor>::CalculateIndex(const TKey& key) const
	{
		static THashFunctor hashFunctor;
		return (hashFunctor(key) % mData.Size());
	}

	template <typename TKey, typename TData, typename THashFunctor, typename TCompareFunctor>
	void HashMap<TKey, TData, THashFunctor, TCompareFunctor>::Move(HashMap& rhs)
	{
		mData = std::move(rhs.mData);
		mSize = rhs.mSize;
		rhs.mSize = 0;
	}

#pragma endregion
}
