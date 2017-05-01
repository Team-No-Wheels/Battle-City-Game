#pragma once

#include "Sprite.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "LevelManager.h"

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
			@param[in] pDeltaTime Time between frames in seconds.
		*/
		void Update(float pDeltaTime);

	private:
		AnonymousEngine::Core::GameObject* mGameObject;
		AnonymousEngine::Core::CollisionManager mCollisionManager;

		/** Declaring LevelManager for BattleCity Game.
		*/
		Managers::LevelManager mLevelManager;

		/** Pointer to the World of the game.
		*/
		AnonymousEngine::Containers::World* mWorld;
	};
}