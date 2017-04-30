#include "Pch.h"
#include "Grass.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(Grass)
		ENTITY_FACTORY_DEFINITIONS(Grass)

		void Grass::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);			
		}
	}
}