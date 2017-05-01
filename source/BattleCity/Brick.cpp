#include "Pch.h"
#include "Brick.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(Brick)
		ENTITY_FACTORY_DEFINITIONS(Brick)

		Brick::Brick() :
			TileBase(TileType::BRICK)
		{
		}

		void Brick::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}