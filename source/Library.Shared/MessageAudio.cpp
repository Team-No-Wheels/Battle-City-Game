#include "MessageAudio.h"

namespace AnonymousEngine
{
	namespace Audio
	{
		using namespace Containers;

		ATTRIBUTED_DEFINITIONS(MessageAudio)

		MessageAudio::MessageAudio(const MessageAudio& rhs) :
			EventMessageAttributed(rhs)
		{
		}

		void MessageAudio::SetAudioType(const std::string& type)
		{
			EventMessageAttributed::SetSubtype(type);
		}

		const std::string& MessageAudio::AudioType()
		{
			return EventMessageAttributed::GetSubtype();
		}
	}
}