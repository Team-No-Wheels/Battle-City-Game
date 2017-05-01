#include "Pch.h"
#include "TileBase.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(TileBase)
		ENTITY_FACTORY_DEFINITIONS(TileBase)		

		void TileBase::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}

		void TileBase::SetTileType(TileType tileType)
		{
			mTileType = tileType;
		}
	}
}
