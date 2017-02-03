#pragma once

#include <cstdint>
#include <utility>
#include "HashFunctors.h"
#include "SList.h"
#include "Vector.h"

namespace AnonymousEngine
{
	template <typename TKey, typename TData, typename THashFunctor = DefaultHashFunctor<TKey>>
	class HashMap final
	{
	public:
		typedef std::pair<TKey, TData> EntryType;
		typedef SList<EntryType> ChainType;
		typedef Vector<ChainType> BucketType;

		/*class Iterator
		{
		public:
			Iterator();


		private:
			std::uint32_t mIndex;
			typename ChainType::Iterator mChainIterator;

			friend HashMap;
		};*/

		/** Initializes a hashmap with provided capacity (no. of buckets).
		 *  A default capaicty is provided in case the user doesn't supply any
		 */
		explicit HashMap(std::uint32_t buckets = 13U);

		/** Copy constructor. Defaults will suffice here
		 *  @param rhs The hashmap to copy from
		 */
		HashMap(const HashMap& rhs) = default;
		/** Copy Assignment operator. Defaults will suffice here
		 *  @param rhs The hashmap to assign from
		 *  @return A reference to the current hashmap
		*/
		HashMap& operator=(const HashMap& rhs) = default;

		//TODO: return iterator
		/** Searches for a key in the hashmap and returns an iterator to the found element
		 *  @param key The key to search for in the hashmap
		 *  @return Iterator to the found key. Returns end() if the key is not found.
		 */
		bool Find(const TKey& key) const;

		//TODO: return iterator
		/** Insert an entry into the hashmap. This method would not overwrite any existing element with the same key
		 *  @param entry The entry to insert into the hashmap
		 *  @return An iterator to the inserted element or with the given key if an element already exists
		 */
		void Insert(const EntryType& entry);

		/** Insert an entry into the hashmap.
		*   @param key The key of the element which should be removed from the hashmap
		*   @return A boolean indicating whether the element was removed or not
		*/
		bool Remove(const TKey& key);

		/** Returns a reference to the data element for a given key.
		 *  If the given key does not exist in the hashmap, insert a default initialized value and return a reference to that
		 *  @param key The key for which the element has to be retrieved
		 *  @returns A reference to the data for the given key
		 */
		TData& operator[](const TKey& key);
		/** Returns a constant reference to the data element for a given key.
		*  If the given key does not exist in the hashmap, this method throws an exception
		*  @param key The key for which the element has to be retrieved
		*  @returns A constant reference to the data for the given key
		*/
		const TData& operator[](const TKey& key) const;

		/** Clears the contents of the hashmap
		 */
		void Clear();
		/** Get the number of elements in the hashmap
		 *  @return The number of elements in the hashmap
		 */
		std::uint32_t Size() const;

		/** Checks if a given key is present in the hashmap
		 *  @param key The key to search in the hashmap
		 *  @return A boolean indicating whether the key is present in the hashmap or not
		 */
		bool ContainsKey(const TKey& key);

		/*Iterator begin() const;
		Iterator end() const;*/

		/** Finalizes the hashmap. Default implementation suffices here.
		 */
		~HashMap() = default;
	private:
		BucketType mData;
		std::uint32_t mSize;

		std::uint32_t CalculateIndex(const TKey& key);
		EntryType& InsertEntry(TKey& key, TData& data);

		typedef typename BucketType::Iterator BucketIterator;
		typedef typename ChainType::Iterator ChainIterator;
	};
}

#include "Hashmap.inl"
