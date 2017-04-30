#include "Pch.h"
#include "Sprite.h"
#include "ServiceLocator.h"
#include "Rectangle.h"


//#include "TextureLoader.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		ATTRIBUTED_DEFINITIONS(Sprite)
		ENTITY_FACTORY_DEFINITIONS(Sprite);

		Sprite::Sprite() :
			Renderable(), isInitialized(false)
		{

		}


		void Sprite::Init(const std::string& pSpriteFilePath)
		{
			Renderable::Init(pSpriteFilePath);
			TextureLoaderService* loader = Core::ServiceLocator::GetTextureLoader();
			mTexture = loader->GetTexture(pSpriteFilePath);

			mHeight = 100;
			mWidth = 50;

			//glClearColor(backRed, backGreen, backGreen, 0.0f);			// Background Color
			glClearDepth(1.0f);											// Depth Buffer Setup

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
			glEnable(GL_BLEND);											// Enable Blending
			glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
			glEnable(GL_CULL_FACE);										// Remove Back Face
			//glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);										// Type Of Depth Testing
		}

		void Sprite::Update(float pDeltaTime)
		{
			Renderable::Update(pDeltaTime);
		}

		void Sprite::Render()
		{
			if (isInitialized)
			{
				Geometry::Rectangle uv(0, 1, 1, 1, 0, 0, 1, 0);
				Geometry::Rectangle position(-100 + 400, 100 + 400,
					100 + 400, 100 + 400,
					-100 + 400, -100 + 400,
					100 + 400, -100 + 400);

				Core::ServiceLocator::GetRenderer()->Render(mTexture, position, uv);


#ifdef _DEBUG
				DrawDebugBounds();
#endif 
			}
		}

		void Sprite::DrawDebugBounds()
		{
			Geometry::Rectangle position(-100 + 400, 100 + 400, 
				100 + 400, 100 + 400, 
				-100 + 400, -100 + 400, 
				100 + 400, -100 + 400);
			Core::ServiceLocator::GetRenderer()->DrawRectangle(position, 255, 0, 0);
		}

		void Sprite::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}