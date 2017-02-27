
namespace AnonymousEngine
{
#pragma region NodeMethods
	template<typename T>
	SList<T>::Node::Node(Node* next, const T& data) : mNext(next), mData(data)
	{
	}
#pragma endregion 

#pragma region IteratorMethods
	template<typename T>
	SList<T>::Iterator::Iterator() : mNode(nullptr), mOwner(nullptr)
	{
	}

	template<typename T>
	SList<T>::Iterator::Iterator(Node* node, const SList<T>* owner) : mNode(node), mOwner(owner)
	{
	}
	
	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mNode != nullptr)
		{
			mNode = mNode->mNext;
			return *this;
		}
		else
		{
			throw std::out_of_range("Iterator out of range");
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		if (mNode != nullptr)
		{
			Iterator it = *this;
			mNode = mNode->mNext;
			return it;
		}
		else
		{
			throw std::out_of_range("Iterator out of range");
		}
	}

	template<typename T>
	T& SList<T>::Iterator::operator*() const
	{
		if (mNode == nullptr)
		{
			throw std::domain_error("Iterator does not point a valid element");
		}
		return mNode->mData;
	}

	template<typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mNode == rhs.mNode);
	}

	template<typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}
#pragma endregion 

#pragma region SListMethods
	template<typename T>
	SList<T>::SList() : mFront(nullptr), mBack(nullptr), mSize(0)
	{
	}

	template<typename T>
	SList<T>::SList(const SList& rhs) : SList()
	{
		Copy(rhs);
	}

	template<typename T>
	SList<T>& SList<T>::operator=(const SList& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Copy(rhs);
		}
		return *this;
	}

	template<typename T>
	SList<T>::SList(SList&& rhs) noexcept
	{
		Move(rhs);
	}

	template <typename T>
	SList<T>& SList<T>::operator=(SList&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			Move(rhs);
		}
		return *this;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::PushFront(const T& data)
	{
		Node* node = new Node(mFront, data);
		if (mFront == nullptr)
		{
			mBack = node;
		}
		mFront = node;
		mSize++;
		return begin();
	}

	template<typename T>
	void SList<T>::PopFront()
	{
		if (mSize > 0)
		{
			Node* node = mFront;
			mFront = node->mNext;
			mSize--;
			if (mFront == nullptr)
			{
				mBack = nullptr;
			}
			delete node;
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& data)
	{
		Node* node = new Node(nullptr, data);
		if (mBack != nullptr)
		{
			mBack->mNext = node;
		}
		else
		{
			mFront = node;
		}
		mBack = node;
		mSize++;
		return Iterator(node, this);
	}

	template<typename T>
	T& SList<T>::Front()
	{
		if (mFront == nullptr)
		{
			throw std::domain_error("The list is empty.");
		}
		return mFront->mData;
	}

	template<typename T>
	const T& SList<T>::Front() const
	{
		return const_cast<const T&>(const_cast<SList*>(this)->Front());
	}

	template<typename T>
	T& SList<T>::Back()
	{
		if (mBack == nullptr)
		{
			throw std::domain_error("The list is empty.");
		}
		return mBack->mData;
	}

	template<typename T>
	const T& SList<T>::Back() const
	{
		return const_cast<const T&>(const_cast<SList*>(this)->Back());
	}

	template<typename T>
	std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	bool SList<T>::IsEmpty() const
	{
		return (mFront == nullptr);
	}

	template<typename T>
	void SList<T>::Clear()
	{
		while(mSize > 0)
		{
			PopFront();
		}
	}

	template<typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(mFront, this);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(nullptr, this);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& value) const
	{
		for(Iterator it = begin(); it != end(); ++it)
		{
			if (*it == value)
			{
				return it;
			}
		}
		return end();
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::InsertAfter(const T& data, const typename SList<T>::Iterator& it)
	{
		if (it.mOwner != this)
		{
			throw std::invalid_argument("Iterator is not an iterator to the current list");
		}
		
		if (it == end())
		{
			return PushBack(data);
		}

		Node* node = new Node(it.mNode->mNext, data);
		if (it.mNode == mBack)
		{
			mBack = node;
		}
		it.mNode->mNext = node;
		mSize++;
		return Iterator(node, this);
	}

	template<typename T>
	bool SList<T>::Remove(const T& data)
	{
		if (mSize == 0)
		{
			return false;
		}
		
		if (mFront->mData == data)
		{
			PopFront();
			return true;
		}
				
		Iterator previous = begin();
		for (Iterator it = ++begin(); it != end(); ++it)
		{
			if (*it == data)
			{
				previous.mNode->mNext = it.mNode->mNext;
				if (it.mNode == mBack)
				{
					mBack = previous.mNode;
				}
				delete it.mNode;
				mSize--;
				return true;
			}
			previous = it;
		}
		return false;
	}

	// This method is used by copy constructor and copy assignment operator to copy values from another list
	template<typename T>
	void SList<T>::Copy(const SList<T>& rhs)
	{
		for (Node* node = rhs.mFront; node != nullptr; node = node->mNext)
		{
			PushBack(node->mData);
		}
	}

	// This method is used by move constructor and move assignment operator to move values from another list
	template<typename T>
	void SList<T>::Move(SList<T>& rhs)
	{
		mFront = rhs.mFront;
		mBack = rhs.mBack;
		mSize = rhs.mSize;
		rhs.mFront = rhs.mBack = nullptr;
		rhs.mSize = 0;
	}

#pragma endregion 
}
