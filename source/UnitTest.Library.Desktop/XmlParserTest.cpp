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
			parser1.Parse(TestXml.c_str(), TestXml.size(), true);
			parser1.RemoveHelper(helper1);

			XmlParseMaster parser2;
			TestXmlParserHelper helper2;
			TestSharedData data2;
			helper2.Initialize(data2);
			parser2.AddHelper(helper2);
			parser2.Parse(TestXml.c_str(), TestXml.size(), true);

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
		static std::string TestXml;
	};

	TestClassHelper XmlParserTest::mHelper;
	std::string XmlParserTest::TestXml = "\
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
}
