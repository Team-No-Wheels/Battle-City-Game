#pragma once
#include "HashMap.h"
namespace AnonymousEngine
{
	namespace Containers
	{
		class WorldState;
	}

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
		TankDefinedMessage(const std::string& name, const std::int32_t value);

		/** Returns the name of the tank type.
		*	@return The name of the tank type.
		*/
		const std::string& Name() const;

		/** Returns he value of destroying the tank type.
		*	@return The value of destroying of the tank type.
		*/
		std::int32_t Value() const;

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
		HashMap<std::string, std::int32_t> mFinalScores;
	public:
		/** Construct a level over message and fill in it's members
		*/
		LevelOverMessage(const bool wasWin, const HashMap<std::string, std::int32_t>& finalScores);

		/** Returns whether the level was a win or loss.
		*	@return Whether the level was a win or loss.
		*/
		bool WasWin() const;

		/** Returns the map of score type name to final score.
		*	@return The map of score type name to final score.
		*/
		const HashMap<std::string, std::int32_t>& FinalScores() const;

		/** Destruct a level over message
		*/
		~LevelOverMessage() = default;
	};

	/** Used for events where the score would increase
	*/
	struct ScoreEventMessage
	{
	private:
		std::string mName;
		Containers::WorldState& mWorldState;
	public:
		/** Construct a score increase message and fill in it's members
		*/
		ScoreEventMessage(const std::string& name, Containers::WorldState& worldState);

		/** Returns the name of the score type.
		*	@return The name of the score type.
		*/
		const std::string& Name() const;

		/** Returns a reference to the world state.
		*	@return A reference to the world state.
		*/
		Containers::WorldState& WorldState();

		/** Destruct a tank defined message
		*/
		~ScoreEventMessage() = default;
	};

	/** Used for events where a tank would be destroyed but no score would be awarded,
	*	such as with the bomb power up.
	*/
	struct TankDestroyedNoScoreMessage
	{
	private:
		Containers::WorldState& mWorldState;
	public:
		/** Construct a tanks destroyed no score message and fill in it's members
		*/
		TankDestroyedNoScoreMessage(Containers::WorldState& worldState);

		/** Returns a reference to the world state.
		*	@return A reference to the world state.
		*/
		Containers::WorldState& WorldState() const;

		/** Destruct a tanks destroyed no score message
		*/
		~TankDestroyedNoScoreMessage() = default;
	};

	/** Used for events which fire when either the player or the flag receives damage
	*/
	struct PlayerSideDamageMessage
	{
	private:
		bool mWasFlag;
		Containers::WorldState& mWorldState;
	public:
		/** Construct a player side damage message and fill in it's members
		*/
		PlayerSideDamageMessage(const bool wasFlag, Containers::WorldState& worldState);

		/** Returns whether the damage was to the flag or not.
		*	@return Whether the damage was to the flag or not.
		*/
		bool WasFlag() const;

		/** Returns a reference to the world state.
		*	@return A reference to the world state.
		*/
		Containers::WorldState& WorldState();

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
		PlayerLivesChangedMessage(const std::int32_t numLives);

		/** Returns the number of player lives.
		*	@return The number of player lives.
		*/
		std::int32_t NumLives() const;

		/** Destruct a player lives changed message
		*/
		~PlayerLivesChangedMessage() = default;
	};

	/** Used for events which fire when a new level starts.
	*/
	struct LevelStartMessage
	{
	private:
		std::int32_t mNumberTanks;
		std::int32_t mLevelNumber;
	public:
		/** Construct a player lives changed message and fill in it's members
		*/
		LevelStartMessage(const std::int32_t numberTanks, const std::int32_t levelNumber);

		/** Returns the number of tanks.
		*	@return The number of tanks.
		*/
		std::int32_t NumTanks() const;

		/** Returns the level number.
		*	@return The level number.
		*/
		std::int32_t LevelNumber() const;

		/** Destruct a player lives changed message
		*/
		~LevelStartMessage() = default;
	};

	/** Used for events which fire when the player heals a life
	*/
	struct PlayerSideHealMessage
	{
	private:
		Containers::WorldState& mWorldState;
	public:
		/** Construct a player side heal message and fill in it's members
		*/
		PlayerSideHealMessage(Containers::WorldState& worldState);

		/** Returns a reference to the world state.
		*	@return A reference to the world state.
		*/
		Containers::WorldState& WorldState();

		/** Destruct a player side heal message
		*/
		~PlayerSideHealMessage() = default;
	};
}

