#include "SetValue.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(SetValue)

		SetValue::SetValue(const std::string& name) :
			Action(name), mIndex(0)
		{
			AddExternalAttribute("Target", &mTarget, 1);
			AddExternalAttribute("Value", &mValue, 1);
			AddExternalAttribute("Index", &mIndex, 1);
		}

		void SetValue::Update(WorldState& worldState)
		{
			worldState.mAction = this;
			Datum* foundDatum = GetParent()->Search(mTarget);
			if (foundDatum != nullptr && static_cast<std::int32_t>(foundDatum->Size()) > mIndex)
			{
				foundDatum->SetFromString(mValue, mIndex);
			}
			worldState.mAction = nullptr;
		}

		void SetValue::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Target");
			prescribedAttributeNames.PushBack("Value");
			prescribedAttributeNames.PushBack("Index");
		}

		ACTION_FACTORY_DEFINITIONS(SetValue)
	}
}
