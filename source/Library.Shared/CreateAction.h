#pragma once

#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class CreateAction : public Action
		{
		public:
			CreateAction(const std::string& name = "");
			virtual ~CreateAction() = default;

			CreateAction(const CreateAction&) = delete;
			CreateAction(CreateAction&&) = delete;
			CreateAction& operator==(const CreateAction&) = delete;
			CreateAction& operator==(const CreateAction&&) = delete;

			void SetClassName(const std::string& className);
			const std::string& ClassName() const;
			void Update(WorldState& worldState) override;

		private:
			std::string mClassName;

			ATTRIBUTED_DECLARATIONS(CreateAction, Action)
		};

		ACTION_FACTORY_DECLARATIONS(CreateAction)
	}
}
