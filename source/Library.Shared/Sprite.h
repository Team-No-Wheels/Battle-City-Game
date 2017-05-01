#pragma once
#include "Renderable.h"
#include "Rectangle.h"

namespace AnonymousEngine
{
	namespace Core 
	{
		class GameObject;
	}
	namespace Graphics
	{
		
		class Sprite : public Renderable
		{
			ATTRIBUTED_DECLARATIONS(Sprite, Renderable)
		public:
			/**
				@brief Default constructor.
			*/
			Sprite(Core::GameObject& gameObject);
			/**
			* Destructor.
			*/
			~Sprite() = default;

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

			/**
			* Get the game object which owns this sprite.
			*/
			Core::GameObject& GetOwner();
		private:
			Core::GameObject& mGameObject;

			Geometry::Rectangle mSpriteBounds;
		};

		ENTITY_FACTORY_DECLARATIONS(Sprite);
	}
}