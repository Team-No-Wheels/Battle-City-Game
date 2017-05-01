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
			friend class GameObject;

		public:
			/**
				@brief Default constructor.
			*/
			Sprite(Core::GameObject& pGameObject);
			/**
			* Destructor.
			*/
			virtual ~Sprite() = default;

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
			virtual void Render() const override;

			/**
				@brief If debug is enabled this is called every frame.
			*/
			virtual void DrawDebugBounds() const override;

			/**
			* Get the game object which owns this sprite.
			*/
			Core::GameObject& GetOwner() const;

			/**
				Return the sprite bounds
			*/
			Geometry::Rectangle GetSpriteBounds() const;

			/**
				Get the rectangle where sprite is rendered
			*/
			Geometry::Rectangle GetRenderingBounds() const;

			/**
				Return the sprite uv
			*/
			const Geometry::Rectangle& GetUVBounds() const;

			/**
				Translate the sprite bounds based on parent GameObject
			*/
			void UpdatePosition();

			/**
				Rotate sprite based on the rotation of parent GameObject.
			*/
			void UpdateRotation();
		protected:
			Core::GameObject& mGameObject;

			Geometry::Rectangle mSpriteBounds;
			Geometry::Rectangle mRenderingBounds;
			Geometry::Rectangle mUVBounds;

		private:
			float mRotationBuffer;

			glm::vec2 RotatePoint(glm::vec2 pOriginPoint, glm::vec2 pPoint, float_t pAngle);
		};
	}
}