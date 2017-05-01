#pragma once
#include "Entity.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		class Frame : public Containers::Entity
		{
			ATTRIBUTED_DECLARATIONS(Frame, Entity)
		public:
			/**
				Default constructor.
			*/
			Frame();

			/**
				Prescribed attributes
			*/
			int mFrameID;
			std::string mFrameName;
			std::string mFilePath;
			glm::vec4 mPosition;
			int width, height;
		};

		ENTITY_FACTORY_DECLARATIONS(Frame);
	}
}