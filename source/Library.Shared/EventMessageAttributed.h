#pragma once

#include "Attributed.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		/** Implements an attributed event message type
		 */
		class EventMessageAttributed : public Attributed
		{
		public:
			/** Initialize an action list with the given name
			 */
			EventMessageAttributed();
			/** Free up any allocated resources
			 */
			virtual ~EventMessageAttributed() = default;

			/** Copy constructor. Initialize an event message attributed from another instance
			 *  @param rhs The other instance to copy values from
			 */
			EventMessageAttributed(const EventMessageAttributed& rhs);
			/** Move constructor. Initialize an event message attributed from another instance
			 *  @param rhs The other instance to move values from
			 */
			EventMessageAttributed(EventMessageAttributed&& rhs) noexcept;
			/** Copy assignment operator. Copy values from another event message attributed instance
			 *  @param rhs The other instance to copy values from
			 */
			EventMessageAttributed& operator=(const EventMessageAttributed& rhs);
			/** Move assignment operator. Move values from another event message attributed instance
			 *  @param rhs The other instance to move values from
			 */
			EventMessageAttributed& operator=(EventMessageAttributed&& rhs) noexcept;

			/** Get the subtype of events this message is used for
			 *  @return The subtype of this event message
			 */
			const std::string& GetSubtype() const;
			/** Set the sybtype of events this message is used for
			 *  @param subtype The subtype of mesage this event is used for
			 */
			void SetSubtype(const std::string& subtype);

			/** Get the current world on which this message operates
			 *  @return A pointer to the current world
			 */
			class World* GetWorld() const;
			/** Sets the current world on which this message operates on
			 *  @param world The new world on which this message should operate on
			 */
			void SetWorld(class World& world);

		private:
			// The subtype of the event used in subscribing to specifc message types
			std::string mSubtype;
			// The world in which this event is used
			Scope* mWorld;

			ATTRIBUTED_DECLARATIONS(EventMessageAttributed, Attributed)
		};
	}
}
