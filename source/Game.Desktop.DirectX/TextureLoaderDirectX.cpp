#include "Pch.h"
#include "TextureLoaderDirectX.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		TextureLoaderDirectX::TextureLoaderDirectX() :
			TextureLoaderService()
		{

		}

		TextureLoaderDirectX::~TextureLoaderDirectX()
		{
			Purge();
		}

		Texture* TextureLoaderDirectX::GetTexture(const std::string& pTextureFilePath, bool pForceLoad)
		{
			pTextureFilePath;
			pForceLoad;
			// TODO : Load texture using DirectX
			return nullptr;
		}

		void TextureLoaderDirectX::Purge()
		{
			// TODO : delete texture form GPU
			mTextureBank.Clear();
		}
	}
}