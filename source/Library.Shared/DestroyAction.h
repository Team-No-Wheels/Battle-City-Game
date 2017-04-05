#pragma once

#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class DestroyAction : public Action
		{
		public:
			DestroyAction(const std::string& name = "");
			virtual ~DestroyAction() = default;

			DestroyAction(const DestroyAction&) = delete;
			DestroyAction(DestroyAction&&) = delete;
			DestroyAction& operator==(const DestroyAction&) = delete;
			DestroyAction& operator==(const DestroyAction&&) = delete;

			void Update(WorldState& worldState) override;

		private:
			std::string mInstanceName;

			ATTRIBUTED_DECLARATIONS(DestroyAction, Action)
		};

		ACTION_FACTORY_DECLARATIONS(DestroyAction)
	}
}
