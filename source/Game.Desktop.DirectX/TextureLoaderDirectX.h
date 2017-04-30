#pragma once
#include "TextureLoaderService.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		/**
			Struct that handles the DirectX texture.
		*/
		struct TextureOpenGL : public Texture
		{
			IDirect3DTexture9* mTextureID;
		};

		class TextureLoaderDirectX final : public TextureLoaderService
		{
		public:
			/**
				Default constructor.
			*/
			TextureLoaderDirectX();

			/**
				Default constructor
			*/
			~TextureLoaderDirectX();

			/**
				@brief Return the unsigned int that is used to represent the texture id.
				@details If OpenGL the return value should be casted to GLuint. If DirectX value should be casted to HRESULT
				@param[in] pTextureFilePath String that holds the path to the texture.
				@param[in] pForceLoad If true it will reload the texture if its already loaded. If false load the texture if not loaded else return the already loaded texture id.
				@return unsigned int that holds the id of the texture.
			*/
			virtual Texture* GetTexture(const std::string& pTextureFilePath, bool pForceLoad = false) override;

			/**
				@brief Purge all the textures that are loaded.
			*/
			virtual void Purge() override;

		private:
			/**
				Private constructor so that object of this class cannot be created anywhere outside the ServiceLocator.
			*/
			//TextureLoader_DirectX();
		};
	}
}