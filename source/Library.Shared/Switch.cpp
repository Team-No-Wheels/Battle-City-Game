
#include "Switch.h"
#include "RpnEvaluator.h"
#include "InfixParser.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Switch)

		Switch::Switch(const std::string& name) :
			ActionList(name), mDefaultCase()
		{
			AddExternalAttribute("Expression", &mExpression, 1);
			AddDatumAttribute("DefaultCase", mDefaultCase);
		}

		void Switch::Update(WorldState& worldState)
		{
			worldState.mAction = this;

			Parsers::InfixParser parser;
			Parsers::RpnEvaluator evaluator;
			Datum datum;
			evaluator.EvaluateRPN(parser.ConvertToRPN(mExpression), *this, datum);

			if (datum != nullptr && datum.Size() > 0)
			{
				bool foundCase = false;
				for (std::uint32_t index = 0; index < mActions->Size(); ++index)
				{
					assert(mActions->Get<Scope>(index).Is(Action::TypeIdClass()));
					Action& action = static_cast<Action&>(mActions->Get<Scope>(index));
					
					// create a datum from the case to compare against
					Datum caseValue;
					caseValue.SetType(datum.Type());
					caseValue.Resize(1U);
					caseValue.SetFromString(action.Name());

					if (caseValue == datum)
					{
						foundCase = true;
						action.Update(worldState);
						break;
					}
				}

				if (!foundCase && mDefaultCase->Size() > 0)
				{
					assert(mDefaultCase->Get<Scope>().Is(Action::TypeIdClass()));
					Action& action = static_cast<Action&>(mDefaultCase->Get<Scope>());
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
