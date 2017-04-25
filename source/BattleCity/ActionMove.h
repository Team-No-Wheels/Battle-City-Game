#pragma once
#include "Action.h"
#include "MessageInput.h"
#include "Event.h"
#include "WorldState.h"
#include "EventSubscriber.h"

namespace AnonymousEngine
{

	using namespace Containers;
	using namespace Core;

	class TankPlayer;

	class ActionMove : public Action, public EventSubscriber
	{

		RTTI_DECLARATIONS(ActionMove, Action);

	public:

		enum class Direction
		{
			Unknown = 0,
			Up, 
			Down, 
			Left, 
			Right,
			MaxTypes
		};

		ActionMove();
		~ActionMove();

		void Update(WorldState& worldState);
		void Notify(class EventPublisher& publisher);

		void Move();
		void SetDirection(Direction direction);

	protected:

		Direction mDirection;
		float mSpeed;
		bool mIsEnemy;
	};
}
