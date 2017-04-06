#include "Action.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Action)

		const std::string Action::ActionsAttributeName = "Actions";

		Action::Action(const std::string& name) :
			mName(name)
		{
			AddExternalAttribute("Name", &mName, 1);
		}

		std::string Action::Name() const
		{
			return mName;
		}

		void Action::SetName(const std::string& name)
		{
			mName = name;
		}

		void Action::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Name");
		}
	}
}
