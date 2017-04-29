#pragma once
#include "HashMap.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		/**
			TextureLoader follows the singleton pattern.
		*/
		class TextureLoader
		{
		public:
			
			/**
				@brief Return the unsigned int that is used to represent the texture id.
				@details If OpenGL the return value should be casted to GLuint. If DirectX value should be casted to HRESULT
				@param[in] pTextureFilePath String that holds the path to the texture.
				@param[in] pForceLoad If true it will reload the texture if its already loaded. If false load the texture if not loaded else return the already loaded texture id.
				@return unsigned int that holds the id of the texture.
			*/
			static std::uint32_t GetTexture(const std::string& pTextureFilePath, bool pForceLoad = false);

			/**
				@brief Purge all the textures that are loaded.
			*/
			static void Purge();

		private:
			/**
				Static pointer to the TextureLoader.
			*/
			static TextureLoader* mInstance;

			/**
				Map to string and texture ids.
			*/
			static HashMap<std::string, std::uint32_t> sTextureBank;
		};
	}
}