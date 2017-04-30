#include "Pch.h"
#include "RendererOpenGL.h"
#include "TextureLoaderOpenGL.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		RendererOpenGL::RendererOpenGL()
		{}

		RendererOpenGL::~RendererOpenGL()
		{}

		void RendererOpenGL::Render(Texture* pTexture, const Geometry::Rectangle& pSpriteBounds, const Geometry::Rectangle& pUVBounds)
		{
			TextureOpenGL* openglTex = static_cast<TextureOpenGL*>(pTexture);
			
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, openglTex->mTextureID);
			
			glBegin((GLenum)GL_QUADS);

				// tint
				glColor4ub((GLubyte)255, (GLubyte)255, (GLubyte)255, (GLubyte)255);

				// bottom left
				glTexCoord2f(pUVBounds.BottomLeft.x, pUVBounds.BottomLeft.y);
				glVertex3f(pSpriteBounds.BottomLeft.x, pSpriteBounds.BottomLeft.y, 0.0f);

				// bottom right
				glTexCoord2f(pUVBounds.BottomRight.x, pUVBounds.BottomRight.y);
				glVertex3f(pSpriteBounds.BottomRight.x, pSpriteBounds.BottomRight.y, 0.0f);

				// top right
				glTexCoord2f(pUVBounds.TopRight.x, pUVBounds.TopRight.y);
				glVertex3f(pSpriteBounds.TopRight.x, pSpriteBounds.TopRight.y, 0.0f);

				// top left
				glTexCoord2f(pUVBounds.TopLeft.x, pUVBounds.TopLeft.y);
				glVertex3f(pSpriteBounds.TopLeft.x, pSpriteBounds.TopLeft.y, 0.0f);

				// bottom left
				glTexCoord2f(pUVBounds.BottomLeft.x, pUVBounds.BottomLeft.y);
				glVertex3f(pSpriteBounds.BottomLeft.x, pSpriteBounds.BottomLeft.y, 0.0f);

			glEnd();
		}

		void RendererOpenGL::DrawRectangle(const Geometry::Rectangle& pRectangle, unsigned char pRed, unsigned char pGreen, unsigned char pBlue)
		{
			glLineWidth(1);
			
			// Draw filtered lines
			glEnable(GL_LINE_SMOOTH);
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_LINE_STRIP);
				glColor3ub(pRed, pGreen, pBlue);
				// draw the bounds
				glVertex3f(pRectangle.TopLeft.x, pRectangle.TopLeft.y, 99.0f);
				glVertex3f(pRectangle.TopRight.x, pRectangle.TopRight.y, 99.0f);

				glVertex3f(pRectangle.TopRight.x, pRectangle.TopRight.y, 99.0f);
				glVertex3f(pRectangle.BottomRight.x, pRectangle.BottomRight.y, 99.0f);

				glVertex3f(pRectangle.BottomRight.x, pRectangle.BottomRight.y, 99.0f);
				glVertex3f(pRectangle.BottomLeft.x, pRectangle.BottomLeft.y, 99.0f);

				glVertex3f(pRectangle.BottomLeft.x, pRectangle.BottomLeft.y, 99.0f);
				glVertex3f(pRectangle.TopLeft.x, pRectangle.TopLeft.y, 99.0f);

			glEnd();
		}
	}
}