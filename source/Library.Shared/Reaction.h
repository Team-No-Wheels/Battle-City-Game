#pragma once

#include "ActionList.h"
#include "EventSubscriber.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** Implements an action which can hold other actions
		 */
		class Reaction : public ActionList, public Core::EventSubscriber
		{
		public:
			/** Initialize an action list with the given name
			 *  @param name The name of the action list
			 */
			Reaction(const std::string& name = "");
			/** Free up any allocated resources
			 */
			virtual ~Reaction() = default;

			// Delete move and copy semantics
			Reaction(const Reaction&) = delete;
			Reaction(Reaction&&) = delete;
			Reaction& operator==(const Reaction&) = delete;
			Reaction& operator==(const Reaction&&) = delete;

			ATTRIBUTED_DECLARATIONS(Reaction, Action)
		};

#define REACTION_FACTORY_DECLARATIONS(ConcreteReactionT)		\
	CONCRETE_FACTORY_DECLARATIONS(Reaction, ConcreteReactionT)

#define REACTION_FACTORY_DEFINITIONS(ConcreteReactionT)		\
	CONCRETE_FACTORY_DEFINITIONS(Reaction, ConcreteReactionT)
	}
}
