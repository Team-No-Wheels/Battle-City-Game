#pragma once

#include "Windows.h"
#include "Action.h"
#include "Event.h"
#include "EventQueue.h"
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

		static const std::string LEFT;
		static const std::string RIGHT;
		static const std::string UP;
		static const std::string DOWN;
		static const std::string SHOOT;
	};
}
