#include "Pch.h"
#include "XmlParseMaster.h"
#include "TestXmlParseHelper.h"
#include "TestClassHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(XmlParserTest)
	{
		typedef AnonymousEngine::Parsers::XmlParseMaster XmlParseMaster;
	public:
		TEST_METHOD(TestInitialization)
		{
			XmlParseMaster parser;
			TestXmlParserHelper helper;
			parser.AddHelper(helper);
			parser.RemoveHelper(helper);
		}

		TEST_METHOD(TestParseXmlStrings)
		{
			for (const auto& xml : TestXmlStrings)
			{
				TestSharedData data1;
				XmlParseMaster parser1;
				data1.SetXmlParseMaster(parser1);
				parser1.SetSharedData(data1);
				TestXmlParserHelper helper1;
				parser1.AddHelper(helper1);
				parser1.Parse(xml, true);
				parser1.RemoveHelper(helper1);
				std::string output1 = data1.AwardWinners()->ToString();

				TestSharedData data2;
				XmlParseMaster parser2;
				data2.SetXmlParseMaster(parser2);
				parser2.SetSharedData(data2);
				TestXmlParserHelper helper2;
				parser2.AddHelper(helper2);
				parser2.Parse(xml, true);
				std::string output2 = data2.AwardWinners()->ToString();

				Assert::IsTrue(data2.AwardWinners()->Equals(data1.AwardWinners()));
				Assert::AreEqual(output1, output2);
			}
		}

		TEST_METHOD(TestParseXmlFiles)
		{
			for (const auto& xmlFile : TestXmlFiles)
			{
				TestSharedData data1;
				XmlParseMaster parser1;
				data1.SetXmlParseMaster(parser1);
				parser1.SetSharedData(data1);
				TestXmlParserHelper helper1;
				parser1.AddHelper(helper1);
				parser1.ParseFromFile(xmlFile);
				parser1.RemoveHelper(helper1);
				std::string output1 = data1.AwardWinners()->ToString();

				TestSharedData data2;
				XmlParseMaster parser2;
				data2.SetXmlParseMaster(parser2);
				parser2.SetSharedData(data2);
				TestXmlParserHelper helper2;
				parser2.AddHelper(helper2);
				parser2.ParseFromFile(xmlFile);
				std::string output2 = data2.AwardWinners()->ToString();

				Assert::IsTrue(data2.AwardWinners()->Equals(data1.AwardWinners()));
				Assert::AreEqual(output1, output2);
			}
		}

		TEST_METHOD(TestParseXmlFileTypesAndCompare)
		{
			TestSharedData data1;
			XmlParseMaster parser1;
			data1.SetXmlParseMaster(parser1);
			parser1.SetSharedData(data1);
			TestXmlParserHelper helper1;
			parser1.AddHelper(helper1);
			const std::string& xml1 = TestXmlStrings[0];
			parser1.Parse(xml1, true);
			parser1.RemoveHelper(helper1);
			std::string output1 = data1.AwardWinners()->ToString();

			TestSharedData data2;
			XmlParseMaster parser2;
			data2.SetXmlParseMaster(parser2);
			parser2.SetSharedData(data2);
			TestXmlParserHelper helper2;
			parser2.AddHelper(helper2);
			const std::string& xml2 = TestXmlStrings[1];
			parser2.Parse(xml2, true);
			std::string output2 = data2.AwardWinners()->ToString();

			Assert::IsTrue(data2.AwardWinners()->Equals(data1.AwardWinners()));
			Assert::AreEqual(output1, output2);
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
	};

	TestClassHelper XmlParserTest::mHelper;

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
}
