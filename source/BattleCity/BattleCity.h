#pragma once
#include "GameObject.h"
#include "CollisionManager.h"
#include "LevelManager.h"
#include "GameClock.h"

//
#include "WorldState.h"
#include "TankPlayer.h"
#include "ActionMove.h"
#include "ActionShoot.h"
#include "InputHandler.h"


namespace BattleCity
{
	/** Forwared declaring World.
	*/
	class World;

	/**
		Entry point for the game BattleCity :)
	*/
	class BattleCity
	{
	public:
		/**
			@brief Default constructor
		*/
		BattleCity();
		/**
			@brief Call Init with the file name will initialize this Renderable object with the file.
			@param[in] pFilePath Constant reference to string that holds the path of the file.
		*/
		void Init();
		/**
			@brief Called every frame.
		*/
		void Update();

	private:
		/** Collision manager
		 */
		AnonymousEngine::Core::CollisionManager mCollisionManager;
		/** Declaring LevelManager for BattleCity Game.
		*/
		Managers::LevelManager mLevelManager;
		/** Pointer to the World of the game.
		*/
		AnonymousEngine::Containers::World* mWorld;

		AnonymousEngine::GameClock mGameClock;

		//AnonymousEngine::Core::GameObject* mGameObject;
		AnonymousEngine::TankPlayer* mGameObject;


		//
		AnonymousEngine::Containers::WorldState mWorldState;
		AnonymousEngine::ActionMoveFactory aMoveFactory;
		AnonymousEngine::ActionShootFactory aShootFactory;
		AnonymousEngine::InputHandler* mInputHandler;

	};
}
