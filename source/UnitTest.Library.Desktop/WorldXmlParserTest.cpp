#include "Pch.h"
#include "XmlParseMaster.h"
#include "WorldParserHelper.h"
#include "TestClassHelper.h"
#include "Entity.h"
#include "Action.h"
#include "World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(WorldXmlParserTest)
	{
		typedef AnonymousEngine::Parsers::XmlParseMaster XmlParseMaster;
		typedef AnonymousEngine::Parsers::WorldParserHelper WorldParserHelper;
		typedef AnonymousEngine::Parsers::WorldSharedData WorldSharedData;
	public:
		TEST_METHOD(TestConstructor)
		{
			WorldSharedData data;
			XmlParseMaster parser(data);
			WorldParserHelper helper;
			parser.AddHelper(helper);
			parser.RemoveHelper(helper);
			Assert::IsTrue(&data == parser.GetSharedData());
		}

		TEST_METHOD(TestParseXmlFiles)
		{
			Containers::EntityFactory entityFactory;
			Containers::ActionFactory actionFactory;
			for (const auto& xmlFile : TestXmlFiles)
			{
				WorldSharedData data;
				XmlParseMaster parser(data);
				WorldParserHelper helper;
				parser.AddHelper(helper);
				parser.ParseFromFile(xmlFile);
				parser.RemoveHelper(helper);

				Containers::World* world = data.ExtractWorld();
				std::string output1 = world->ToString();
				Assert::AreEqual(TestWorldDataString, output1);
				Assert::AreEqual(xmlFile, parser.GetFileName());
				delete world;
			}
		}

		TEST_METHOD(TestInitialize)
		{
			//Containers::EntityFactory entityFactory;
			//Containers::ActionFactory actionFactory;

			//WorldSharedData data1;
			//XmlParseMaster parser1(data1);
			//WorldParserHelper helper1;
			//parser1.AddHelper(helper1);
			//parser1.ParseFromFile(TestXmlFiles[0]);
			//std::string output = data1.mAttributed->ToString();
			////Assert::AreEqual(TestXmlFiles[0], output);

			//helper1.Initialize();
			//WorldSharedData data2;
			//parser1.SetSharedData(data2);
			//parser1.ParseFromFile(TestXmlFiles[0]);
			//output = data1.mAttributed->ToString();
			////Assert::AreEqual(TestXmlFiles[0], output);
			//Assert::AreEqual(0U, data1.Depth());
			//Assert::AreEqual(0U, data2.Depth());
			//delete data1.mAttributed;
			//delete data2.mAttributed;
		}

		TEST_METHOD(TestClone)
		{
			/*WorldSharedData data1;
			XmlParseMaster parser1(data1);
			WorldParserHelper helper1;
			parser1.AddHelper(helper1);
			parser1.Parse(TestXmlFiles[0]);
			Assert::AreEqual(0U, data1.Depth());

			WorldSharedData& data2 = *data1.Clone()->As<WorldSharedData>();
			Assert::AreEqual(data2.Depth(), data1.Depth());
			AnonymousEngine::Scope& scope1 = *(data2.mAttributed);
			AnonymousEngine::Scope& scope2 = *(data1.mAttributed);
			Assert::AreEqual(0U, data2.Depth());
			delete &data2;
			Assert::IsTrue(scope1 == scope2);

			WorldParserHelper* helper2 = helper1.Clone()->As<WorldParserHelper>();
			delete helper2;

			XmlParseMaster* parser2 = parser1.Clone();
			Assert::ExpectException<std::runtime_error>([&parser2, &helper1]()
			{
				parser2->AddHelper(helper1);
			});
			Assert::ExpectException<std::runtime_error>([&parser2, &helper1]()
			{
				parser2->RemoveHelper(helper1);
			});
			WorldSharedData* parser2Data = parser2->GetSharedData()->As<WorldSharedData>();
			delete parser2Data->mAttributed;
			delete parser2;
			delete &scope1;
			delete &scope2;*/
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

		static TestClassHelper mHelper;
		static const AnonymousEngine::Vector<std::string> TestXmlFiles;
		static const std::string TestWorldDataString;
	};

	TestClassHelper WorldXmlParserTest::mHelper;

	const AnonymousEngine::Vector<std::string> WorldXmlParserTest::TestXmlFiles = {
		"TestData/world.xml"
	};

	const std::string WorldXmlParserTest::TestWorldDataString = "{\"Name\": \"Skyrim\", \"Sectors\": [{\"Name\": \"Whiterun\", \"Entities\": [{\"Name\": \"Bannered Mare\", \"Actions\": [{\"Name\": \"Init\", \"Capacity\": \"10\"}, {\"Name\": \"Upgrade\", \"Capacity\": \"5\"}], \"Owner\": \"Hulda\", \"Beds\": \"10\", \"Price\": \"20000.500000\", \"Location\": \"0.500000,10.200000,100.000000,1.000000\", \"Transform\": \"1.200000,10.200000,0.005000,1.000000,3.600000,102.000000,0.010000,1.000000,1000.000000,177.199997,101.000000,1.000000,11.000000,13.600000,100.000351,1.000000\"}, {\"Name\": \"Dragonsreach\", \"Owner\": \"Balgruuf the Greater\", \"Location\": \"50.400002,12.300000,10.000000,1.000000\"}], \"Jarl\": \"Balgruuf the Greater\"}, {\"Name\": \"Winterhold\", \"Entities\": {\"Name\": \"College of Winterhold\", \"Actions\": {\"Name\": \"Init\", \"MaxStudents\": \"100\"}, \"Arch-Mage\": \"Savos Aren\", \"Location\": \"77.040001,27.900000,20.000000,1.000000\"}, \"Jarl\": \"Korir\"}], \"Population\": \"100000\"}";
}
