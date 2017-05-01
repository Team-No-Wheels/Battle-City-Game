#include "Pch.h"
#include "Sprite.h"
#include "ServiceLocator.h"
#include "GameObject.h"

#define DEGREE_TO_RAD 0.0174533f

namespace AnonymousEngine
{
	namespace Graphics
	{
		Sprite::Sprite(Core::GameObject& pGameObject) : 
			mGameObject(pGameObject), mUVBounds(0, 0, 1, 0, 0, 1, 1, 1)
		{
			mGameObject.SetSprite(*this);
			mRotationBuffer = mGameObject.GetRotation();

			mGameObject.AddExternalAttribute(Core::GameObject::sWidthAttributeName, &mWidth, 1);
			mGameObject.AddExternalAttribute(Core::GameObject::sHeightAttributeName, &mHeight, 1);
		}


		void Sprite::Init(const std::string& pSpriteFilePath)
		{
			Renderable::Init(pSpriteFilePath);
			TextureLoaderService* loader = Core::ServiceLocator::GetTextureLoader();
			mTexture = loader->GetTexture(pSpriteFilePath);

			mHeight = 15;
			mWidth = 15;

			mSpriteBounds.TopLeft.x = 0.0f;
			mSpriteBounds.TopLeft.y = (float)mHeight;

			mSpriteBounds.TopRight.x = (float)mWidth;
			mSpriteBounds.TopRight.y = (float)mHeight;

			mSpriteBounds.BottomLeft.x = 0.0f;
			mSpriteBounds.BottomLeft.y = 0.0f;

			mSpriteBounds.BottomRight.x = (float)mWidth;
			mSpriteBounds.BottomRight.y = 0.0f;

			mRenderingBounds = mSpriteBounds;
		}

		void Sprite::Update(float pDeltaTime)
		{
			Renderable::Update(pDeltaTime);
		}

		void Sprite::Render() const
		{
			if (isInitialized)
			{
				Core::ServiceLocator::GetRenderer()->Render(*this);

#ifdef _DEBUG
				DrawDebugBounds();
#endif 
			}
		}

		void Sprite::DrawDebugBounds() const
		{
			Core::ServiceLocator::GetRenderer()->DrawRectangle(mRenderingBounds, 255, 0, 0);
		}

		Core::GameObject& Sprite::GetOwner() const
		{
			return mGameObject;
		}

		Geometry::Rectangle Sprite::GetSpriteBounds() const
		{
			// translate the bounds to sprite position
			return mSpriteBounds;
		}

		Geometry::Rectangle Sprite::GetRenderingBounds() const
		{
			return mRenderingBounds;
		}



		const Geometry::Rectangle& Sprite::GetUVBounds() const
		{
			return mUVBounds;
		}

		void Sprite::UpdatePosition()
		{
			glm::vec4 translationValue = GetOwner().GetPosition() - glm::vec4(GetWidth() / 2.0f, GetHeight() / 2.0f, 0.0f, 0.0f);
			mRenderingBounds = Geometry::Rectangle::Translate(mSpriteBounds, translationValue);
		}

		void Sprite::UpdateRotation()
		{
			glm::vec2 pivotPoint = glm::vec2(mGameObject.GetPosition().x, mGameObject.GetPosition().y);
			//glm::vec2 pivotPoint = glm::vec2(mWidth / 2.0f, mHeight / 2.0f);

			float offset = mGameObject.GetRotation() - mRotationBuffer;

			if (offset != 0.0f)
			{
				mRenderingBounds.TopLeft = RotatePoint(pivotPoint, mRenderingBounds.TopLeft, offset);
				mRenderingBounds.TopRight = RotatePoint(pivotPoint, mRenderingBounds.TopRight, offset);
				mRenderingBounds.BottomLeft = RotatePoint(pivotPoint, mRenderingBounds.BottomLeft, offset);
				mRenderingBounds.BottomRight = RotatePoint(pivotPoint, mRenderingBounds.BottomRight, offset);
			}
			
			mRotationBuffer = mGameObject.GetRotation();
		}

		glm::vec2 Sprite::RotatePoint(glm::vec2 pOriginPoint, glm::vec2 pPoint, float_t pAngle)
		{
			float_t sinValue = (float_t)sin(pAngle * DEGREE_TO_RAD);
			float_t cosValue = (float_t)cos(pAngle * DEGREE_TO_RAD);

			// translate point back to origin:
			pPoint.x -= pOriginPoint.x;
			pPoint.y -= pOriginPoint.y;

			// rotate point
			double xnew = pPoint.x * cosValue - pPoint.y * sinValue;
			double ynew = pPoint.x * sinValue + pPoint.y * cosValue;

			// translate point back:
			pPoint.x = (float)(xnew + pOriginPoint.x);
			pPoint.y = (float)(ynew + pOriginPoint.y);

			return pPoint;
		}
	}
}