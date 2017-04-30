#pragma once
#include "Vector.h"
#include "EventMessageAttributed.h"

namespace BattleCity
{
	using namespace AnonymousEngine::Containers;

	class MessageInput : public EventMessageAttributed
	{
		ATTRIBUTED_DECLARATIONS(MessageInput, EventMessageAttributed)

	public:
		MessageInput();
		bool operator==(const MessageInput& rhs);
		~MessageInput();

		void AddKey(std::string& key);
		AnonymousEngine::Vector<std::string*>& GetKeys();

	private:
		AnonymousEngine::Vector<std::string*> mKeys;
	};
}