#pragma once

#include "WorldState.h"
#include "HashMap.h"

namespace AnonymousEngine
{
	enum class InputType;
	enum class KeyState;

	class MessageInput
	{
	public:
		MessageInput();
		bool operator==(const MessageInput& rhs);
		~MessageInput();

		void AddKey(InputType key, KeyState state);
		HashMap<InputType, KeyState>& GetKeys();
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
		HashMap<InputType, KeyState> mKeys;
		/**
		* A pointer to the associated world state.
		*/
		Containers::WorldState* mWorldState;
	};
}
