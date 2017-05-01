#pragma once

#include "Vector.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	class MessageInput
	{
	public:
		MessageInput();
		bool operator==(const MessageInput& rhs);
		~MessageInput();

		void AddKey(const std::string& key);
		Vector<std::string>& GetKeys();
		/**
		* Set the world state associated with this method.
		* @param worldState The world state object to set.
		*/
		void SetWorldState(Containers::WorldState& worldState);
		/**
		* Get the world state associated with this method.
		*/
		Containers::WorldState& GetWorldState() const;
	private:
		Vector<std::string> mKeys;
		/**
		* A pointer to the associated world state.
		*/
		Containers::WorldState* mWorldState;
	};
}
