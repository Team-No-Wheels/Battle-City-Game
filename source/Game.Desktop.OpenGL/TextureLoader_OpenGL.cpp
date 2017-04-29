#include "Pch.h"
#include "TextureLoader_OpenGL.h"
#include "SOIL.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		TextureLoader_OpenGL::TextureLoader_OpenGL()
		{

		}

		TextureLoader_OpenGL::~TextureLoader_OpenGL()
		{
			Purge();
		}

		std::uint32_t TextureLoader_OpenGL::GetTexture(const std::string& pTextureFilePath, bool pForceLoad)
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

		void TextureLoader_OpenGL::Purge()
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