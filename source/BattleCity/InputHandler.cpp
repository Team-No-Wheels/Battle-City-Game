#include "Pch.h"
#include "InputHandler.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(InputHandler);

InputHandler::InputHandler() :
	handle(GetStdHandle(STD_INPUT_HANDLE)), mEventQueue(nullptr)
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::Update(WorldState& worldState)
{
	worldState.mAction = this;

	DWORD Events = 0;     // Event count
	DWORD EventsRead = 0; // Events read from console

	GetNumberOfConsoleInputEvents(handle, &Events);
	mEventQueue = &worldState.mWorld->EventQueue();

	if (mEventQueue != nullptr && Events != 0)
	{
		MessageInput input;
		INPUT_RECORD* eventBuffer = (INPUT_RECORD*)malloc(Events*sizeof(INPUT_RECORD));
		ReadConsoleInput(handle, eventBuffer, Events, &EventsRead);

		// Read Keys
		for (DWORD i = 0; i < EventsRead; ++i)
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

				case 0x5A || 0x7A: // Z Key
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

		delete eventBuffer;
	}

	worldState.mAction = nullptr;
}