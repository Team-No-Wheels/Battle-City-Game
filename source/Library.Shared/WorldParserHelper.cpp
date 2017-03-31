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
			{"world", HandleWorldStart},
			{"sectors", HandleListStart},
			{"sector", HandleSectorStart},
			{"entities", HandleListStart},
			{"entity", HandleEntityStart},
			{"actions", HandleListStart},
			{"action", HandleActionStart}
		};

		const HashMap<std::string, WorldParserHelper::EndHandlerFunction> WorldParserHelper::EndElementHandlers = {
			{"integer", HandleCommonEnd},
			{"float", HandleCommonEnd},
			{"string", HandleCommonEnd},
			{"vector", HandleCommonEnd},
			{"matrix", HandleMatrixEnd},
			{"world", HandleWorldEnd},
			{"sectors", HandleListEnd},
			{"sector", HandleSectorEnd},
			{"entities", HandleListEnd},
			{"entity", HandleEntityEnd},
			{"actions", HandleListEnd},
			{"action", HandleActionEnd}
		};

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

			mPreviousTagName = name;
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
			Datum& datum = sharedData.mAttributed->Append(attributes[NAME]);
			if (attributes.ContainsKey(VALUE))
			{
				datum.PushBack(std::stoi(attributes[VALUE]));
			}
		}

		void WorldParserHelper::HandleFloatStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			Datum& datum = sharedData.mAttributed->Append(attributes[NAME]);
			if (attributes.ContainsKey(VALUE))
			{
				datum.PushBack(std::stof(attributes[VALUE]));
			}
		}

		void WorldParserHelper::HandleStringStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			Datum& datum = sharedData.mAttributed->Append(attributes[NAME]);
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
					sharedData.mAttributed->Append(attributes[NAME]).PushBack(datum.Get<glm::vec4>());
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

		void WorldParserHelper::HandleWorldStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			if (sharedData.mAttributed == nullptr)
			{
				sharedData.mAttributed = new World(attributes["name"]);
			}
			else
			{
				World& world = static_cast<World&>(sharedData.mAttributed->AppendScope(attributes[NAME]));
				sharedData.mAttributed = &world;
			}
		}

		void WorldParserHelper::HandleSectorStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			if (sharedData.mAttributed == nullptr)
			{
				sharedData.mAttributed = new World(attributes["name"]);
			}
			else
			{
				World& world = static_cast<World&>(sharedData.mAttributed->AppendScope(attributes[NAME]));
				sharedData.mAttributed = &world;
			}
		}

		void WorldParserHelper::HandleEntityStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			if (sharedData.mAttributed == nullptr)
			{
				sharedData.mAttributed = new World(attributes["name"]);
			}
			else
			{
				World& world = static_cast<World&>(sharedData.mAttributed->AppendScope(attributes[NAME]));
				sharedData.mAttributed = &world;
			}
		}

		void WorldParserHelper::HandleActionStart(WorldParserHelper&, WorldSharedData& sharedData, const AttributeMap& attributes)
		{
			ValidateRequiredAttributes(attributes);
			if (sharedData.mAttributed == nullptr)
			{
				sharedData.mAttributed = new World(attributes["name"]);
			}
			else
			{
				World& world = static_cast<World&>(sharedData.mAttributed->AppendScope(attributes[NAME]));
				sharedData.mAttributed = &world;
			}
		}

		void WorldParserHelper::HandleListStart(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap&)
		{
			sharedData.mListTag = helper.mPreviousTagName;
		}

		void WorldParserHelper::HandleCommonEnd(WorldParserHelper&, WorldSharedData&)
		{
			// do nothing
		}

		void WorldParserHelper::HandleMatrixEnd(WorldParserHelper& helper, WorldSharedData& sharedData)
		{
			sharedData.mAttributed->Append(helper.mMatrixName).PushBack(glm::mat4(helper.mMatrixVectors[0].Get<glm::vec4>(),
				helper.mMatrixVectors[1].Get<glm::vec4>(), helper.mMatrixVectors[2].Get<glm::vec4>(), helper.mMatrixVectors[3].Get<glm::vec4>()));
			helper.mMatrixName.clear();
		}

		void WorldParserHelper::HandleWorldEnd(WorldParserHelper&, WorldSharedData& sharedData)
		{
			if (sharedData.Depth() > 1)
			{
				sharedData.mAttributed = static_cast<World*>(sharedData.mAttributed->GetParent());
			}
		}

		void WorldParserHelper::HandleSectorEnd(WorldParserHelper&, WorldSharedData& sharedData)
		{
			if (sharedData.Depth() > 1)
			{
				sharedData.mAttributed = static_cast<World*>(sharedData.mAttributed->GetParent());
			}
		}

		void WorldParserHelper::HandleEntityEnd(WorldParserHelper&, WorldSharedData& sharedData)
		{
			if (sharedData.Depth() > 1)
			{
				sharedData.mAttributed = static_cast<World*>(sharedData.mAttributed->GetParent());
			}
		}

		void WorldParserHelper::HandleActionEnd(WorldParserHelper&, WorldSharedData& sharedData)
		{
			if (sharedData.Depth() > 1)
			{
				sharedData.mAttributed = static_cast<World*>(sharedData.mAttributed->GetParent());
			}
		}

		void WorldParserHelper::HandleListEnd(WorldParserHelper&, WorldSharedData& sharedData)
		{
			sharedData.mListTag.clear();
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
