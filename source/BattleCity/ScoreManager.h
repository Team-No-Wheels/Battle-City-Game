#pragma once
#include "EventSubscriber.h"
#include "HashMap.h"
#include "WorldState.h"

namespace AnonymousEngine
{
	class EventPublisher;

	class ScoreManager : public Core::EventSubscriber
	{
	private:
		HashMap<std::string, std::int32_t> mScoreValues;
		HashMap<std::string, std::int32_t> mCurrentScores;
		std::int32_t mPlayerLives;
		std::int32_t mNumberTanks;
		std::int32_t mLevelNumber;

		static const std::int32_t mPowerupValues;
		static const std::string mPowerupKey;
		static const std::string mTotalKey;
	public:

		/** Construct a score manager. Enter the powerup value and set the powerup and
		*	total current score to 0. Subscribes to the message types: take defined,
		*	score increased, player side dmage, and level start. Sends out the message:
		*	level over and player lives changed.
		*/
		ScoreManager();

		/** Add a tank type to the score value table.
			@param name The name of the tank type.
			@value value The points recieved when destroying that type of tank.
		*/
		void AddTankType(std::string name, std::int32_t value);

		/** Increase the correct field in the total score map. Also if a tank was destroyed
			decrease the number of tanks and handle level over if there are no more tanks.
			@param scoreType The key for the total score map.
		*/
		void HandleScore(std::string scoreType, Containers::WorldState& worldState);

		/** Do the final score calculation and trigger an end of level event.
			@param wasWin true if the player beat the level.
		*/
		void LevelOver(bool wasWin, Containers::WorldState& worldState);

		/** Either subtract lives from the player or end the level imediately if the damage was
		*	to the flag.
		*	@param wasFlag True if the damage was to the flag.
			@param worldState The current state of the world
		*/
		void DamagePlayer(bool wasFlag, Containers::WorldState& worldState);

		/** Add a life to the player
		*	@param worldState The current state of the world
		*/
		void HealPlayer(Containers::WorldState& worldState);

		/** Set all fields for the start of the level
		*	@param playerLives The starting lives for the player.
		*	@param numberTakes The number of tanks in the level.
		*	@param levelNumber	The current level number.
		*/
		void HandleLevelStart(std::int32_t playerLives, std::int32_t numberTanks, std::int32_t levelNumber);

		/** Decrease the number of tanks and handle level over if there are no more.
		*/
		void ScoreManager::DecreaseNumTanks(Containers::WorldState& worldState);

		/** Notify the score manager about any of several score related events.
		*  @param publisher The publisher of the event. Event data is retrieved from this publisher
		*/
		virtual void Notify(class Core::EventPublisher& publisher) override;

		/** Release any interface allocated resources
		*/
		~ScoreManager() = default;
	};
}
