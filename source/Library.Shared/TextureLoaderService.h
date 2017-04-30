#pragma once
#include "HashMap.h"
#include "Service.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		/**
			Parent struct that will be holding all the texture based on the platform.
		*/
		struct Texture abstract
		{};

		/**
			The interface that should be implemented by texture loader for ServiceLocator pattern.
		*/
		class TextureLoaderService abstract : public Core::Service
		{
		public:
			/**
				Default constructor.
			*/
			TextureLoaderService() : 
				mTextureBank()
			{

			}

			/**
				@brief Return the unsigned int that is used to represent the texture id.
				@details If OpenGL the return value should be casted to GLuint. If DirectX value should be casted to HRESULT
				@param[in] pTextureFilePath String that holds the path to the texture.
				@param[in] pForceLoad If true it will reload the texture if its already loaded. If false load the texture if not loaded else return the already loaded texture id.
				@return unsigned int that holds the id of the texture.
			*/
			virtual Texture* GetTexture(const std::string& pTextureFilePath, bool pForceLoad = false) = 0;

			/**
				@brief Purge all the textures that are loaded.
			*/
			virtual void Purge() = 0;

		protected:

			/**
				Map to string and texture ids.
			*/
			HashMap<std::string, Texture*> mTextureBank;
		};
	}
}