#include "Pch.h"
#include "AudioManager.h"
#include "Event.h"
#include "MessageAudio.h"
#include "fmod.hpp"
//#include "fmod_common.h"
#include <exception>

namespace AnonymousEngine
{
	namespace Audio
	{
		using namespace AnonymousEngine::Core;

		AudioManager::AudioManager()
		{
			Event<MessageAudio>::Subscribe(*this);
		}

		void AudioManager::Initialize(std::uint32_t numChannels)
		{
			if (FMOD::System_Create(&mSystem) != FMOD_OK)
			{
				throw std::runtime_error("Error creating the FMOD system.");
			}

			//Check if the computer has supported sound drivers.
			std::int32_t driverCount = 0;
			mSystem->getNumDrivers(&driverCount);

			if (driverCount == 0)
			{
				throw std::runtime_error("No supported audio drivers found.");
				return;
			}

			mSystem->init(numChannels, FMOD_INIT_NORMAL, nullptr);
		}

		AudioManager::~AudioManager()
		{
			Event<MessageAudio>::Unsubscribe(*this);
		}

		void AudioManager::CreateSound(FMOD::Sound* sound, const std::string& filePath)
		{
			mSystem->createSound(filePath.c_str(), FMOD_DEFAULT, nullptr, &sound);
		}

		void AudioManager::PlaySoundBC(FMOD::Sound* sound, bool loop)
		{
			if (!loop)
			{
				sound->setMode(FMOD_LOOP_OFF);
			}
			else
			{
				sound->setMode(FMOD_LOOP_NORMAL);
				sound->setLoopCount(-1);
			}
			mSystem->playSound(sound, 0, false, 0);
		}

		void AudioManager::ReleaseSound(FMOD::Sound* sound)
		{
			sound->release();
		}
	}
}