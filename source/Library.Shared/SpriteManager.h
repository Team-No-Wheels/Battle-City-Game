#pragma once
#include "Entity.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		typedef AnonymousEngine::Containers::Entity Entity;

		class SpriteManager :public Entity
		{
			ATTRIBUTED_DECLARATIONS(SpriteManager, Entity)
		public:
			SpriteManager();

			~SpriteManager() = default;

		private:
			std::string mSpriteSheetName;

			static const std::string sSpriteSheetAttributeName;
		};

		ENTITY_FACTORY_DECLARATIONS(SpriteManager)
	}
}