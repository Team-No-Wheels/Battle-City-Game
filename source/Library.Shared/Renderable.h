#pragma once
#include "Entity.h"
#include "TextureLoaderService.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		/**
			Any object that can be rendered on the screen will extend this class.
		*/
		class Renderable abstract : public Containers::Entity
		{
		public:
			/**
				Default constructor
			*/
			Renderable();

			/**
				@brief Call Init with the file name will initialize this Renderable object with the file.
				@param[in] pFilePath Constant reference to string that holds the path of the file.
			*/
			virtual void Init(const std::string& pFilePath);

			/**
				@brief Called every frame.
				@param[in] pDeltaTime Time between frames in seconds.
			*/
			virtual void Update(float pDeltaTime);

			/**
				@brief Called every frame.
			*/
			virtual void Render() = 0;

			/**
				@brief If debug is enabled this is called every frame.
			*/
			virtual void DrawDebugBounds() = 0;
		protected:
			/**
				Texture ID for this Renderable
			*/
			Texture* mTexture;

			/**
				Alpha
			*/
			float mAlpha;

			std::int32_t mWidth;
			std::int32_t mHeight;
			glm::vec4 mPosition;

			bool isInitialized;

		private:
			ATTRIBUTED_DECLARATIONS(Renderable, Containers::Entity)
		};
	}
}