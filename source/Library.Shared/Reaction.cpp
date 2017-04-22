#include "Reaction.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Reaction)

		Reaction::Reaction(const std::string& name) :
			ActionList(name)
		{
		}

		void Reaction::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Action::AppendPrescribedAttributeNames(prescribedAttributeNames);
		}
	}
}
