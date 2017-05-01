#include "Pch.h"
#include "MessageInput.h"

namespace AnonymousEngine
{
	MessageInput::MessageInput() :
		mKeys(5), mWorldState(nullptr)
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
	
	void MessageInput::SetWorldState(Containers::WorldState& worldState)
	{
		mWorldState = &worldState;
	}

	Containers::WorldState& MessageInput::GetWorldState() const
	{
		if (!mWorldState)
		{
			std::runtime_error("Input message has no reference to the world state.");
		}
		return *mWorldState;
	}
}
