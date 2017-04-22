#include "Pch.h"
#include "TextureLoader.h"
#include "EngineSettings.h"
#include "SOIL.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		HashMap<std::string, std::uint32_t> TextureLoader::sTextureBank;

		std::uint32_t TextureLoader::GetTexture(const std::string& pTextureFilePath, bool pForceLoad)
		{
			HashMap<std::string, std::uint32_t>::Iterator itr = sTextureBank.Find(pTextureFilePath);
			// search if the texture is already loaded before and if not force load
			if (itr != sTextureBank.end() && !pForceLoad)
			{
				return itr->second;
			}

			if (AnonymousEngine::Core::EngineSettings::GetPlatform() == AnonymousEngine::Core::PlatformType::OpenGL)
			{
				// load the texture and then save the texture in the bank
				std::uint32_t texture = SOIL_load_OGL_texture(pTextureFilePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_INVERT_Y);

				sTextureBank[pTextureFilePath] = texture;
				return texture;
			}
			else if (AnonymousEngine::Core::EngineSettings::GetPlatform() == AnonymousEngine::Core::PlatformType::DirectX)
			{

			}
			assert("Unsupported platform.");
			return 0;
		}

		void TextureLoader::Purge()
		{
			sTextureBank.Clear();
		}
	}
}