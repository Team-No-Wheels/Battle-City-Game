#include "Pch.h"
#include "MessageInput.h"
#include "InputHandler.h"

namespace AnonymousEngine
{
	MessageInput::MessageInput() :
		mWorldState(nullptr)
	{

	}

	MessageInput::~MessageInput()
	{

	}

	bool MessageInput::operator==(const MessageInput& rhs)
	{
		return mKeys == rhs.mKeys;
	}

	void MessageInput::AddKey(InputType key, KeyState state)
	{
		mKeys[key] = state;
	}

	HashMap<InputType, KeyState>& MessageInput::GetKeys()
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
