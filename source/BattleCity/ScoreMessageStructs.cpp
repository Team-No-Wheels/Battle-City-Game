#include "Pch.h"
#include "ScoreMessageStructs.h"

namespace AnonymousEngine
{
	//TankDefinedMessage functions

	TankDefinedMessage::TankDefinedMessage(std::string name, std::int32_t value) : mName(name), mValue(value)
	{
	}

	std::string TankDefinedMessage::Name()
	{
		return mName;
	}

	std::int32_t TankDefinedMessage::Value()
	{
		return mValue;
	}


	//LevelOverMessage functions

	LevelOverMessage::LevelOverMessage(bool wasWin, HashMap<std::string, std::int32_t> finalScores) : mWasWin(wasWin), mFinalScores(finalScores)
	{
	}

	bool LevelOverMessage::WasWin()
	{
		return mWasWin;
	}

	HashMap<std::string, std::int32_t> LevelOverMessage::FinalScores()
	{
		return mFinalScores;
	}

	//ScoreEventMessage functions

	ScoreEventMessage::ScoreEventMessage(std::string name, Containers::WorldState& worldState):mName(name), mWorldState(worldState)
	{
	}

	std::string ScoreEventMessage::Name()
	{
		return mName;
	}

	Containers::WorldState& ScoreEventMessage::WorldState()
	{
		return mWorldState;
	}

	//TankDestroyedNoScoreMessage functions
	TankDestroyedNoScoreMessage::TankDestroyedNoScoreMessage(Containers::WorldState& worldState): mWorldState(worldState)
	{
	}

	Containers::WorldState& TankDestroyedNoScoreMessage::WorldState()
	{
		return mWorldState;
	}

	//PlayerSideDamageMessage functions

	PlayerSideDamageMessage::PlayerSideDamageMessage(bool wasFlag, Containers::WorldState& worldState) :mWasFlag(wasFlag), mWorldState(worldState)
	{
	}

	bool PlayerSideDamageMessage::WasFlag()
	{
		return mWasFlag;
	}

	Containers::WorldState& PlayerSideDamageMessage::WorldState()
	{
		return mWorldState;
	}

	//PlayerLivesChangedMessage functions

	PlayerLivesChangedMessage::PlayerLivesChangedMessage(std::int32_t numLives) :mNumLives(numLives)
	{
	}

	std::int32_t PlayerLivesChangedMessage::NumLives()
	{
		return mNumLives;
	}

	//LevelStartMessage functions

	LevelStartMessage::LevelStartMessage(std::int32_t playerLives, std::int32_t numberTanks, std::int32_t levelNumber):mPlayerLives(playerLives), mNumberTanks(numberTanks), mLevelNumber(levelNumber)
	{
	}

	std::int32_t LevelStartMessage::PlayerLives()
	{
		return mPlayerLives;
	}

	std::int32_t LevelStartMessage::NumTanks()
	{
		return mNumberTanks;
	}

	int32_t LevelStartMessage::LevelNumber()
	{
		return mLevelNumber;
	}

	//PlayerSideHealMessage functions
	PlayerSideHealMessage::PlayerSideHealMessage(Containers::WorldState& worldState):mWorldState(worldState)
	{
	}

	Containers::WorldState& PlayerSideHealMessage::WorldState()
	{
		return mWorldState;
	}
}