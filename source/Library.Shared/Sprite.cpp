#include "Pch.h"
#include "Sprite.h"
//#include "TextureLoader.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		ATTRIBUTED_DEFINITIONS(Sprite)
		ENTITY_FACTORY_DEFINITIONS(Sprite);

		Sprite::Sprite() :
			Renderable()
		{

		}


		void Sprite::Init(const std::string& pSpriteFilePath)
		{
			Renderable::Init(pSpriteFilePath);

			//mTextureID = TextureLoader::GetTexture(pSpriteFilePath);

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
			// Clear the window
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			// Set the modelview matrix to be the identity matrix
			//glLoadIdentity();


			glColor3f(1, 1, 1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, mTextureID);


			// Draw a textured quad
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-100, -100, 0);
			glTexCoord2f(0, 1); glVertex3f(-100, 100, 0);
			glTexCoord2f(1, 1); glVertex3f(100, 100, 0);
			glTexCoord2f(1, 0); glVertex3f(100, -100, 0);
			glEnd();

			glLineWidth(10);
			// Draw filtered lines
			glEnable(GL_LINE_SMOOTH);
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_LINE_STRIP);

			glColor3ub(200, 200, 255);
			glVertex3f(-100000, -100000, 0.0f);
			glVertex3f(100000, 100000, 0.0f);

			glEnd();

			//glFlush();

#ifdef _DEBUG
			DrawDebugBounds();
#endif 

		}

		void Sprite::DrawDebugBounds()
		{
		}

		void Sprite::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}