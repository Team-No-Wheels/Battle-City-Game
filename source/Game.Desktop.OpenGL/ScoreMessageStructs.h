#pragma once
#include "HashMap.h"
namespace AnonymousEngine
{
	/** Used for events which fire when a tank definition is recieved by
	*   the parser.
	*/
	struct TankDefinedMessage
	{
	private:
		std::string mName;
		std::int32_t mValue;
	public:
		/** Construct a tank defined message and fill in it's members
		*/
		TankDefinedMessage(std::string name, std::int32_t value);

		/** Returns the name of the tank type.
		*	@return The name of the tank type.
		*/
		std::string Name();

		/** Returns he value of destroying the tank type.
		*	@return The value of destroying of the tank type.
		*/
		std::int32_t Value();

		/** Destruct a tank defined message
		*/
		~TankDefinedMessage() = default;
	};

	/** Used for events which fire when a level is over so the UI can know what
	*	to display and what comes after the score screen.
	*/
	struct LevelOverMessage
	{
	private:
		bool mWasWin;
		HashMap<std::string, std::int16_t> mFinalScores;
	public:
		/** Construct a level over message and fill in it's members
		*/
		LevelOverMessage(bool wasWin, HashMap<std::string, std::int16_t> finalScores);

		/** Returns whether the level was a win or loss.
		*	@return Whether the level was a win or loss.
		*/
		bool WasWin();

		/** Returns the map of score type name to final score.
		*	@return The map of score type name to final score.
		*/
		HashMap<std::string, std::int16_t> FinalScores();

		/** Destruct a level over message
		*/
		~LevelOverMessage() = default;
	};

	/** Used for events where the score would increase
	*/
	struct ScoreIncreasedMessage
	{
	private:
		std::string mName;
	public:
		/** Construct a score increase message and fill in it's members
		*/
		ScoreIncreasedMessage(std::string name);

		/** Returns the name of the score type.
		*	@return The name of the score type.
		*/
		std::string Name();

		/** Destruct a tank defined message
		*/
		~ScoreIncreasedMessage() = default;
	};

	/** Used for events which fire when either the player or the flag recieves damage
	*/
	struct PlayerSideDamageMessage
	{
	private:
		bool mWasFlag;
	public:
		/** Construct a player side damage message and fill in it's members
		*/
		PlayerSideDamageMessage(bool wasFlag);

		/** Returns whether the damage was to the flag or not.
		*	@return Whether the damage was to the flag or not.
		*/
		bool WasFlag();

		/** Destruct a player side damage message
		*/
		~PlayerSideDamageMessage() = default;
	};

	/** Used for events which fire when the number of player lives has changed
	*/
	struct PlayerLivesChangedMessage
	{
	private:
		std::int32_t mNumLives;
	public:
		/** Construct a player lives changed message and fill in it's members
		*/
		PlayerLivesChangedMessage(std::int32_t numLives);

		/** Returns the number of player lives.
		*	@return The number of player lives.
		*/
		std::int32_t NumLives();

		/** Destruct a player lives changed message
		*/
		~PlayerLivesChangedMessage() = default;
	};

	/** Used for events which fire when a new level starts
	*/
	struct LevelStartMessage
	{
	private:
		std::int32_t mPlayerLives;
		std::int32_t mNumberTanks;
		std::int32_t mLevelNumber;
	public:
		/** Construct a player lives changed message and fill in it's members
		*/
		LevelStartMessage(std::int32_t playerLives, std::int32_t numberTanks, std::int32_t levelNumber);

		/** Returns the number of player lives.
		*	@return The number of player lives.
		*/
		std::int32_t PlayerLives();

		/** Returns the number of tanks.
		*	@return The number of tanks.
		*/
		std::int32_t NumTanks();

		/** Returns the level number.
		*	@return The level number.
		*/
		std::int32_t LevelNumber();

		/** Destruct a player lives changed message
		*/
		~LevelStartMessage() = default;
	};
}
