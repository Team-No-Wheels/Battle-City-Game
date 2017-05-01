#include "Pch.h"
#include "Grass.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(Grass)
		ENTITY_FACTORY_DEFINITIONS(Grass)

		Grass::Grass() :
			TileBase(TileType::GRASS)
		{
			GetCollider().SetTag(AnonymousEngine::Core::Collider::ColliderTag::Grass);
		}

		void Grass::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);			
		}
	}
}