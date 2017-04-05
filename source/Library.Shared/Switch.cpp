
#include "Switch.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		Switch::Switch(const std::string& name) :
			ActionList(name), mDefaultCase()
		{
			AddExternalAttribute("Expression", &mExpression, 1);
			AddDatumAttribute("DefaultCase", mDefaultCase);
		}

		void Switch::Update(WorldState& worldState)
		{
			worldState.mAction = this;

			//TODO: evaluate expression
			const std::string& mEvaluated = mExpression;
			Datum* datum = Search(mEvaluated);

			if (datum != nullptr && datum->Size() > 0)
			{
				const std::string& value = datum->ToString();
				bool foundCase = false;
				for (std::uint32_t index = 0; index < mActions->Size(); ++index)
				{
					assert(mActions->Get<Scope>(index).Is(Action::TypeIdClass()));
					Action& action = static_cast<Action&>(mActions->Get<Scope>(index));
					if (action.Name() == value)
					{
						foundCase = true;
						action.Update(worldState);
						break;
					}
				}

				if (!foundCase && mDefaultCase != nullptr)
				{
					assert(mDefaultCase->Get<Scope>().Is(Action::TypeIdClass()));
					Action& action = static_cast<Action&>(mActions->Get<Scope>());
					action.Update(worldState);
				}
			}
			worldState.mAction = nullptr;
		}

		void Switch::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Expression");
			prescribedAttributeNames.PushBack("DefaultCase");
		}

		ACTION_FACTORY_DEFINITIONS(Switch)
	}
}
