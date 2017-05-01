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

		enum class InputType
		{
			Esc,
			Up,
			Down,
			Left,
			Right,
			Shoot
		};

		enum class KeyState
		{
			Invalid,
			Pressed,
			Released,
			Repeat
		};

		void Update(WorldState& worldState) override;

		void SetKeyState(InputType key, KeyState state);

	private:
		EventQueue* mEventQueue;

		HashMap<InputType, KeyState> mKeyStates;

		static HashMap<InputType, std::string> KeyEnumStringMap;
	};
}
