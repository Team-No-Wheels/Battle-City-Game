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
			HashMap<std::string, Texture*>::Iterator itr = mTextureBank.Find(pTextureFilePath);
			// search if the texture is already loaded before and if not force load
			if (itr != mTextureBank.end() && !pForceLoad)
			{
				return itr->second;
			}

			// load the texture and then save the texture in the bank
			IDirect3DTexture9 *d3dTexture = nullptr;
			HRESULT result;
			result = mD3DDevice->CreateTexture(128, 128, 0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &d3dTexture, nullptr);

			if (result < 0)
			{
				// if unable to load the texture.
				return nullptr;
			}
			
			/*switch (result)
			{
			case D3D_OK: MessageBox(NULL, L"Success", NULL, NULL); break;
			case D3DERR_INVALIDCALL: MessageBox(NULL, L"D3D - Invalid call", NULL, NULL); break;
			case D3DERR_NOTAVAILABLE: MessageBox(NULL, L"D3D - Not available", NULL, NULL); break;
			case D3DERR_OUTOFVIDEOMEMORY: MessageBox(NULL, L"D3D - Out of video memory", NULL, NULL); break;
			//case D3DXERR_INVALIDDATA: MessageBox(NULL, L"D3DX - Invalid data", NULL, NULL); break;
			case E_OUTOFMEMORY: MessageBox(NULL, L"E - Out of memory", NULL, NULL); break;
			}*/

			TextureDirectX* newTexture = new TextureDirectX;
			newTexture->mTextureID = d3dTexture;

			mTextureBank[pTextureFilePath] = newTexture;
			return newTexture;
		}

		void TextureLoaderDirectX::Purge()
		{
			// delete textures from GPU.
			for (std::pair<std::string, Texture*> element : mTextureBank)
			{
				TextureDirectX* texture = static_cast<TextureDirectX*>(element.second);
				//texture->mTextureID->Release();

				// cleaning house
				delete texture;
			}
			mTextureBank.Clear();
		}
	}
}