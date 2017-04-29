#include "Pch.h"
#include "TextureLoader_DirectX.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		TextureLoader_DirectX::TextureLoader_DirectX()
		{

		}

		TextureLoader_DirectX::~TextureLoader_DirectX()
		{
			Purge();
		}

		std::uint32_t TextureLoader_DirectX::GetTexture(const std::string& pTextureFilePath, bool pForceLoad)
		{
			// TODO : Load texture using DirectX
			return 0U;
		}

		void TextureLoader_DirectX::Purge()
		{
			// TODO : delete texture form GPU
			mTextureBank.Clear();
		}
	}
}