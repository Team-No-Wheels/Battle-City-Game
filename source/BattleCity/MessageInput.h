#pragma once

#include "Vector.h"

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

	private:
		Vector<std::string> mKeys;
	};
}
