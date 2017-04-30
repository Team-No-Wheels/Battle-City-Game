#include "Pch.h"
#include "Rectangle.h"

namespace AnonymousEngine
{
	namespace Geometry
	{
		Rectangle::Rectangle()
		{
			TopLeft.x = 0.0f;
			TopLeft.y = 0.0f;

			TopRight.x = 1.0f;
			TopRight.y = 0.0f;

			BottomLeft.x = 0.0f;
			BottomLeft.y = 1.0f;

			BottomRight.x = 1.0f;
			BottomRight.y = 1.0f;
		}

		Rectangle::Rectangle(glm::vec2 pTopLeft, glm::vec2 pTopRight, glm::vec2 pBottomLeft, glm::vec2 pBottomRight) :
			TopLeft(pTopLeft), TopRight(pTopRight), BottomLeft(pBottomLeft), BottomRight(pBottomRight)
		{

		}

		Rectangle::Rectangle(float pTopLeftX, float pTopLeftY, float pTopRightX, float pTopRightY, float pBottomLeftX, float pBottomLeftY, float pBottomRightX, float pBottomRightY)
		{
			TopLeft.x = pTopLeftX;
			TopLeft.y = pTopLeftY;

			TopRight.x = pTopRightX;
			TopRight.y = pTopRightY;

			BottomLeft.x = pBottomLeftX;
			BottomLeft.y = pBottomLeftY;

			BottomRight.x = pBottomRightX;
			BottomRight.y = pBottomRightY;
		}
	}
}