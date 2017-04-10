#include "SetValue.h"
#include "RpnEvaluator.h"
#include "InfixParser.h"

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
			Parsers::InfixParser parser;
			Parsers::RpnEvaluator evaluator;

			Datum& foundDatum = *(GetParent()->Search(mTarget));
			if (foundDatum != nullptr && static_cast<std::int32_t>(foundDatum.Size()) > mIndex)
			{
				Datum datum;
				evaluator.EvaluateRPN(parser.ConvertToRPN(mValue), *this, datum);
				switch(datum.Type())
				{
				case Datum::DatumType::Integer:
					foundDatum.Set(datum.Get<std::int32_t>());
					break;
				case Datum::DatumType::Float:
					foundDatum.Set(datum.Get<float>());
					break;
				case Datum::DatumType::String:
					foundDatum.Set(datum.Get<std::string>());
					break;
				case Datum::DatumType::Vector:
					foundDatum.Set(datum.Get<glm::vec4>());
					break;
				case Datum::DatumType::Matrix:
					foundDatum.Set(datum.Get<glm::mat4>());
					break;
				case Datum::DatumType::Scope:
					foundDatum.Set(datum.Get<Scope>());
					break;
				case Datum::DatumType::RTTI:
					break;
				default:
					break;
				}
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
