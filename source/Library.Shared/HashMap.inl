#include <utility>

namespace AnonymousEngine
{
	template <typename TKey, typename TData, typename THashFunctor>
	HashMap<TKey, TData, THashFunctor>::HashMap(std::uint32_t buckets = 13U) :
		mSize(0U)
	{
		mData.Reserve(buckets);
		ChainType chainTypeObject;
		for (std::uint32_t i = 0; i < buckets; i++)
		{
			mData.PushBack(chainTypeObject);
		}
	}

	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::Find(const TKey& key) const
	{
		// TODO: return iterator
		std::uint32_t index = CalculateIndex(key);
		ChainType chain = mData[index];
		for (const auto& pair : chain)
		{
			if (pair.first == key)
			{
				return true;
			}
		}
		return false;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	void HashMap<TKey, TData, THashFunctor>::Insert(const EntryType& entry)
	{
		// TODO: return iterator returned by find
		if (Find(entry.first))
		{
			return;
		}
		else
		{
			InsertEntry(entry.first, entry.second);
			return;
		}
	}

	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::Remove(const TKey& key)
	{
		// TODO: match return value with end()
		if (Find(key))
		{
			//TODO: remove the correct item
			return true;
		}
		return false;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	TData& HashMap<TKey, TData, THashFunctor>::operator[](const TKey& key)
	{
		if (Find(key))
		{
			// TODO: return reference to dereference of iterator
			return (*(mData[0].begin())).second;
		}
		else
		{
			TData data;
			return (*InsertEntry(key, data)).second;
		}
	}

	template <typename TKey, typename TData, typename THashFunctor>
	const TData& HashMap<TKey, TData, THashFunctor>::operator[](const TKey& key) const
	{
		if (Find(key))
		{
			// TODO: return reference to dereference of iterator
			return (*(mData[0].begin())).second;
		}
		else
		{
			throw std::out_of_range("Key not found");
		}
	}

	template <typename TKey, typename TData, typename THashFunctor>
	std::uint32_t HashMap<TKey, TData, THashFunctor>::Size() const
	{
		return mSize;
	}

	template <typename TKey, typename TData, typename THashFunctor>
	bool HashMap<TKey, TData, THashFunctor>::ContainsKey(const TKey& key)
	{
		// TODO: check find's return with end()
		return Find(key);
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
	std::uint32_t HashMap<TKey, TData, THashFunctor>::CalculateIndex(const TKey& key)
	{
		static THashFunctor hashFunctor;
		return (hashFunctor(key) % mData.Capacity());
	}

	template <typename TKey, typename TData, typename THashFunctor>
	typename HashMap<TKey, TData, THashFunctor>::EntryType& HashMap<TKey, TData, THashFunctor>::InsertEntry(TKey& key, TData& data)
	{
		std::uint32_t index = CalculateIndex(key);
		ChainIterator it;
		it = mData[index].PushBack(std::make_pair<TKey, TData>(key, TData()));
		return *it;
	}
}
