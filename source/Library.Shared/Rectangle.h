#pragma once
#include "glm/vec2.hpp"

namespace AnonymousEngine
{
	namespace Geometry
	{
		class Rectangle
		{
		public:
			glm::vec2 TopLeft;
			glm::vec2 TopRight;
			glm::vec2 BottomLeft;
			glm::vec2 BottomRight;

			/**
				Default constructor
			*/
			Rectangle();

			/**
				Parameter constructor.
			*/
			Rectangle(glm::vec2 pTopLeft, glm::vec2 pTopRight, glm::vec2 pBottomLeft, glm::vec2 pBottomRight);

			/**
				Parameter constructor.
			*/
			Rectangle(float pTopLeftX, float pTopLeftY, float pTopRightX, float pTopRightY, float pBottomLeftX, float pBottomLeftY, float pBottomRightX, float pBottomRightY);

			static Geometry::Rectangle Translate(Geometry::Rectangle pRectangle, const glm::vec4& pPosition);
		};
	}
}