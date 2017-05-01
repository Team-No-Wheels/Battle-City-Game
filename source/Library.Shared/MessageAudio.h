#pragma once

#include "EventMessageAttributed.h"

namespace AnonymousEngine
{
	namespace Audio
	{
		using namespace Containers;

		class MessageAudio : public EventMessageAttributed
		{
			ATTRIBUTED_DECLARATIONS(MessageAudio, EventMessageAttributed)

		public:
			MessageAudio() = default;

			virtual ~MessageAudio() = default;

			MessageAudio(const MessageAudio& rhs);

			void SetAudioType(const std::string& type);

			const std::string& AudioType();
		};
	}
}