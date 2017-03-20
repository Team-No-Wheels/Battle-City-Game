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

		TEST_METHOD(TestParseAttributedXml)
		{
			XmlParseMaster parser1;
			TestXmlParserHelper helper1;
			TestSharedData data1;
			helper1.Initialize(data1);
			parser1.AddHelper(helper1);
			parser1.Parse(TestXmlAttributed.c_str(), TestXmlAttributed.size(), true);
			parser1.RemoveHelper(helper1);

			std::string output = data1.AwardWinners()->ToString();

			XmlParseMaster parser2;
			TestXmlParserHelper helper2;
			TestSharedData data2;
			helper2.Initialize(data2);
			parser2.AddHelper(helper2);
			parser2.Parse(TestXmlAttributed.c_str(), TestXmlAttributed.size(), true);

			Assert::IsTrue(data2.AwardWinners()->Equals(data1.AwardWinners()));
		}

		TEST_METHOD(TestParseVerboseXml)
		{
			XmlParseMaster parser1;
			TestXmlParserHelper helper1;
			TestSharedData data1;
			helper1.Initialize(data1);
			parser1.AddHelper(helper1);
			parser1.Parse(TestXmlVerbose.c_str(), TestXmlVerbose.size(), true);
			parser1.RemoveHelper(helper1);

			std::string output = data1.AwardWinners()->ToString();

			XmlParseMaster parser2;
			TestXmlParserHelper helper2;
			TestSharedData data2;
			helper2.Initialize(data2);
			parser2.AddHelper(helper2);
			parser2.Parse(TestXmlVerbose.c_str(), TestXmlVerbose.size(), true);

			Assert::IsTrue(data2.AwardWinners()->Equals(data1.AwardWinners()));
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
		static std::string TestXmlAttributed;
		static std::string TestXmlVerbose;
	};

	TestClassHelper XmlParserTest::mHelper;
	std::string XmlParserTest::TestXmlAttributed = "\
		<award name=\"E3 Game Critics Awards\">\
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
		</award>";

	std::string XmlParserTest::TestXmlVerbose = "\
	<award>\
	<name>E3 Game Critics Awards</name>\
	<year>\
		<value>2016</value>\
		<categories>\
			<category>\
				<name>Best of Show</name>\
				<game>The Legend of Zelda: Breath of the Wild</game>\
			</category>\
			<category>\
				<name>Best Original Game</name>\
				<game>Horizon: Zero Dawn</game>\
			</category>\
			<category>\
				<name>Best Console Game</name>\
				<game>The Legend of Zelda: Breath of the Wild</game>\
			</category>\
			<category>\
				<name>Best VR Game</name>\
				<game>Batman: Arkham VR</game>\
			</category>\
			<category>\
				<name>Best PC Game</name>\
				<game>Civilization VI</game>\
			</category>\
			<category>\
				<name>Best Hardware/Peripheral</name>\
				<game>PlayStation VR</game>\
			</category>\
			<category>\
				<name>Best Action Game</name>\
				<game>Battlefield 1</game>\
			</category>\
			<category>\
				<name>Best Action/Adventure Game</name>\
				<game>The Legend of Zelda: Breath of the Wild</game>\
			</category>\
			<category>\
				<name>Best Role-Playing Game</name>\
				<game>Final Fantasy XV</game>\
			</category>\
			<category>\
				<name>Best Racing Game</name>\
				<game>Forza Horizon 3</game>\
			</category>\
			<category>\
				<name>Best Sports Game</name>\
				<game>Steep</game>\
			</category>\
			<category>\
				<name>Best Family Game</name>\
				<game>Skylanders: Imaginators</game>\
			</category>\
			<category>\
				<name>Best Online Multiplayer</name>\
				<game>Titanfall 2</game>\
			</category>\
			<category>\
				<name>Best Independent Game</name>\
				<game>Inside</game>\
			</category>\
			<category>\
				<name>Special Commendation for Graphics</name>\
				<game>God of War</game>\
			</category>\
		</categories>\
	</year>\
</award>";
}
