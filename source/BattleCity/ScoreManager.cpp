#include "Pch.h"
#include "ScoreManager.h"
#include "ScoreMessageStructs.h"
#include "Event.h"
#include "World.h"

namespace AnonymousEngine
{
	const std::int32_t ScoreManager::mPowerupValues = 500;
	const std::string ScoreManager::mPowerupKey = "Powerups";
	const std::string ScoreManager::mTotalKey = "Total";

	ScoreManager::ScoreManager()
	{
		mScoreValues.Insert(std::pair<std::string, std::int32_t>(mPowerupKey, mPowerupValues));
		mCurrentScores.Insert(std::pair<std::string, std::int32_t>(mPowerupKey, 0));
		mCurrentScores.Insert(std::pair<std::string, std::int32_t>(mTotalKey, 0));

		Core::Event<TankDefinedMessage>::Subscribe(*this);
		Core::Event<ScoreEventMessage>::Subscribe(*this);
		Core::Event<PlayerSideDamageMessage>::Subscribe(*this);
		Core::Event<LevelStartMessage>::Subscribe(*this);
	}

	void ScoreManager::AddTankType(std::string name, std::int32_t value)
	{
		mScoreValues.Insert(std::pair<std::string, std::int32_t>(name, value));
	}

	void ScoreManager::HandleScore(std::string scoreType, Containers::WorldState& worldState)
	{
		HashMap<std::string, std::int32_t>::Iterator valueIterator = mScoreValues.Find(scoreType);
		assert(valueIterator != mScoreValues.end());
		HashMap<std::string, std::int32_t>::Iterator totalsIterator = mCurrentScores.Find(scoreType);
		assert(totalsIterator != mScoreValues.end());
		std::int32_t newScore = (*totalsIterator).second + (*valueIterator).second;
		mCurrentScores[scoreType] = newScore;

		if ((scoreType != mPowerupKey) && (scoreType != mTotalKey))
		{
			mNumberTanks--;
			if (mNumberTanks <= 0)
			{
				LevelOver(true, worldState);
			}
		}
	}

	void ScoreManager::LevelOver(bool wasWin, Containers::WorldState& worldState)
	{
		std::int32_t total = 0;
		for(std::pair<std::string, std::int32_t> pair: mCurrentScores)
		{
			if (pair.first != mTotalKey)
			{
				total += pair.second;
			}
		}
		mCurrentScores[mTotalKey] = total;
		LevelOverMessage message(wasWin, mCurrentScores);
		const std::shared_ptr<Core::Event<LevelOverMessage>> eventptr = std::make_shared<Core::Event<LevelOverMessage>>(message);
		worldState.mWorld->EventQueue().Enqueue(eventptr, worldState.mGameTime, 0u);

	}

	void ScoreManager::DamagePlayer(bool wasFlag, Containers::WorldState& worldState)
	{
		if (wasFlag)
		{
			LevelOver(false, worldState);
		}
		else
		{
			mPlayerLives--;
			PlayerLivesChangedMessage message(mPlayerLives);
			const std::shared_ptr<Core::Event<PlayerLivesChangedMessage>> eventptr = std::make_shared<Core::Event<PlayerLivesChangedMessage>>(message);
			worldState.mWorld->EventQueue().Enqueue(eventptr, worldState.mGameTime, 0u);

			if (mPlayerLives <= 0)
			{
				LevelOver(false, worldState);
			}
		}
	}

	void ScoreManager::HandleLevelStart(std::int32_t playerLives, std::int32_t numberTanks, std::int32_t levelNumber)
	{
		mPlayerLives = playerLives;
		mNumberTanks = numberTanks;
		mLevelNumber = levelNumber;
		
		//Reset all scores
		HashMap<std::string, std::int32_t>::Iterator scoreIt = mCurrentScores.begin();
		while (scoreIt != mCurrentScores.end())
		{
			(*scoreIt).second = 0;
			++scoreIt;
		}
	}

	void ScoreManager::Notify(class Core::EventPublisher& publisher)
	{
		if (publisher.Is(Core::Event<TankDefinedMessage>::TypeIdClass()))
		{
			TankDefinedMessage message = publisher.As<Core::Event<TankDefinedMessage>>()->Message();
			AddTankType(message.Name(), message.Value());
		}
		else if (publisher.Is(Core::Event<ScoreEventMessage>::TypeIdClass()))
		{
			ScoreEventMessage message = publisher.As<Core::Event<ScoreEventMessage>>()->Message();
			HandleScore(message.Name(), message.WorldState());
		}
		else if (publisher.Is(Core::Event<PlayerSideDamageMessage>::TypeIdClass()))
		{
			PlayerSideDamageMessage message = publisher.As<Core::Event<PlayerSideDamageMessage>>()->Message();
			DamagePlayer(message.WasFlag(), message.WorldState());
		}
		else if (publisher.Is(Core::Event<LevelStartMessage>::TypeIdClass()))
		{
			LevelStartMessage message = publisher.As<Core::Event<LevelStartMessage>>()->Message();
			HandleLevelStart(message.PlayerLives(), message.NumTanks(), message.LevelNumber());
		}
	}
}
