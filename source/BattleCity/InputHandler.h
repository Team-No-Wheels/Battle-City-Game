#pragma once
#include "Windows.h"
#include "Action.h"
#include "Event.h"
#include "EventQueue.h"
#include "MessageInput.h"
#include "World.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	using namespace Containers;
	using namespace Core;

	class InputHandler final : public Action
	{

		RTTI_DECLARATIONS(InputHandler, Action);

	public:

		InputHandler();
		~InputHandler();

		void Update(WorldState& worldState);

	private:
		HANDLE handle;        // handle to read console
		EventQueue* mEventQueue;

		std::string LEFT = "Left";
		std::string RIGHT = "Right";
		std::string UP = "Up";
		std::string DOWN = "Down";
		std::string SHOOT = "Shoot";
	};
}
