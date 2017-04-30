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

		ATTRIBUTED_DECLARATIONS(InputHandler, Action);

	public:

		InputHandler();
		~InputHandler() = default;

		void Update(WorldState& worldState) override;

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
