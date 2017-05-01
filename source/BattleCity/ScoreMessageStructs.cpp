#include "Pch.h"
#include "ScoreMessageStructs.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	//TankDefinedMessage functions

	TankDefinedMessage::TankDefinedMessage(const std::string& name, const std::int32_t value) : mName(name), mValue(value)
	{
	}

	const std::string& TankDefinedMessage::Name() const
	{
		return mName;
	}

	std::int32_t TankDefinedMessage::Value() const
	{
		return mValue;
	}

	//LevelOverMessage functions

	LevelOverMessage::LevelOverMessage(const bool wasWin, const HashMap<std::string, std::int32_t>& finalScores) : mWasWin(wasWin), mFinalScores(finalScores)
	{
	}

	bool LevelOverMessage::WasWin() const
	{
		return mWasWin;
	}

	const HashMap<std::string, std::int32_t>& LevelOverMessage::FinalScores() const
	{
		return mFinalScores;
	}

	//ScoreEventMessage functions

	ScoreEventMessage::ScoreEventMessage(const std::string& name, Containers::WorldState& worldState):mName(name), mWorldState(worldState)
	{
	}

	const std::string& ScoreEventMessage::Name() const
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

	Containers::WorldState& TankDestroyedNoScoreMessage::WorldState() const
	{
		return mWorldState;
	}

	//PlayerSideDamageMessage functions

	PlayerSideDamageMessage::PlayerSideDamageMessage(const bool wasFlag, Containers::WorldState& worldState) :mWasFlag(wasFlag), mWorldState(worldState)
	{
	}

	bool PlayerSideDamageMessage::WasFlag() const
	{
		return mWasFlag;
	}

	Containers::WorldState& PlayerSideDamageMessage::WorldState()
	{
		return mWorldState;
	}

	//PlayerLivesChangedMessage functions

	PlayerLivesChangedMessage::PlayerLivesChangedMessage(const std::int32_t numLives) :mNumLives(numLives)
	{
	}

	std::int32_t PlayerLivesChangedMessage::NumLives() const
	{
		return mNumLives;
	}

	//LevelStartMessage functions

	LevelStartMessage::LevelStartMessage(const std::int32_t numberTanks, const std::int32_t levelNumber):mNumberTanks(numberTanks), mLevelNumber(levelNumber)
	{
	}

	std::int32_t LevelStartMessage::NumTanks() const
	{
		return mNumberTanks;
	}

	int32_t LevelStartMessage::LevelNumber() const
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