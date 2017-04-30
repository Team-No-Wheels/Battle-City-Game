#include "Pch.h"
#include "Flag.h"

namespace BattleCity
{
	namespace MapEntities
	{
		ATTRIBUTED_DEFINITIONS(Flag)
		ENTITY_FACTORY_DEFINITIONS(Flag)

		void Flag::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}