#pragma once

#include "ActionList.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		class Print : public Action
		{
		public:
			Print(const std::string& name = "");
			virtual ~Print() = default;

			Print(const Print&) = delete;
			Print(Print&&) = delete;
			Print& operator==(const Print&) = delete;
			Print& operator==(const Print&&) = delete;


			void Update(WorldState& worldState) override;
		private:
			std::string mPrintString;

			ATTRIBUTED_DECLARATIONS(Print, Action)
		};

		ACTION_FACTORY_DECLARATIONS(Print)
	}
}
