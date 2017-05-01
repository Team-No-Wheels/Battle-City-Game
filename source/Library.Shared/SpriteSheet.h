#pragma once
#include "Sprite.h"
#include "SpriteFrame.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		class SpriteSheet : public Sprite
		{
		public:
			/**
				Default constructor
			*/
			SpriteSheet(Core::GameObject& pGameObject);

			/**
				Default destructor
			*/
			~SpriteSheet();

			/**
				@brief Call Init with the file name will initialize this Renderable object with the file.
				@param[in] pFilePath Constant reference to string that holds the path of the file.
			*/
			virtual void Init(const std::string& pSpriteFilePath) override;

			/**
				@brief Called every frame.
				@param[in] pDeltaTime Time between frames in seconds.
			*/
			virtual void Update(float pDeltaTime) override;

			/**
				@brief Called every frame.
			*/
			virtual void Render() override;

			/**
				@brief If debug is enabled this is called every frame.
			*/
			virtual void DrawDebugBounds() override;
		};
	}
}