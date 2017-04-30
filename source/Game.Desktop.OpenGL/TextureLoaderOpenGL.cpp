#include "Pch.h"
#include "TextureLoaderOpenGL.h"
#include "SOIL.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		TextureLoaderOpenGL::TextureLoaderOpenGL()
		{

		}

		TextureLoaderOpenGL::~TextureLoaderOpenGL()
		{
			Purge();
		}

		std::uint32_t TextureLoaderOpenGL::GetTexture(const std::string& pTextureFilePath, bool pForceLoad)
		{
			HashMap<std::string, std::uint32_t>::Iterator itr = mTextureBank.Find(pTextureFilePath);
			// search if the texture is already loaded before and if not force load
			if (itr != mTextureBank.end() && !pForceLoad)
			{
				return itr->second;
			}

			// load the texture and then save the texture in the bank
			std::uint32_t texture = SOIL_load_OGL_texture(pTextureFilePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y);

			mTextureBank[pTextureFilePath] = texture;
			return texture;
		}

		void TextureLoaderOpenGL::Purge()
		{
			// delete textures from GPU.
			for (std::pair<std::string, std::uint32_t> element : mTextureBank)
			{
				glDeleteTextures(1, &element.second);
			}
			mTextureBank.Clear();
		}
	}
}