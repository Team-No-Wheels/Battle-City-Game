#include "Pch.h"
#include "MessageInput.h"

namespace AnonymousEngine
{
	MessageInput::MessageInput() :
		mKeys(5)
	{

	}

	MessageInput::~MessageInput()
	{

	}

	bool MessageInput::operator==(const MessageInput& rhs)
	{
		if (mKeys.Size() != rhs.mKeys.Size())
		{
			return false;
		}

		for (std::uint32_t i = 0; i < mKeys.Size(); ++i)
		{
			if (mKeys[i] != rhs.mKeys[i])
			{
				return false;
			}
		}
		return true;
	}

	void MessageInput::AddKey(const std::string& key)
	{
		mKeys.PushBack(key);
	}

	Vector<std::string>& MessageInput::GetKeys()
	{
		return mKeys;
	}
}
