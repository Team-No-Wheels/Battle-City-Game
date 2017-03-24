#include "ScopeParseHelper.h"
#include "ScopeSharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(ScopeParseHelper)

		const HashMap<std::string, ScopeParseHelper::StartHandlerFunction> ScopeParseHelper::StartElementHandlers = {
			{"integer", HandleIntegerStart},
			{"float", HandleFloatStart},
			{"string", HandleStringStart},
			{"vector", HandleVectorStart},
			{"matrix", HandleMatrixStart},
			{"scope", HandleScopeStart}
		};

		const HashMap<std::string, ScopeParseHelper::EndHandlerFunction> ScopeParseHelper::EndElementHandlers = {
			{"integer", HandleCommonEnd},
			{"float", HandleCommonEnd},
			{"string", HandleCommonEnd},
			{"vector", HandleCommonEnd},
			{"matrix", HandleMatrixEnd},
			{"scope", HandleScopeEnd}
		};

		const std::string ScopeParseHelper::NAME = "name";
		const std::string ScopeParseHelper::VALUE = "value";
		const std::string ScopeParseHelper::VECTOR_X = "x";
		const std::string ScopeParseHelper::VECTOR_Y = "y";
		const std::string ScopeParseHelper::VECTOR_Z = "z";
		const std::string ScopeParseHelper::VECTOR_W = "w";

		IXmlParserHelper* ScopeParseHelper::Clone()
		{
			ScopeParseHelper* helper = new ScopeParseHelper();
			return helper;
		}

		bool ScopeParseHelper::StartElementHandler(SharedData& sharedData, const std::string& name, const AttributeMap& attributes)
		{
			if (!sharedData.Is(ScopeSharedData::TypeIdClass()) || !StartElementHandlers.ContainsKey(name))
			{
				return false;
			}
			sharedData.IncrementDepth();
			ScopeSharedData& data = *(sharedData.As<ScopeSharedData>());
			StartElementHandlers[name](*this, data, attributes);
			return true;
		}

		bool ScopeParseHelper::EndElementHandler(SharedData& sharedData, const std::string& name)
		{
			if (!sharedData.Is(ScopeSharedData::TypeIdClass()) || !StartElementHandlers.ContainsKey(name))
			{
				return false;
			}
			ScopeSharedData& data = *(sharedData.As<ScopeSharedData>());
			EndElementHandlers[name](*this, data);
			sharedData.DecrementDepth();
			return true;
		}

		void ScopeParseHelper::HandleIntegerStart(ScopeParseHelper&, ScopeSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			Datum& datum = sharedData.mScope->Append(attributes[NAME]);
			if (attributes.ContainsKey(VALUE))
			{
				datum.PushBack(std::stoi(attributes[VALUE]));
			}
		}

		void ScopeParseHelper::HandleFloatStart(ScopeParseHelper&, ScopeSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			Datum& datum = sharedData.mScope->Append(attributes[NAME]);
			if (attributes.ContainsKey(VALUE))
			{
				datum.PushBack(std::stof(attributes[VALUE]));
			}
		}

		void ScopeParseHelper::HandleStringStart(ScopeParseHelper&, ScopeSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			Datum& datum = sharedData.mScope->Append(attributes[NAME]);
			if (attributes.ContainsKey(VALUE))
			{
				datum.PushBack(attributes[VALUE]);
			}
		}

		void ScopeParseHelper::HandleVectorStart(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			if (attributes.ContainsKey(VECTOR_X) && attributes.ContainsKey(VECTOR_Y) && attributes.ContainsKey(VECTOR_Z) && attributes.ContainsKey(VECTOR_W))
			{
				Datum datum;
				datum.SetType(Datum::DatumType::Vector);
				std::string toParse = attributes[VECTOR_X];
				toParse.append(attributes[VECTOR_Y]).append(",");
				toParse.append(attributes[VECTOR_Z]).append(",");
				toParse.append(attributes[VECTOR_W]);
				datum.SetFromString(toParse);

				if (helper.mMatrixName.empty())
				{
					sharedData.mScope->Append(attributes[NAME]) = std::move(datum);
				}
				else
				{
					helper.mMatrixVectors.PushBack(datum);
				}
			}
		}

		void ScopeParseHelper::HandleMatrixStart(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			sharedData.mScope->Append(attributes[NAME]);
			helper.mMatrixName = attributes[NAME];
		}

		void ScopeParseHelper::HandleScopeStart(ScopeParseHelper&, ScopeSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			if (sharedData.mScope == nullptr)
			{
				sharedData.mScope = new Scope();
			}
			else
			{
				Scope& scope = sharedData.mScope->AppendScope(attributes[NAME]);
				sharedData.mScope = &scope;
			}
		}

		void ScopeParseHelper::HandleCommonEnd(ScopeParseHelper&, ScopeSharedData&)
		{
			// do nothing for now
		}

		void ScopeParseHelper::HandleMatrixEnd(ScopeParseHelper& helper, ScopeSharedData& sharedData)
		{
			sharedData.mScope->Append(helper.mMatrixName) = glm::mat4(helper.mMatrixVectors[0].Get<glm::vec4>(),
				helper.mMatrixVectors[1].Get<glm::vec4>(), helper.mMatrixVectors[2].Get<glm::vec4>(), helper.mMatrixVectors[3].Get<glm::vec4>());
			helper.mMatrixName.clear();
		}

		void ScopeParseHelper::HandleScopeEnd(ScopeParseHelper&, ScopeSharedData& sharedData)
		{
			sharedData.mScope = const_cast<Scope*>(sharedData.mScope->GetParent());
		}

		void ScopeParseHelper::ValidateRequiredAttributes(const AttributeMap& attributes)
		{
			if (!attributes.ContainsKey(NAME))
			{
				throw std::runtime_error("Name is a required attribute");
			}
		}
	}
}
