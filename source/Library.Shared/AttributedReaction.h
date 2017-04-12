#pragma once

#include "Reaction.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** A reaction to respond to an attributed event 
		 */
		class AttributedReaction final : public Reaction
		{
		public:
			/** Initialize an attributed reaction instance
			 *  @param name The name of the reaction
			 */
			AttributedReaction(const std::string& name = "");

			/** Accepts notification of events this has subscribed
			 *  @param publisher The publisher of the event
			 */
			void Notify(Core::EventPublisher& publisher) override;
		private:
			// The type of the event to which this reaction reacts to
			std::string mSubtype;
			// The event arguments
			Attributed* mEventArgs;

			ATTRIBUTED_DECLARATIONS(AttributedReaction, Reaction)
		};

		REACTION_FACTORY_DECLARATIONS(AttributedReaction);
	}
}
