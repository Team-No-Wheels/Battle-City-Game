
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
}
