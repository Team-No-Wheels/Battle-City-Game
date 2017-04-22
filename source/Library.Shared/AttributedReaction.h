#pragma once

#include "Reaction.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** A reaction to respond to an attributed event. Even though this is an action this should never be
		 *  added to Actions attribute of any scope
		 */
		class AttributedReaction final : public Reaction
		{
		public:
			/** Initialize an attributed reaction instance
			 *  @param name The name of the reaction
			 */
			AttributedReaction(const std::string& name = "");
			~AttributedReaction() = default;

			// Delete move and copy semantics
			AttributedReaction(const AttributedReaction&) = delete;
			AttributedReaction(AttributedReaction&&) = delete;
			AttributedReaction& operator=(const AttributedReaction&) = delete;
			AttributedReaction& operator=(AttributedReaction&&) = delete;

			/** Accepts notification of events this has subscribed
			 *  @param publisher The publisher of the event
			 */
			void Notify(Core::EventPublisher& publisher) override;
		private:
			// Matches subtypes
			bool MatchSubtype(const std::string& subtype) const;

			// Event type separator
			static const char TypeSeparator;

			ATTRIBUTED_DECLARATIONS(AttributedReaction, Reaction)
		};

		REACTION_FACTORY_DECLARATIONS(AttributedReaction);
	}
}
