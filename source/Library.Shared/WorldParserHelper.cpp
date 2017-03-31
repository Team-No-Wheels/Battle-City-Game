#include "WorldParserHelper.h"
#include "WorldSharedData.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		using namespace AnonymousEngine::Containers;

		RTTI_DEFINITIONS(WorldParserHelper)

			const HashMap<std::string, WorldParserHelper::StartHandlerFunction> WorldParserHelper::StartElementHandlers = {
				{"integer", HandleIntegerStart},
				{"float", HandleFloatStart},
				{"string", HandleStringStart},
				{"vector", HandleVectorStart},
				{"matrix", HandleMatrixStart},
				{"scope", HandleScopeStart}
		};

		const HashMap<std::string, WorldParserHelper::EndHandlerFunction> WorldParserHelper::EndElementHandlers = {
			{"integer", HandleCommonEnd},
			{"float", HandleCommonEnd},
			{"string", HandleCommonEnd},
			{"vector", HandleCommonEnd},
			{"matrix", HandleMatrixEnd},
			{"scope", HandleScopeEnd}
		};

		const std::string WorldParserHelper::ROOT_TAG = "scope";
		const std::string WorldParserHelper::NAME = "name";
		const std::string WorldParserHelper::VALUE = "value";
		const std::string WorldParserHelper::VECTOR_X = "x";
		const std::string WorldParserHelper::VECTOR_Y = "y";
		const std::string WorldParserHelper::VECTOR_Z = "z";
		const std::string WorldParserHelper::VECTOR_W = "w";

		IXmlParserHelper* WorldParserHelper::Clone()
		{
			WorldParserHelper* helper = new WorldParserHelper();
			return helper;
		}

		bool WorldParserHelper::StartElementHandler(SharedData& sharedData, const std::string& name, const AttributeMap& attributes)
		{
			if (!sharedData.Is(WorldSharedData::TypeIdClass()) || !StartElementHandlers.ContainsKey(name))
			{
				return false;
			}

			if (sharedData.Depth() == 1 && name != ROOT_TAG)
			{
				throw std::runtime_error("Invalid root tag");
			}

			WorldSharedData& data = *(sharedData.As<WorldSharedData>());
			StartElementHandlers[name](*this, data, attributes);
			return true;
		}

		bool WorldParserHelper::EndElementHandler(SharedData& sharedData, const std::string& name)
		{
			if (!sharedData.Is(WorldSharedData::TypeIdClass()) || !StartElementHandlers.ContainsKey(name))
			{
				return false;
			}
			WorldSharedData& data = *(sharedData.As<WorldSharedData>());
			EndElementHandlers[name](*this, data);
			return true;
		}

		void WorldParserHelper::HandleIntegerStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			Datum& datum = sharedData.mWorld->Append(attributes[NAME]);
			if (attributes.ContainsKey(VALUE))
			{
				datum.PushBack(std::stoi(attributes[VALUE]));
			}
		}

		void WorldParserHelper::HandleFloatStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			Datum& datum = sharedData.mWorld->Append(attributes[NAME]);
			if (attributes.ContainsKey(VALUE))
			{
				datum.PushBack(std::stof(attributes[VALUE]));
			}
		}

		void WorldParserHelper::HandleStringStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			Datum& datum = sharedData.mWorld->Append(attributes[NAME]);
			if (attributes.ContainsKey(VALUE))
			{
				datum.PushBack(attributes[VALUE]);
			}
		}

		void WorldParserHelper::HandleVectorStart(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			if (attributes.ContainsKey(VECTOR_X) && attributes.ContainsKey(VECTOR_Y) && attributes.ContainsKey(VECTOR_Z) && attributes.ContainsKey(VECTOR_W))
			{
				Datum datum;
				datum.SetType(Datum::DatumType::Vector);
				std::string toParse = attributes[VECTOR_X];
				toParse.append(",");
				toParse.append(attributes[VECTOR_Y]).append(",");
				toParse.append(attributes[VECTOR_Z]).append(",");
				toParse.append(attributes[VECTOR_W]);
				datum.Resize(1U);
				datum.SetFromString(toParse);

				if (helper.mMatrixName.empty())
				{
					sharedData.mWorld->Append(attributes[NAME]).PushBack(datum.Get<glm::vec4>());
				}
				else
				{
					helper.mMatrixVectors.PushBack(datum);
				}
			}
		}

		void WorldParserHelper::HandleMatrixStart(WorldParserHelper& helper, WorldSharedData&, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			helper.mMatrixName = attributes[NAME];
		}

		void WorldParserHelper::HandleScopeStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			if (sharedData.mWorld == nullptr)
			{
				sharedData.mWorld = new World(attributes["name"]);
			}
			else
			{
				World& world = static_cast<World&>(sharedData.mWorld->AppendScope(attributes[NAME]));
				sharedData.mWorld = &world;
			}
		}

		void WorldParserHelper::HandleCommonEnd(WorldParserHelper&, WorldSharedData&)
		{
			// do nothing for now
		}

		void WorldParserHelper::HandleMatrixEnd(WorldParserHelper& helper, WorldSharedData& sharedData)
		{
			sharedData.mWorld->Append(helper.mMatrixName).PushBack(glm::mat4(helper.mMatrixVectors[0].Get<glm::vec4>(),
				helper.mMatrixVectors[1].Get<glm::vec4>(), helper.mMatrixVectors[2].Get<glm::vec4>(), helper.mMatrixVectors[3].Get<glm::vec4>()));
			helper.mMatrixName.clear();
		}

		void WorldParserHelper::HandleScopeEnd(WorldParserHelper&, WorldSharedData& sharedData)
		{
			if (sharedData.Depth() > 1)
			{
				sharedData.mWorld = static_cast<World*>(sharedData.mWorld->GetParent());
			}
		}

		void WorldParserHelper::ValidateRequiredAttributes(const AttributeMap& attributes)
		{
			if (!attributes.ContainsKey(NAME))
			{
				throw std::runtime_error("Name is a required attribute");
			}
		}
	}
}
