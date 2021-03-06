#pragma once
#include "TextureLoaderService.h"
#include "Color.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class GameObject;
	}
	namespace Graphics
	{
		/**
			Any object that can be rendered on the screen will extend this class.
		*/
		class Renderable
		{
			friend class Core::GameObject;
		public:
			/**
				Default constructor
			*/
			Renderable();

			/**
			    Default destructor
			*/
			virtual ~Renderable() = default;

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
			virtual void Render() const = 0;

			/**
				@brief If debug is enabled this is called every frame.
			*/
			virtual void DrawDebugBounds() const = 0;

			/**
				@brief return pointer to texture.
				@return Pointer to texture.
			*/
			Texture* GetTexture() const;
			/**
				@brief Get width
			*/
			int32_t GetWidth() const;

			/**
				@brief Get height
			*/
			int32_t GetHeight() const;
			/**
				Getter for tint
			*/
			Color GetTint() const;
			/**
				Setter for tint
			*/
			void SetTint(Color pTint);
		protected:
			/**
				Texture ID for this Renderable
			*/
			Texture* mTexture;

			/**
				Alpha
			*/
			float mAlpha;

			/**
				Tint
			*/
			Color mTint;

			std::int32_t mWidth;
			std::int32_t mHeight;
			
			bool isInitialized;
		};
	}
}