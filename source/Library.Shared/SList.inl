namespace AnonymousEngine
{
	template<typename T>
	SList<T>::Iterator::Iterator() : mNode(nullptr), mOwner(nullptr)
	{}

	template<typename T>
	SList<T>::Iterator::Iterator(const Iterator& rhs) : mNode(rhs.mNode), mOwner(rhs.mOwner)
	{}

	template<typename T>
	SList<T>::Iterator::Iterator(Node* node, const SList<T>* owner) : mNode(node), mOwner(owner)
	{}

	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const typename SList<T>::Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mNode = rhs.mNode;
		}
		return *this;
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
			throw std::exception("Iterator out of range");
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int unused)
	{
		// The line below is to get rid of the unused parameter warning
		unused;
		if (mNode != nullptr)
		{
			Iterator it = *this;
			mNode = mNode->mNext;
			return it;
		}
		else
		{
			throw std::exception("Iterator out of range");
		}
	}

	template<typename T>
	T& SList<T>::Iterator::operator*()
	{
		if (mNode == nullptr)
		{
			throw std::exception("Iterator does not point a valid element");
		}
		return mNode->mData;
	}

	template<typename T>
	const T& SList<T>::Iterator::operator*() const
	{
		if (mNode == nullptr)
		{
			throw std::exception("Iterator does not point a valid element");
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

	template<typename T>
	SList<T>::SList() : mFront(nullptr), mBack(nullptr), mSize(0)
	{
	}

	template<typename T>
	SList<T>::SList(const SList<T>& list) : mFront(nullptr), mBack(nullptr), mSize(0)
	{
		Copy(list);
	}

	template<typename T>
	SList<T>& SList<T>::operator=(const SList<T>& list)
	{
		if (this != &list)
		{
			Clear();
			Copy(list);
		}
		return *this;
	}

	template<typename T>
	void SList<T>::PushFront(const T& data)
	{
		Node* node = new Node(mFront, data);
		if (mFront == nullptr)
		{
			mBack = node;
		}
		mFront = node;
		mSize++;
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
	void SList<T>::PushBack(const T& data)
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
	}

	template<typename T>
	T& SList<T>::Front()
	{
		if (mFront == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return mFront->mData;
	}

	template<typename T>
	const T& SList<T>::Front() const
	{
		if (mFront == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return static_cast<const T&>(mFront->mData);
	}

	template<typename T>
	T& SList<T>::Back()
	{
		if (mBack == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return mBack->mData;
	}

	template<typename T>
	const T& SList<T>::Back() const
	{
		if (mBack == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return static_cast<const T&>(mBack->mData);
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
		std::uint32_t initialSize = mSize;
		for(std::uint32_t i = 0; i < initialSize; i++)
		{
			PopFront();
		}
	}

	template<typename T>
	SList<T>::~SList()
	{
		// Since clear does all the necessary things required to free up resources, call clear
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
	typename SList<T>::Iterator SList<T>::Find(T& value)
	{
		if (mSize == 1 && mFront->mData == value)
		{
			return Iterator(mFront, this);
		}
		else
		{
			Iterator it = FindIfNextItemMatches(value);
			if (it != end())
			{
				return ++it;
			}
			else
			{
				return it;
			}
		}
	}

	template<typename T>
	void SList<T>::InsertAfter(const T& data, const typename SList<T>::Iterator& it)
	{
		if (it.mNode != nullptr)
		{
			Node* temp = new Node(it.mNode->mNext, data);
			it.mNode->mNext = temp;
			if (mFront == mBack)
			{
				mBack = temp;
			}
			mSize++;
		}
		else
		{
			throw std::exception("Iterator out of range for insert after");
		}
	}

	template<typename T>
	void SList<T>::Remove(T& data)
	{
		if (mFront != nullptr && mFront->mData == data)
		{
			PopFront();
		}
		else if (mSize > 1)
		{
			Iterator it = FindIfNextItemMatches(data);
			if (it != end())
			{
				Node* temp = it.mNode;
				Node* nodeToDelete = temp->mNext;
				temp->mNext = nodeToDelete->mNext;
				delete nodeToDelete;
				mSize--;
			}

			if(mSize == 1)
			{
				mBack = mFront;
			}
		}
	}

	// This method is used by copy constructor and assignment operator to copy values from another list
	template<typename T>
	void SList<T>::Copy(const SList<T>& list)
	{
		for (Node* node = list.mFront; node != nullptr; node = node->mNext)
		{
			PushBack(node->mData);
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::FindIfNextItemMatches(const T& value)
	{
		if (mFront == nullptr)
		{
			return end();
		}
		else
		{
			Node* temp = mFront;
			while (temp->mNext != nullptr)
			{
				if (temp->mNext->mData == value)
				{
					return Iterator(temp, this);
				}
				temp = temp->mNext;
			}
			return end();
		}
	}
}
