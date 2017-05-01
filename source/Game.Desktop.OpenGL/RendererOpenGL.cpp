#include "Pch.h"
#include "RendererOpenGL.h"
#include "GameObject.h"
#include "TextureLoaderOpenGL.h"
#include "Color.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		RendererOpenGL::RendererOpenGL()
		{}

		RendererOpenGL::~RendererOpenGL()
		{}

		void RendererOpenGL::Render(const Sprite& pSprite) const
		{
			TextureOpenGL* openglTex = static_cast<TextureOpenGL*>(pSprite.GetTexture());
			const Geometry::Rectangle& uvBounds = pSprite.GetUVBounds();
			Geometry::Rectangle spriteBounds = pSprite.GetRenderingBounds();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, openglTex->mTextureID);
			
			glBegin((GLenum)GL_QUADS);
				Color tint = pSprite.GetTint();
				// tint
				glColor4ub((GLubyte)tint.r, (GLubyte)tint.g, (GLubyte)tint.b, (GLubyte)255);

				// top left
				glTexCoord2f(uvBounds.TopLeft.x, uvBounds.TopLeft.y);
				glVertex3f(spriteBounds.TopLeft.x, spriteBounds.TopLeft.y, 0.0f);

				// top right
				glTexCoord2f(uvBounds.TopRight.x, uvBounds.TopRight.y);
				glVertex3f(spriteBounds.TopRight.x, spriteBounds.TopRight.y, 0.0f);

				// bottom right
				glTexCoord2f(uvBounds.BottomRight.x, uvBounds.BottomRight.y);
				glVertex3f(spriteBounds.BottomRight.x, spriteBounds.BottomRight.y, 0.0f);

				// bottom left
				glTexCoord2f(uvBounds.BottomLeft.x, uvBounds.BottomLeft.y);
				glVertex3f(spriteBounds.BottomLeft.x, spriteBounds.BottomLeft.y, 0.0f);

				

				

				

				

			glEnd();
		}

		void RendererOpenGL::DrawRectangle(const Geometry::Rectangle& pRectangle, unsigned char pRed, unsigned char pGreen, unsigned char pBlue) const
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