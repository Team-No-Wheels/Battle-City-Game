#include "Pch.h"
#include "TileBase.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(TileBase)

		TileBase::TileBase(TileType tileType) :
			mTileType(tileType)
		{
		}

		void TileBase::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}
