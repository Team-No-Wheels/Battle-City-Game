#include "Pch.h"
#include "Flag.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(Flag)
		ENTITY_FACTORY_DEFINITIONS(Flag)

		Flag::Flag() :
			TileBase(TileType::FLAG)
		{
			GetCollider().SetTag(AnonymousEngine::Core::Collider::ColliderTag::Flag);
		}

		void Flag::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}