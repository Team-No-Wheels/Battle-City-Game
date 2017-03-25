#pragma once

#include <cstdint>
#include <initializer_list>
#include <utility>
#include "Compare.h"
#include "HashFunctors.h"
#include "SList.h"
#include "Vector.h"

namespace AnonymousEngine
{
	/** A templated Hashmap implementation
	 */
	template <typename TKey, typename TData, typename THashFunctor = DefaultHashFunctor<const TKey>, typename TCompareFunctor = DefaultCompare<const TKey>>
	class HashMap final
	{
	public:
		/** The type of each entry in the hashmap
		*/
		typedef std::pair<const TKey, TData> EntryType;
		/** The type of each chain in the hashmap bucket
		*/
		typedef SList<EntryType> ChainType;
		/** The type of the hashmap buckets
		*/
		typedef Vector<ChainType> BucketType;
		/** The type of iterator to the chain in a hashmap bucket
		*/
		typedef typename ChainType::Iterator ChainIterator;
		/** The type of iterator to the hashmap buckets
		*/
		typedef typename BucketType::Iterator BucketIterator;

		/** Iterator to the hashmap
		 */
		class Iterator
		{
		public:
			/** Default constructor with default implementation
			 */
			Iterator();
			/** Copy constructor with default implementation
			 *  @param rhs The iterator to copy from
			*/
			Iterator(const Iterator& rhs) = default;
			/** Copy assignment operator with default implementation
			 *  @param rhs The iterator to assign from
			 *  @return A reference to the current iterator
			*/
			Iterator& operator=(const Iterator& rhs) = default;
			/** Destructor with default implementation
			*/
			~Iterator() = default;

			/** Moves the iterator to next location.
			 *  @return A reference to the current iterator
			*/
			Iterator& operator++();
			/** Moves the iterator to next location.
			 *  @return An iterator which points to the location before the increment
			*/
			Iterator operator++(int);

			/** Get the entry in the hashmap at the location pointed by the iterator
			 *  @return A reference to the entry at the location pointed by the iterator
			*/
			EntryType& operator*();

			/** Get the entry in the hashmap at the location pointed by the iterator. Constant version
			*   @return A reference to the entry at the location pointed by the iterator
			*/
			const EntryType& operator*() const;

			/** Get the entry in the hashmap at the location pointed by the iterator
			 *  @return A pointer to the entry at the location pointed by the iterator
			*/
			EntryType* operator->();

			/** Get the entry in the hashmap at the location pointed by the iterator constant version
			*  @return A pointer to the entry at the location pointed by the iterator
			*/
			const EntryType* operator->() const;
			
			/** Check if two iterators are equal
			 *  @param rhs The other iterator to which the current one should be compared
			 *  @return True if both the iterators are same. False otherwise
			 */
			bool operator==(const Iterator& rhs) const;
			/** Check if two iterators are not equal
			*  @param rhs The other iterator to which the current one should be compared
			*  @return False if both the iterators are same. True otherwise
			*/
			bool operator!=(const Iterator& rhs) const;

			/** Gets the end iterator for the current hashmap
			 *  @return The end iterator for the current hashmap
			 */
			Iterator end() const;
		private:
			std::uint32_t mIndex;
			typename ChainType::Iterator mChainIterator;
			HashMap* mOwner;
			
			// initialize the iterator with given values
			Iterator(const std::uint32_t index, const ChainIterator& it, HashMap* owner);

			friend HashMap;
		};

		/** Initializes a hashmap with provided capacity (no. of buckets).
		 *  A default capaicty is provided in case the user doesn't supply any
		 */
		explicit HashMap(std::uint32_t buckets = 13U);

		/** Initializes a hashmap with values provided in an initializer list
		 *  @param entries The initalizer list values that will be passed in
		 */
		HashMap(const std::initializer_list<EntryType>& entries);

		/** Copy constructor. Defaults will suffice here
		 *  @param rhs The hashmap to copy from
		 */
		HashMap(const HashMap& rhs) = default;
		/** Copy Assignment operator. Defaults will suffice here
		 *  @param rhs The hashmap to assign from
		 *  @return A reference to the current hashmap
		*/
		HashMap& operator=(const HashMap& rhs) = default;

		/** Move constructor. Defaults will suffice here
		 *  @param rhs The hashmap to copy from
		 */
		HashMap(HashMap&& rhs) noexcept;
		/** Move Assignment operator. Defaults will suffice here
		 *  @param rhs The hashmap to assign from
		 *  @return A reference to the current hashmap
		 */
		HashMap& operator=(HashMap&& rhs) noexcept;

		/** Searches for a key in the hashmap and returns an iterator to the found element
		 *  @param key The key to search for in the hashmap
		 *  @return Iterator to the found key. Returns end() if the key is not found.
		 */
		Iterator Find(const TKey& key) const;

		/** Insert an entry into the hashmap. This method would not overwrite any existing element with the same key
		 *  @param entry The entry to insert into the hashmap
		 *  @return An iterator to the inserted element or with the given key if an element already exists
		 */
		Iterator Insert(const EntryType& entry);

		/** Insert an entry into the hashmap. This method would not overwrite any existing element with the same key
		 *  @param entry The entry to insert into the hashmap
		 *  @param hasInserted Boolean out parameter to indicate whether a new element was inserted or not
		 *  @return An iterator to the inserted element or with the given key if an element already exists
		 */
		Iterator Insert(const EntryType& entry, bool& hasInserted);

		/** Insert an entry into the hashmap.
		 *  @param key The key of the element which should be removed from the hashmap
		 *  @return A boolean indicating whether the element was removed or not
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

		/** Compares this hashmap with another hashmap
		 *  @param rhs The other hashmap instance to compare to
		 *  @return A boolean indicating whether this hashmap is equivalent to the other instance or not
		 */
		bool operator==(const HashMap& rhs) const;

		/** Compares this hashmap with another hashmap
		 *  @param rhs The other hashmap instance to compare to
		 *  @return A boolean indicating whether this hashmap is not equivalent to the other instance or not
		 */
		bool operator!=(const HashMap& rhs) const;

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
		bool ContainsKey(const TKey& key) const;

		/** Return an iterator to the beginning of the hashmap
		 *  @return An iterator to the beginning of the hashmap
		 */
		Iterator begin() const;
		/** Return an iterator to the end of the hashmap. End doesn't point to anything inside the hashmap
		 *  @return An iterator to the end of the hashmap
		 */
		Iterator end() const;

		/** Finalizes the hashmap. Default implementation suffices here.
		 */
		~HashMap() = default;
	private:
		BucketType mData;
		std::uint32_t mSize;

		Iterator InsertEntry(const TKey& key, const TData& data);
		std::uint32_t CalculateIndex(const TKey& key) const;

		// internal method for move semantics
		void Move(HashMap& rhs);
	};
}

#include "Hashmap.inl"
