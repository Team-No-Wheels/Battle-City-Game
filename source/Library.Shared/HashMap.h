#pragma once

#include <cstdint>
#include <utility>
#include "SList.h"
#include "Vector.h"

namespace AnonymousEngine
{
	template <typename TKey, typename TData, typename HashFunctor>
	class Hashmap final
	{
		typedef std::pair<TKey, TData> EntryType;
		typedef SList<EntryType> ChainType;
		typedef Vector<ChainType> BucketType;

	public:

		/*class Iterator
		{
		public:
			Iterator();


		private:
			std::uint32_t mIndex;
			typename ChainType::Iterator mChainIterator;

			friend Hashmap;
		};*/

		explicit Hashmap(std::uint32_t buckets = 13U);
		~Hashmap();
	};
}

#include "Hashmap.inl"
