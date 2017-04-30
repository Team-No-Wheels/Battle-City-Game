#include "Pch.h"
#include "TextureLoaderOpenGL.h"
#include "SOIL.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		TextureLoaderOpenGL::TextureLoaderOpenGL() :
			TextureLoaderService()
		{

		}

		TextureLoaderOpenGL::~TextureLoaderOpenGL()
		{
			Purge();
		}

		Texture* TextureLoaderOpenGL::GetTexture(const std::string& pTextureFilePath, bool pForceLoad)
		{
			HashMap<std::string, Texture*>::Iterator itr = mTextureBank.Find(pTextureFilePath);
			// search if the texture is already loaded before and if not force load
			if (itr != mTextureBank.end() && !pForceLoad)
			{
				return itr->second;
			}

			// load the texture and then save the texture in the bank
			std::uint32_t texture = SOIL_load_OGL_texture(pTextureFilePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y);

			TextureOpenGL* newTexture = new TextureOpenGL;
			newTexture->mTextureID = texture;

			mTextureBank[pTextureFilePath] = newTexture;
			return newTexture;
		}

		void TextureLoaderOpenGL::Purge()
		{
			// delete textures from GPU.
			for (std::pair<std::string, Texture*> element : mTextureBank)
			{
				TextureOpenGL* texture = static_cast<TextureOpenGL*>(element.second);
				glDeleteTextures(1, &texture->mTextureID);

				// cleaning house
				delete texture;
			}
			mTextureBank.Clear();
		}
	}
}