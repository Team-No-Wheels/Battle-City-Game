#include "Pch.h"
#include "GameClock.h"
#include "Action.h"
#include "Entity.h"
#include "Sector.h"
#include "TestClassHelper.h"
#include "World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestLibraryDesktop
{
	using namespace AnonymousEngine::Containers;
	using namespace std::chrono;

	TEST_CLASS(WorldTest)
	{
	public:
		TEST_METHOD(TestWorldInitialize)
		{
			std::string name = mHelper.GetRandomString();
			World world(name);
			Assert::IsTrue(Datum::DatumType::String == world["Name"].Type());
			Assert::IsTrue(Datum::DatumType::Scope == world["Sectors"].Type());
			Assert::IsNull(world.GetParent());
			Assert::AreEqual(name, world.Name());
			Assert::AreEqual(name, world["Name"].Get<std::string>());
			Assert::AreEqual(1U, world["Name"].Size());
			Assert::AreEqual(0U, world.Sectors().Size());
			Assert::AreEqual(0U, world["Sectors"].Size());
			Assert::IsTrue(&world.Sectors() == &world["Sectors"]);

			std::string name2 = mHelper.GetRandomString();
			world.SetName(name2);
			Assert::AreEqual(name2, world["Name"].Get<std::string>());
		}

		TEST_METHOD(TestSectorInitialize)
		{
			std::string name = mHelper.GetRandomString();
			Sector sector(name);
			Assert::IsTrue(Datum::DatumType::String == sector["Name"].Type());
			Assert::IsTrue(Datum::DatumType::Scope == sector["Entities"].Type());
			Assert::IsNull(sector.GetParent());
			Assert::AreEqual(name, sector.Name());
			Assert::AreEqual(name, sector["Name"].Get<std::string>());
			Assert::AreEqual(1U, sector["Name"].Size());
			Assert::AreEqual(0U, sector.Entities().Size());
			Assert::AreEqual(0U, sector["Entities"].Size());
			Assert::IsTrue(&sector.Entities() == &sector["Entities"]);

			std::string name2 = mHelper.GetRandomString();
			sector.SetName(name2);
			Assert::AreEqual(name2, sector["Name"].Get<std::string>());
		}

		TEST_METHOD(TestEntityInitialize)
		{
			std::string name = mHelper.GetRandomString();
			Entity entity(name);
			Assert::IsTrue(Datum::DatumType::String == entity["Name"].Type());
			Assert::IsTrue(Datum::DatumType::Scope == entity["Actions"].Type());
			Assert::IsNull(entity.GetParent());
			Assert::AreEqual(name, entity.Name());
			Assert::AreEqual(name, entity["Name"].Get<std::string>());
			Assert::AreEqual(1U, entity["Name"].Size());
			Assert::AreEqual(0U, entity.Actions().Size());
			Assert::AreEqual(0U, entity["Actions"].Size());
			Assert::IsTrue(&entity.Actions() == &entity["Actions"]);

			std::string name2 = mHelper.GetRandomString();
			entity.SetName(name2);
			Assert::AreEqual(name2, entity["Name"].Get<std::string>());
		}

		TEST_METHOD(TestActionInitialize)
		{
			std::string name = mHelper.GetRandomString();
			Action action(name);
			Assert::IsTrue(Datum::DatumType::String == action["Name"].Type());
			Assert::IsTrue(Datum::DatumType::Scope == action["Actions"].Type());
			Assert::IsNull(action.GetParent());
			Assert::AreEqual(name, action.Name());
			Assert::AreEqual(name, action["Name"].Get<std::string>());
			Assert::AreEqual(1U, action["Name"].Size());
			Assert::AreEqual(0U, action.Actions().Size());
			Assert::AreEqual(0U, action["Actions"].Size());
			Assert::IsTrue(&action.Actions() == &action["Actions"]);

			std::string name2 = mHelper.GetRandomString();
			action.SetName(name2);
			Assert::AreEqual(name2, action["Name"].Get<std::string>());
		}

		TEST_METHOD(TestCreateAndAdoptSector)
		{
			World world(mHelper.GetRandomString());
			Assert::AreEqual(0U, world.Sectors().Size());
			
			for (std::uint32_t index = 0; index < ((mHelper.GetRandomUInt32() % 10) + 1); ++index)
			{
				std::string name = mHelper.GetRandomString();
				world.CreateSector(name);
				Assert::AreEqual(index + 1, world.Sectors().Size());
				Sector* sector = static_cast<Sector*>(&world.Sectors().Get<Scope>(index));
				Assert::IsTrue(&world == &sector->GetWorld());
				Assert::AreEqual(name, sector->Name());
			}
		}

		TEST_METHOD(TestCreateAndAdoptEntity)
		{
			World world(mHelper.GetRandomString());
			Sector& sector = world.CreateSector(mHelper.GetRandomString());
			EntityFactory entityFactory;

			for (std::uint32_t index = 0; index < ((mHelper.GetRandomUInt32() % 10) + 1); ++index)
			{
				std::string name = mHelper.GetRandomString();
				sector.CreateEntity(name, entityFactory.ClassName());
				Assert::AreEqual(index + 1, sector.Entities().Size());
				Entity* entity = static_cast<Entity*>(&sector.Entities().Get<Scope>(index));
				Assert::IsTrue(&sector == &entity->GetSector());
				Assert::AreEqual(name, entity->Name());
			}
		}

		TEST_METHOD(TestCreateAndAdoptActionInEntity)
		{
			World world(mHelper.GetRandomString());
			Sector& sector = world.CreateSector(mHelper.GetRandomString());
			EntityFactory entityFactory;
			Entity& entity = sector.CreateEntity(mHelper.GetRandomString(), entityFactory.ClassName());
			ActionFactory actionFactory;

			for (std::uint32_t index = 0; index < ((mHelper.GetRandomUInt32() % 10) + 1); ++index)
			{
				std::string name = mHelper.GetRandomString();
				entity.CreateAction(name, actionFactory.ClassName());
				Assert::AreEqual(index + 1, entity.Actions().Size());
				Action* action = static_cast<Action*>(&entity.Actions().Get<Scope>(index));
				Assert::IsTrue(&entity == static_cast<Entity*>(action->GetParent()));
				Assert::AreEqual(name, action->Name());
			}
		}

		TEST_METHOD(TestCreateAndAdoptActionInAction)
		{
			World world(mHelper.GetRandomString());
			Sector& sector = world.CreateSector(mHelper.GetRandomString());
			EntityFactory entityFactory;
			Entity& entity = sector.CreateEntity(mHelper.GetRandomString(), entityFactory.ClassName());
			ActionFactory actionFactory;
			Action& action = entity.CreateAction(mHelper.GetRandomString(), actionFactory.ClassName());

			for (std::uint32_t index = 0; index < ((mHelper.GetRandomUInt32() % 10) + 1); ++index)
			{
				std::string name = mHelper.GetRandomString();
				action.CreateAction(name, actionFactory.ClassName());
				Assert::AreEqual(index + 1, action.Actions().Size());
				Action* newAction = static_cast<Action*>(&action.Actions().Get<Scope>(index));
				Assert::IsTrue(&action == static_cast<Action*>(newAction->GetParent()));
				Assert::AreEqual(name, newAction->Name());
			}
		}

		TEST_METHOD(TestUpdate)
		{
			World world(mHelper.GetRandomString());
			WorldState state;
			GameClock clock;
			clock.StartTime();
			clock.UpdateGameTime(state.mGameTime);
			const std::uint32_t maxItems = 10;

			PopulateSectors(world, (mHelper.GetRandomUInt32() % maxItems) + 1);
			for (std::uint32_t sectorIndex = 0; sectorIndex < world.Sectors().Size(); ++sectorIndex)
			{
				Sector* sector = static_cast<Sector*>(&world.Sectors().Get<Scope>(sectorIndex));
				PopulateEntities(*sector, (mHelper.GetRandomUInt32() % maxItems) + 1);

				for (std::uint32_t entityIndex = 0; entityIndex < sector->Entities().Size(); ++entityIndex)
				{
					Entity* entity = static_cast<Entity*>(&sector->Entities().Get<Scope>(entityIndex));
					PopulateActionsInEntity(*entity, (mHelper.GetRandomUInt32() % maxItems) + 1);

					for (std::uint32_t actionIndex = 0; actionIndex < entity->Actions().Size(); ++actionIndex)
					{
						Action* action = static_cast<Action*>(&entity->Actions().Get<Scope>(actionIndex));
						PopulateActionsInAction(*action, (mHelper.GetRandomUInt32() % maxItems) + 1);
					}
				}
			}

			for (std::uint32_t index = 0; index < ((mHelper.GetRandomUInt32() % 10) + 1); ++index)
			{
				clock.UpdateGameTime(state.mGameTime);
				Assert::IsTrue(clock.StartTime() <= clock.CurrentTime());
				Assert::IsTrue(clock.StartTime() <= clock.LastTime());
				Assert::IsTrue(clock.CurrentTime() >= clock.LastTime());
				Assert::IsTrue(state.mGameTime.CurrentTime() == clock.CurrentTime());
				Assert::IsTrue(state.mGameTime.ElapsedGameTime() >= milliseconds());
				Assert::IsTrue(state.mGameTime.TotalGameTime() == duration_cast<milliseconds>(clock.CurrentTime() - clock.StartTime()));

				world.Update(state);
			}
		}

		TEST_CLASS_INITIALIZE(InitializeClass)
		{
			mHelper.BeginClass();
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			mHelper.Setup();
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			mHelper.Teardown();
		}

		TEST_CLASS_CLEANUP(CleanupClass)
		{
			mHelper.EndClass();
		}

	private:

		static void PopulateSectors(World& world, std::uint32_t elements)
		{
			for (std::uint32_t index = 0; index < elements; ++index)
			{
				world.CreateSector(mHelper.GetRandomString());
			}
		}

		static void PopulateEntities(Sector& sector, std::uint32_t elements)
		{
			EntityFactory entityFactory;
			for (std::uint32_t index = 0; index < elements; ++index)
			{
				sector.CreateEntity(mHelper.GetRandomString(), entityFactory.ClassName());
			}
		}

		static void PopulateActionsInEntity(Entity& entity, std::uint32_t elements)
		{
			ActionFactory actionFactory;
			for (std::uint32_t index = 0; index < elements; ++index)
			{
				entity.CreateAction(mHelper.GetRandomString(), actionFactory.ClassName());
			}
		}

		static void PopulateActionsInAction(Action& action, std::uint32_t elements)
		{
			ActionFactory actionFactory;
			for (std::uint32_t index = 0; index < elements; ++index)
			{
				action.CreateAction(mHelper.GetRandomString(), actionFactory.ClassName());
			}
		}

		static TestClassHelper mHelper;
	};

	TestClassHelper WorldTest::mHelper;
}
