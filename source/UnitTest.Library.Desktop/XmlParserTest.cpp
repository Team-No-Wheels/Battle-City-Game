#include "Pch.h"
#include "XmlParseMaster.h"
#include "FooXmlParseHelper.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(XmlParserTest)
	{
		typedef AnonymousEngine::Parsers::XmlParseMaster XmlParseMaster;
	public:
		TEST_METHOD(TestConstructor)
		{
			FooSharedData data;
			XmlParseMaster parser(data);
			FooXmlParserHelper helper1, helper2;
			parser.AddHelper(helper1);
			Assert::ExpectException<std::runtime_error>([&parser, &helper2] { parser.AddHelper(helper2); });
			parser.RemoveHelper(helper1);
			Assert::IsTrue(&data == parser.GetSharedData());
			Assert::ExpectException<std::runtime_error>([&data] { data.DecrementDepth(); });
		}

		TEST_METHOD(TestParseInvalidXml)
		{
			FooSharedData data1;
			XmlParseMaster parser1(data1);
			FooXmlParserHelper helper1;
			parser1.AddHelper(helper1);
			Assert::ExpectException<std::runtime_error>([&parser1] { parser1.Parse(TestXmlInvalid); });

			FooSharedData data2;
			XmlParseMaster parser2(data1);
			FooXmlParserHelper helper2;
			parser2.AddHelper(helper2);
			Assert::ExpectException<std::runtime_error>([&parser2] { parser2.ParseFromFile(mHelper.GetRandomString()); });
		}

		TEST_METHOD(TestParseXmlStrings)
		{
			for (const auto& xml : TestXmlStrings)
			{
				FooSharedData data1;
				XmlParseMaster parser1(data1);
				FooXmlParserHelper helper1;
				parser1.AddHelper(helper1);
				parser1.Parse(xml);
				parser1.RemoveHelper(helper1);
				std::string output1 = data1.mAwardWinners->ToString();
				Assert::AreEqual(TestScopeDataString, output1);

				FooSharedData data2;
				XmlParseMaster parser2(data2);
				FooXmlParserHelper helper2;
				parser2.AddHelper(helper2);
				parser2.Parse(xml);
				std::string output2 = data2.mAwardWinners->ToString();
				Assert::AreEqual(TestScopeDataString, output2);

				Assert::IsTrue(data2.mAwardWinners->Equals(data1.mAwardWinners));
				Assert::AreEqual(output1, output2);
				delete data1.mAwardWinners;
				delete data2.mAwardWinners;
			}
		}

		TEST_METHOD(TestParseXmlFiles)
		{
			for (const auto& xmlFile : TestXmlFiles)
			{
				FooSharedData data1;
				XmlParseMaster parser1(data1);
				FooXmlParserHelper helper1;
				parser1.AddHelper(helper1);
				parser1.ParseFromFile(xmlFile);
				parser1.RemoveHelper(helper1);
				std::string output1 = data1.mAwardWinners->ToString();
				Assert::AreEqual(TestScopeDataString, output1);
				Assert::AreEqual(xmlFile, parser1.GetFileName());

				FooSharedData data2;
				XmlParseMaster parser2(data2);
				FooXmlParserHelper helper2;
				parser2.AddHelper(helper2);
				parser2.ParseFromFile(xmlFile);
				std::string output2 = data2.mAwardWinners->ToString();
				Assert::AreEqual(TestScopeDataString, output2);

				Assert::IsTrue(data2.mAwardWinners->Equals(data1.mAwardWinners));
				Assert::AreEqual(output1, output2);
				delete data1.mAwardWinners;
				delete data2.mAwardWinners;
			}
		}

		TEST_METHOD(TestInitialize)
		{
			FooSharedData data1;
			XmlParseMaster parser1(data1);
			FooXmlParserHelper helper1;
			parser1.AddHelper(helper1);
			parser1.Parse(TestXmlStrings[0], true);
			std::string output = data1.mAwardWinners->ToString();
			Assert::AreEqual(TestScopeDataString, output);

			helper1.Initialize();
			FooSharedData data2;
			parser1.SetSharedData(data2);
			parser1.Parse(TestXmlStrings[0], true);
			output = data1.mAwardWinners->ToString();
			Assert::AreEqual(TestScopeDataString, output);
			delete data1.mAwardWinners;
			delete data2.mAwardWinners;
		}

		TEST_METHOD(TestIncorrectSharedDataTypeGetsIgnored)
		{
			for (const auto& xml : TestXmlStrings)
			{
				SharedData data1;
				XmlParseMaster parser1(data1);
				FooXmlParserHelper helper1;
				parser1.AddHelper(helper1);
				parser1.Parse(xml);
			}
		}

		TEST_METHOD(TestParseXmlFileTypesAndCompare)
		{
			FooSharedData data1;
			XmlParseMaster parser1(data1);
			FooXmlParserHelper helper1;
			parser1.AddHelper(helper1);
			const std::string& xml1 = TestXmlStrings[0];
			parser1.Parse(xml1, true);
			parser1.RemoveHelper(helper1);
			std::string output1 = data1.mAwardWinners->ToString();
			Assert::AreEqual(TestScopeDataString, output1);

			FooSharedData data2;
			XmlParseMaster parser2(data2);
			FooXmlParserHelper helper2;
			parser2.AddHelper(helper2);
			const std::string& xml2 = TestXmlStrings[1];
			parser2.Parse(xml2, true);
			std::string output2 = data2.mAwardWinners->ToString();
			Assert::AreEqual(TestScopeDataString, output2);

			Assert::IsTrue(data2.mAwardWinners->Equals(data1.mAwardWinners));
			Assert::AreEqual(output1, output2);
			delete data1.mAwardWinners;
			delete data2.mAwardWinners;
		}

		TEST_METHOD(TestClone)
		{
			FooSharedData data1;
			XmlParseMaster parser1(data1);
			FooXmlParserHelper helper1;
			parser1.AddHelper(helper1);
			parser1.Parse(TestXmlStrings[0]);

			SharedData baseData;
			SharedData* baseDataClone = baseData.Create();
			Assert::AreEqual(baseData.Depth(), baseDataClone->Depth());
			delete baseDataClone;

			FooSharedData& data2 = *data1.Create()->As<FooSharedData>();
			Assert::AreEqual(data2.Depth(), data1.Depth());
			AnonymousEngine::Scope& scope1 = *(data2.mAwardWinners);
			AnonymousEngine::Scope& scope2 = *(data1.mAwardWinners);
			delete &data2;
			Assert::IsTrue(scope1 == scope2);
			
			FooXmlParserHelper* helper2 = helper1.Create()->As<FooXmlParserHelper>();
			delete helper2;

			XmlParseMaster* parser2 = parser1.Clone();
			Assert::ExpectException<std::runtime_error>([&parser2, &helper1]() { parser2->AddHelper(helper1); });
			Assert::ExpectException<std::runtime_error>([&parser2, &helper1]() { parser2->RemoveHelper(helper1); });
			FooSharedData* parser2Data = parser2->GetSharedData()->As<FooSharedData>();
			delete parser2Data->mAwardWinners;
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
		static const std::string TestXmlInvalid;
		static const AnonymousEngine::Vector<std::string> TestXmlStrings;
		static const AnonymousEngine::Vector<std::string> TestXmlFiles;
		static const std::string TestScopeDataString;
	};

	TestClassHelper XmlParserTest::mHelper;

	const std::string XmlParserTest::TestXmlInvalid = "<award";

	const AnonymousEngine::Vector<std::string> XmlParserTest::TestXmlStrings = {
		"<award name=\"E3 Game Critics Awards\">\
		<year value=\"2016\">\
			<categories>\
				<category name=\"Best of Show\" game=\"The Legend of Zelda: Breath of the Wild\"/>\
				<category name=\"Best Original Game\" game=\"Horizon: Zero Dawn\"/>\
				<category name=\"Best Console Game\" game=\"The Legend of Zelda: Breath of the Wild\"/>\
				<category name=\"Best VR Game\" game=\"Batman: Arkham VR\"/>\
				<category name=\"Best PC Game\" game=\"Civilization VI\"/>\
				<category name=\"Best Hardware/Peripheral\" game=\"PlayStation VR\"/>\
				<category name=\"Best Action Game\" game=\"Battlefield 1\"/>\
				<category name=\"Best Action/Adventure Game\" game=\"The Legend of Zelda: Breath of the Wild\"/>\
				<category name=\"Best Role-Playing Game\" game=\"Final Fantasy XV\"/>\
				<category name=\"Best Racing Game\" game=\"Forza Horizon 3\"/>\
				<category name=\"Best Sports Game\" game=\"Steep\"/>\
				<category name=\"Best Family Game\" game=\"Skylanders: Imaginators\"/>\
				<category name=\"Best Online Multiplayer\" game=\"Titanfall 2\"/>\
				<category name=\"Best Independent Game\" game=\"Inside\"/>\
				<category name=\"Special Commendation for Graphics\" game=\"God of War\"/>\
			</categories>\
		</year>\
		</award>",

		"<award>\
			<name>E3 Game Critics Awards</name>\
			<year>\
				<value>2016</value>\
				<categories>\
					<category>\
						<game>The Legend of Zelda: Breath of the Wild</game>\
						<name>Best of Show</name>\
					</category>\
					<category>\
						<game>Horizon: Zero Dawn</game>\
						<name>Best Original Game</name>\
					</category>\
					<category>\
						<game>The Legend of Zelda: Breath of the Wild</game>\
						<name>Best Console Game</name>\
					</category>\
					<category>\
						<game>Batman: Arkham VR</game>\
						<name>Best VR Game</name>\
					</category>\
					<category>\
						<game>Civilization VI</game>\
						<name>Best PC Game</name>\
					</category>\
					<category>\
						<game>PlayStation VR</game>\
						<name>Best Hardware/Peripheral</name>\
					</category>\
					<category>\
						<game>Battlefield 1</game>\
						<name>Best Action Game</name>\
					</category>\
					<category>\
						<game>The Legend of Zelda: Breath of the Wild</game>\
						<name>Best Action/Adventure Game</name>\
					</category>\
					<category>\
						<game>Final Fantasy XV</game>\
						<name>Best Role-Playing Game</name>\
					</category>\
					<category>\
						<game>Forza Horizon 3</game>\
						<name>Best Racing Game</name>\
					</category>\
					<category>\
						<game>Steep</game>\
						<name>Best Sports Game</name>\
					</category>\
					<category>\
						<game>Skylanders: Imaginators</game>\
						<name>Best Family Game</name>\
					</category>\
					<category>\
						<game>Titanfall 2</game>\
						<name>Best Online Multiplayer</name>\
					</category>\
					<category>\
						<game>Inside</game>\
						<name>Best Independent Game</name>\
					</category>\
					<category>\
						<game>God of War</game>\
						<name>Special Commendation for Graphics</name>\
					</category>\
				</categories>\
			</year>\
		</award>"
	};

	const AnonymousEngine::Vector<std::string> XmlParserTest::TestXmlFiles = {
		"TestData/attributed.xml",
		"TestData/verbose.xml"
	};

	const std::string XmlParserTest::TestScopeDataString = "{\"name\": \"E3 Game Critics Awards\", \"year\": {\"value\": \"2016\", \"categories\": {\"category\": [{\"game\": \"The Legend of Zelda: Breath of the Wild\", \"name\": \"Best of Show\"}, {\"game\": \"Horizon: Zero Dawn\", \"name\": \"Best Original Game\"}, {\"game\": \"The Legend of Zelda: Breath of the Wild\", \"name\": \"Best Console Game\"}, {\"game\": \"Batman: Arkham VR\", \"name\": \"Best VR Game\"}, {\"game\": \"Civilization VI\", \"name\": \"Best PC Game\"}, {\"game\": \"PlayStation VR\", \"name\": \"Best Hardware/Peripheral\"}, {\"game\": \"Battlefield 1\", \"name\": \"Best Action Game\"}, {\"game\": \"The Legend of Zelda: Breath of the Wild\", \"name\": \"Best Action/Adventure Game\"}, {\"game\": \"Final Fantasy XV\", \"name\": \"Best Role-Playing Game\"}, {\"game\": \"Forza Horizon 3\", \"name\": \"Best Racing Game\"}, {\"game\": \"Steep\", \"name\": \"Best Sports Game\"}, {\"game\": \"Skylanders: Imaginators\", \"name\": \"Best Family Game\"}, {\"game\": \"Titanfall 2\", \"name\": \"Best Online Multiplayer\"}, {\"game\": \"Inside\", \"name\": \"Best Independent Game\"}, {\"game\": \"God of War\", \"name\": \"Special Commendation for Graphics\"}]}}}";
}
