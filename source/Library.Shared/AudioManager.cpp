#include "Pch.h"
#include "AudioManager.h"

using namespace AnonymousEngine::Audio;

AnonymousEngine::HashMap<std::string, std::string> mSoundMap = { {"Collisions", ""} };

namespace AnonymousEngine
{
	namespace Audio
	{
		void AudioManager::Update(const Containers::EventMessageAttributed& message)
		{
			UNREFERENCED_PARAMETER(message);
		}
	}
}