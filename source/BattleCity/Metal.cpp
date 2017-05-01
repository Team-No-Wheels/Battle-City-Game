#include "Pch.h"
#include "Metal.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(Metal)
		ENTITY_FACTORY_DEFINITIONS(Metal)

		Metal::Metal() :
			TileBase(TileType::METAL)
		{
			GetCollider().SetTag(AnonymousEngine::Core::Collider::ColliderTag::MetalWall);
		}

		void Metal::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}