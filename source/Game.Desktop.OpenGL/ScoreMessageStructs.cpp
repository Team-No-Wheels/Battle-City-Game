#include "Pch.h"
#include "ScoreMessageStructs.h"

namespace AnonymousEngine
{
	//Tank Defined Message functions

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


	//Level Over Message functions

	LevelOverMessage::LevelOverMessage(bool wasWin, HashMap<std::string, std::int16_t> finalScores) : mWasWin(wasWin), mFinalScores(finalScores)
	{
	}

	bool LevelOverMessage::WasWin()
	{
		return mWasWin;
	}

	HashMap<std::string, std::int16_t> LevelOverMessage::FinalScores()
	{
		return mFinalScores;
	}

	//Score Increased Message functions

	ScoreIncreasedMessage::ScoreIncreasedMessage(std::string name) :mName(name)
	{
	}

	std::string ScoreIncreasedMessage::Name()
	{
		return mName;
	}

	//PlayerSideDamageMessage functions

	PlayerSideDamageMessage::PlayerSideDamageMessage(bool wasFlag) :mWasFlag(wasFlag)
	{
	}

	bool PlayerSideDamageMessage::WasFlag()
	{
		return mWasFlag;
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
}