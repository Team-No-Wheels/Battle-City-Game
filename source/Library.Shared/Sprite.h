#pragma once
#include "Renderable.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		class Sprite : public Renderable
		{
			ATTRIBUTED_DECLARATIONS(Sprite, Renderable)
		public:
			/**
				@brief Default constructor.
			*/
			Sprite();

			/**
				@brief Call Init with the file name will initialize this Renderable object with the file.
				@param[in] pFilePath Constant reference to string that holds the path of the file.
			*/
			virtual void Init(const std::string& pSpriteFilePath);

			/**
				@brief Called every frame.
				@param[in] pDeltaTime Time between frames in seconds.
			*/
			virtual void Update(float pDeltaTime);

			/**
				@brief Called every frame.
			*/
			virtual void Render();

			/**
				@brief If debug is enabled this is called every frame.
			*/
			virtual void DrawDebugBounds();
		};

		ENTITY_FACTORY_DECLARATIONS(Sprite);
	}
}