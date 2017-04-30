#include "Pch.h"
#include "TextureLoaderDirectX.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		TextureLoaderDirectX::TextureLoaderDirectX()
		{

		}

		TextureLoaderDirectX::~TextureLoaderDirectX()
		{
			Purge();
		}

		std::uint32_t TextureLoaderDirectX::GetTexture(const std::string& pTextureFilePath, bool pForceLoad)
		{
			pTextureFilePath;
			pForceLoad;
			// TODO : Load texture using DirectX
			return 0U;
		}

		void TextureLoaderDirectX::Purge()
		{
			// TODO : delete texture form GPU
			mTextureBank.Clear();
		}
	}
}