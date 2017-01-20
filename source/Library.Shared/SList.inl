namespace Library
{
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
			mFront = node->next;
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
			mBack->next = node;
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
		return mFront->data;
	}

	template<typename T>
	const T& SList<T>::Front() const
	{
		if (mFront == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return static_cast<const T&>(mFront->data);
	}

	template<typename T>
	T& SList<T>::Back()
	{
		if (mBack == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return mBack->data;
	}

	template<typename T>
	const T& SList<T>::Back() const
	{
		if (mBack == nullptr)
		{
			throw std::exception("The list is empty.");
		}
		return static_cast<const T&>(mBack->data);
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
	SList<T>::Iterator::Iterator() : mNode(nullptr), mOwner(nullptr)
	{
	}

	template<typename T>
	SList<T>::Iterator::Iterator(const Iterator& rhs) : mNode(rhs.mNode), mOwner(rhs.mOwner)
	{
	}

	template<typename T>
	SList<T>::Iterator::Iterator(Node* node, const SList<T>* owner) : mNode(node), mOwner(owner)
	{
	}

	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const typename SList<T>::Iterator& rhs)
	{
		if(this != &rhs)
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
			mNode = mNode->next;
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
		// The line below is to get rid of the warning
		unused;
		if (mNode != nullptr)
		{
			Iterator it = *this;
			mNode = mNode->next;
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
		return mNode->data;
	}

	template<typename T>
	const T& SList<T>::Iterator::operator*() const
	{
		return mNode->data;
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
		if (mSize == 1 && mFront->data == value)
		{
			return Iterator(mFront, this);
		}
		else
		{
			Iterator it = FindMatchNext(value);
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
			Node* temp = new Node(it.mNode->next, data);
			it.mNode->next = temp;
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
		if (mFront != nullptr && mFront->data == data)
		{
			PopFront();
		}
		else if (mSize > 1)
		{
			Iterator it = FindMatchNext(data);
			if (it != end())
			{
				Node* temp = it.mNode;
				Node* nodeToDelete = temp->next;
				temp->next = nodeToDelete->next;
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
		for (Node* node = list.mFront; node != nullptr; node = node->next)
		{
			PushBack(node->data);
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::FindMatchNext(const T& value)
	{
		if (mFront == nullptr)
		{
			return end();
		}
		else
		{
			Node* temp = mFront;
			while (temp->next != nullptr)
			{
				if (temp->next->data == value)
				{
					return Iterator(temp, this);
				}
				temp = temp->next;
			}
			return end();
		}
	}
}
