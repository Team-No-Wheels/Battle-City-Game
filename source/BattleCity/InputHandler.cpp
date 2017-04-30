#include "Pch.h"
#include "InputHandler.h"
#include "MessageInput.h"


#define VK_Z 0x5A


namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(InputHandler);

	const std::string InputHandler::LEFT = "Left";
	const std::string InputHandler::RIGHT = "Right";
	const std::string InputHandler::UP = "Up";
	const std::string InputHandler::DOWN = "Down";
	const std::string InputHandler::SHOOT = "Shoot";

	InputHandler::InputHandler() :
		handle(GetStdHandle(STD_INPUT_HANDLE)), mEventQueue(nullptr)
	{
	}

	void InputHandler::Update(WorldState& worldState)
	{
		worldState.mAction = this;

		DWORD events = 0;     // Event count
		DWORD eventsRead = 0; // Events read from console

		GetNumberOfConsoleInputEvents(handle, &events);
		mEventQueue = &worldState.mWorld->EventQueue();

		if (mEventQueue != nullptr && events != 0)
		{
			MessageInput input;
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[events]; //static_cast<INPUT_RECORD*>(malloc(events * sizeof(INPUT_RECORD)));
			ReadConsoleInput(handle, eventBuffer, events, &eventsRead);

			// Read Keys
			for (DWORD i = 0; i < eventsRead; ++i)
			{
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown)
				{
					// Add Acceptable Keys To MessageInput
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
					{
						case VK_LEFT:
							input.AddKey(LEFT);
							break;

						case VK_RIGHT:
							input.AddKey(RIGHT);
							break;

						case VK_UP:
							input.AddKey(UP);
							break;

						case VK_DOWN:
							input.AddKey(DOWN);
							break;

						case VK_Z:
							input.AddKey(SHOOT);
							break;

						default:
							break;
					}
				}
			}

			// Send MessageInput if not empty
			if (!input.GetKeys().IsEmpty())
			{
				mEventQueue->Enqueue(std::make_shared<Event<MessageInput>>(Event<MessageInput>(input)), worldState.mGameTime, 0U);
			}

			delete[] eventBuffer;
		}

		worldState.mAction = nullptr;
	}

	void InputHandler::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}
}
