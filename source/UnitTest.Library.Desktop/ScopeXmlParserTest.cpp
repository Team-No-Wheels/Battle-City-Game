#include "Pch.h"
#include "XmlParseMaster.h"
#include "ScopeParseHelper.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ScopeXmlParserTest)
	{
		typedef AnonymousEngine::Parsers::XmlParseMaster XmlParseMaster;
		typedef AnonymousEngine::Parsers::ScopeParseHelper ScopeParserHelper;
		typedef AnonymousEngine::Parsers::ScopeSharedData ScopeSharedData;
	public:
		TEST_METHOD(TestConstructor)
		{
			ScopeSharedData data;
			XmlParseMaster parser(data);
			ScopeParserHelper helper;
			parser.AddHelper(helper);
			parser.RemoveHelper(helper);
			Assert::IsTrue(&data == parser.GetSharedData());
		}

		TEST_METHOD(TestParseXmlStrings)
		{
			for (const auto& xml : TestXmlStrings)
			{
				ScopeSharedData data1;
				XmlParseMaster parser1(data1);
				ScopeParserHelper helper1;
				parser1.AddHelper(helper1);
				parser1.Parse(xml, true);
				parser1.RemoveHelper(helper1);
				std::string output1 = data1.mScope->ToString();
				Assert::AreEqual(TestScopeDataString, output1);

				ScopeSharedData data2;
				XmlParseMaster parser2(data2);
				ScopeParserHelper helper2;
				parser2.AddHelper(helper2);
				parser2.Parse(xml, true);
				std::string output2 = data2.mScope->ToString();
				Assert::AreEqual(TestScopeDataString, output2);

				Assert::IsTrue(data2.mScope->Equals(data1.mScope));
				Assert::AreEqual(output1, output2);
				delete data1.mScope;
				delete data2.mScope;
			}
		}

		TEST_METHOD(TestParseXmlFiles)
		{
			for (const auto& xmlFile : TestXmlFiles)
			{
				ScopeSharedData data1;
				XmlParseMaster parser1(data1);
				ScopeParserHelper helper1;
				parser1.AddHelper(helper1);
				parser1.ParseFromFile(xmlFile);
				parser1.RemoveHelper(helper1);
				std::string output1 = data1.mScope->ToString();
				Assert::AreEqual(TestScopeDataString, output1);
				Assert::AreEqual(xmlFile, parser1.GetFileName());

				ScopeSharedData data2;
				XmlParseMaster parser2(data2);
				ScopeParserHelper helper2;
				parser2.AddHelper(helper2);
				parser2.ParseFromFile(xmlFile);
				std::string output2 = data2.mScope->ToString();
				Assert::AreEqual(TestScopeDataString, output2);

				Assert::IsTrue(data2.mScope->Equals(data1.mScope));
				Assert::AreEqual(output1, output2);
				delete data1.mScope;
				delete data2.mScope;
			}
		}

		TEST_METHOD(TestInitialize)
		{
			ScopeSharedData data1;
			XmlParseMaster parser1(data1);
			ScopeParserHelper helper1;
			parser1.AddHelper(helper1);
			parser1.Parse(TestXmlStrings[0], true);
			std::string output = data1.mScope->ToString();
			Assert::AreEqual(TestScopeDataString, output);

			helper1.Initialize();
			ScopeSharedData data2;
			parser1.SetSharedData(data2);
			parser1.Parse(TestXmlStrings[0], true);
			output = data1.mScope->ToString();
			Assert::AreEqual(TestScopeDataString, output);
			delete data1.mScope;
			delete data2.mScope;
		}

		TEST_METHOD(TestIncorrectSharedDataTypeGetsIgnored)
		{
			for (const auto& xml : TestXmlStrings)
			{
				AnonymousEngine::Parsers::SharedData data1;
				XmlParseMaster parser1(data1);
				ScopeParserHelper helper1;
				parser1.AddHelper(helper1);
				parser1.Parse(xml, true);
			}
		}

		TEST_METHOD(TestParseXmlFileTypesAndCompare)
		{
			ScopeSharedData data1;
			XmlParseMaster parser1(data1);
			ScopeParserHelper helper1;
			parser1.AddHelper(helper1);
			const std::string& xml1 = TestXmlStrings[0];
			parser1.Parse(xml1, true);
			parser1.RemoveHelper(helper1);
			std::string output1 = data1.mScope->ToString();
			Assert::AreEqual(TestScopeDataString, output1);

			ScopeSharedData data2;
			XmlParseMaster parser2(data2);
			ScopeParserHelper helper2;
			parser2.AddHelper(helper2);
			const std::string& xml2 = TestXmlStrings[1];
			parser2.Parse(xml2, true);
			std::string output2 = data2.mScope->ToString();
			Assert::AreEqual(TestScopeDataString, output2);

			Assert::IsTrue(data2.mScope->Equals(data1.mScope));
			Assert::AreEqual(output1, output2);
			delete data1.mScope;
			delete data2.mScope;
		}

		TEST_METHOD(TestClone)
		{
			ScopeSharedData data1;
			XmlParseMaster parser1(data1);
			ScopeParserHelper helper1;
			parser1.AddHelper(helper1);
			parser1.Parse(TestXmlStrings[0]);

			ScopeSharedData& data2 = *data1.Clone()->As<ScopeSharedData>();
			Assert::AreEqual(data2.Depth(), data1.Depth());
			AnonymousEngine::Scope& scope1 = *(data2.mScope);
			AnonymousEngine::Scope& scope2 = *(data1.mScope);
			delete &data2;
			Assert::IsTrue(scope1 == scope2);

			ScopeParserHelper* helper2 = helper1.Clone()->As<ScopeParserHelper>();
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
			ScopeSharedData* parser2Data = parser2->GetSharedData()->As<ScopeSharedData>();
			delete parser2Data->mScope;
			delete parser2;
			delete &scope1;
			delete &scope2;
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
		static const AnonymousEngine::Vector<std::string> TestXmlStrings;
		static const AnonymousEngine::Vector<std::string> TestXmlFiles;
		static const std::string TestScopeDataString;
	};

	TestClassHelper ScopeXmlParserTest::mHelper;

	const AnonymousEngine::Vector<std::string> ScopeXmlParserTest::TestXmlStrings = {
		"<scope name=\"world\">\
			<scope name=\"sector1\">\
				<scope name=\"entity1\">\
					<string name=\"name\" value=\"hero\"/>\
					<integer name=\"age\" value=\"27\"/>\
					<float name=\"attack\" value=\"10.5\"/>\
					<vector name=\"position\" x=\"0.5\" y=\"10.2\" z=\"100.0\" w=\"1.0\"/>\
					<matrix>\
						<vector name=\"row1\" x=\"1.2\" y=\"10.2\" z=\"0.005\" w=\"1.0\"/>\
						<vector name=\"row2\" x=\"3.6\" y=\"102\" z=\"0.01\" w=\"1.0\"/>\
						<vector name=\"row3\" x=\"1000\" y=\"177.2\" z=\"101\" w=\"1.0\"/>\
						<vector name=\"row4\" x=\"11\" y=\"13.6\" z=\"100.00035\" w=\"1.0\"/>\
					</matrix>\
				</scope>\
				<scope name=\"entity2\">\
					<string name=\"name\" value=\"minion\"/>\
					<vector name=\"position\" x=\"50.4\" y=\"12.3\" z=\"10.0\" w=\"1.0\"/>\
				</scope>\
			</scope>\
			<scope name=\"sector2\">\
				<scope name=\"entity100\">\
					<string name=\"name\" value=\"boss\"/>\
					<vector name=\"position\" x=\"77.04\" y=\"27.9\" z=\"20.0\" w=\"1.0\"/>\
				</scope>\
			</scope>\
			<integer name=\"sectors\" value=\"2\"/>\
		</scope>"
	};

	const AnonymousEngine::Vector<std::string> ScopeXmlParserTest::TestXmlFiles = {
		"TestData/scope.xml"
	};

	const std::string ScopeXmlParserTest::TestScopeDataString = "{\"name\": \"E3 Game Critics Awards\", \"year\": {\"value\": \"2016\", \"categories\": {\"category\": [{\"game\": \"The Legend of Zelda: Breath of the Wild\", \"name\": \"Best of Show\"}, {\"game\": \"Horizon: Zero Dawn\", \"name\": \"Best Original Game\"}, {\"game\": \"The Legend of Zelda: Breath of the Wild\", \"name\": \"Best Console Game\"}, {\"game\": \"Batman: Arkham VR\", \"name\": \"Best VR Game\"}, {\"game\": \"Civilization VI\", \"name\": \"Best PC Game\"}, {\"game\": \"PlayStation VR\", \"name\": \"Best Hardware/Peripheral\"}, {\"game\": \"Battlefield 1\", \"name\": \"Best Action Game\"}, {\"game\": \"The Legend of Zelda: Breath of the Wild\", \"name\": \"Best Action/Adventure Game\"}, {\"game\": \"Final Fantasy XV\", \"name\": \"Best Role-Playing Game\"}, {\"game\": \"Forza Horizon 3\", \"name\": \"Best Racing Game\"}, {\"game\": \"Steep\", \"name\": \"Best Sports Game\"}, {\"game\": \"Skylanders: Imaginators\", \"name\": \"Best Family Game\"}, {\"game\": \"Titanfall 2\", \"name\": \"Best Online Multiplayer\"}, {\"game\": \"Inside\", \"name\": \"Best Independent Game\"}, {\"game\": \"God of War\", \"name\": \"Special Commendation for Graphics\"}]}}}";
}
