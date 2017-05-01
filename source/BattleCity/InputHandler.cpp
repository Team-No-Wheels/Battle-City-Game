#include "Pch.h"
#include "InputHandler.h"
#include "MessageInput.h"


#define VK_Z 0x5A


namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(InputHandler);

	HashMap<InputType, std::string> InputHandler::KeyEnumStringMap = {
		{ InputType::Esc, "Escape"},
		{ InputType::Up, "Up"},
		{ InputType::Down, "Down"},
		{ InputType::Left, "Left"},
		{ InputType::Right, "Right"},
		{ InputType::Shoot, "Shoot"}
	};

	InputHandler::InputHandler() : mEventQueue(nullptr)
	{
	}

	void InputHandler::SetKeyState(InputType key, KeyState state)
	{
		mKeyStates[key] = state;
	}

	void InputHandler::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		mEventQueue = &(worldState.mWorld->EventQueue());

		if (mEventQueue != nullptr)
		{
			MessageInput input;

			// Read Keys
			for (auto& entry: mKeyStates)
			{
				input.AddKey(entry.first, entry.second);
			}

			// Send MessageInput if not empty
			if (input.GetKeys().Size() != 0)
			{
				input.SetWorldState(worldState);
				mEventQueue->Enqueue(std::make_shared<Event<MessageInput>>(Event<MessageInput>(input)), worldState.mGameTime, 0U);
			}
		}
		worldState.mAction = nullptr;
	}

	void InputHandler::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}
}
