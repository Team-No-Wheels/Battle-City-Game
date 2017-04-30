#include "Pch.h"
#include "TextureLoaderDirectX.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		TextureLoaderDirectX::TextureLoaderDirectX(IDirect3DDevice9& pD3DDevice) :
			TextureLoaderService(), mD3DDevice(&pD3DDevice)
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
			// Load image from file
			IDirect3DTexture9 *d3dTexture;
			if (D3DXCreateTextureFromFile(mD3DDevice, pTextureFilePath.c_str(), d3dTexture) < 0)
			{
				return nullptr;
			}

			return nullptr;
		}

		void TextureLoaderDirectX::Purge()
		{
			// TODO : delete texture form GPU
			mTextureBank.Clear();
		}
	}
}