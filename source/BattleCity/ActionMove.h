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

	class ActionMove : public Action
	{
		ATTRIBUTED_DECLARATIONS(ActionMove, Action);
	public:
		static const float sDefaultSpeed;

		enum class Direction
		{
			Unknown,
			Up,
			Down,
			Left,
			Right,
			MaxTypes
		};

		ActionMove();
		~ActionMove() = default;

		void Update(WorldState& worldState) override;

		void Move(WorldState& worldState);
		void SetSpeed(float speed);
		void SetDirection(const Direction direction);
		Direction GetDirection() const;

		bool GetCanMove() const;
		void SetCanMove(bool canMove = true);

	protected:

		Direction mDirection;
		float mSpeed;
		bool mIsPlayer, mCanMove;
	};

	ACTION_FACTORY_DECLARATIONS(ActionMove);
}
