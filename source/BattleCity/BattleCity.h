#pragma once
#include "Sprite.h"
#include "CollisionManager.h"

namespace BattleCity
{
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
		*
		*/


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
		AnonymousEngine::Graphics::Sprite* mSprite;
		AnonymousEngine::Core::CollisionManager mCollisionManager;
	};
}