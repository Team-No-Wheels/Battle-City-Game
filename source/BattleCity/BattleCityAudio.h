#pragma once

#include "AudioManager.h"
#include "EventSubscriber.h"
#include "Vector.h"

namespace FMOD
{
	class Sound;
}

namespace BattleCity
{
	using namespace AnonymousEngine;

	typedef std::pair<std::string, FMOD::Sound*> SoundPair;

	class BattleCityAudio final : public Audio::AudioManager
	{
	public:
		BattleCityAudio() = default;

		~BattleCityAudio();

		void Initialize();

		void PopulateSounds();

		void ReleaseAllSounds();

		void Notify(Core::EventPublisher& publisher) override;

	private:
		const std::uint32_t mChannelCount = 17;
		static const AnonymousEngine::Vector<std::string> mSoundValues;
		HashMap<std::string, FMOD::Sound*> mSoundMap;
	};
}