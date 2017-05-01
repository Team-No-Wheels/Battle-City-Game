#include "Pch.h"
#include "BattleCityAudio.h"
#include "Event.h"
#include "MessageAudio.h"

namespace BattleCity
{
	using namespace AnonymousEngine;
	using namespace AnonymousEngine::Audio;
	using namespace std;

	const AnonymousEngine::Vector<std::string> BattleCityAudio::mSoundValues = {
																"BulletCollidesWithWall",
																"BulletDestroyed",
																"BullletCreated",
																"EndScoreDisplay",
																"EnemyTankDestroyed",
																"EnemyTankMovement",
																"GameOver",
																"PlayerBlockedByWall",
																"PlayerMovement",
																"PlayerTankDestroyed",
																"PowerUpBomb",
																"PowerUpClock",
																"PowerUpExtraLife",
																"PowerUpShield",
																"PowerUpShovel",
																"Unknown(2)",
																"Unknown"
	};

	BattleCityAudio::~BattleCityAudio()
	{
		ReleaseAllSounds();
	}

	void BattleCityAudio::Initialize()
	{
		Audio::AudioManager::Initialize(mChannelCount);
		PopulateSounds();
	}

	void BattleCityAudio::PopulateSounds()
	{
		for (uint32_t i = 0; i < mChannelCount; ++i)
		{
			FMOD::Sound* tempSound = nullptr;
			string tempName = "sounds\\";
			tempName.append(mSoundValues[i]);
			CreateSound(&tempSound, tempName.append(".wav"));
			mSoundMap.Insert(std::pair<std::string, FMOD::Sound*>(mSoundValues[i], tempSound));
		}
	}

	void BattleCityAudio::Notify(Core::EventPublisher& publisher)
	{
		assert(publisher.Is(Core::Event<MessageAudio>::TypeIdClass()));
		MessageAudio message = static_cast<Core::Event<MessageAudio>&>(publisher).Message();
		PlaySoundBC(mSoundMap[message.AudioType()]);
	}

	void BattleCityAudio::ReleaseAllSounds()
	{
		for (auto& sound : mSoundMap)
		{
			AudioManager::ReleaseSound(sound.second);
		}
	}
}