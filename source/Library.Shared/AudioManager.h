#pragma once

#include "HashMap.h"
#include "EventSubscriber.h"

namespace FMOD
{
	class Sound;
	class System;
}

namespace AnonymousEngine
{
	class Core::EventPublisher;

	namespace Audio
	{
		class AudioManager : public Core::EventSubscriber
		{
		public:
			/**
			* The default constructor of class.
			*/
			AudioManager();

			void Initialize(std::uint32_t numChannels);

			/**
			* The default destructor of class.
			*/
			virtual ~AudioManager();

			AudioManager(const AudioManager&) = delete;
			AudioManager(AudioManager&&) = delete;


			void CreateSound(FMOD::Sound* sound, const std::string& filePath);

			void PlaySound(FMOD::Sound* sound, bool loop = false);

			void ReleaseSound(FMOD::Sound* sound);

		private:
			FMOD::System* mSystem;
		};
	}
}