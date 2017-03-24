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
				parser1.Parse(xml);
				parser1.RemoveHelper(helper1);
				std::string output1 = data1.mScope->ToString();
				Assert::AreEqual(TestScopeDataString, output1);

				ScopeSharedData data2;
				XmlParseMaster parser2(data2);
				ScopeParserHelper helper2;
				parser2.AddHelper(helper2);
				parser2.Parse(xml);
				std::string output2 = data2.mScope->ToString();
				Assert::AreEqual(TestScopeDataString, output2);

				Assert::IsTrue(data2.mScope->Equals(data1.mScope));
				Assert::AreEqual(output1, output2);
				Assert::AreEqual(0U, data1.Depth());
				Assert::AreEqual(0U, data2.Depth());
				delete data1.mScope;
				delete data2.mScope;
			}
		}

		TEST_METHOD(TestParseInvalidXmlStrings)
		{
			for (const auto& xml : InvalidXmls)
			{
				ScopeSharedData data1;
				XmlParseMaster parser1(data1);
				ScopeParserHelper helper1;
				parser1.AddHelper(helper1);
				Assert::ExpectException<std::runtime_error>([&parser1, &xml] { parser1.Parse(xml); });
				delete data1.mScope;
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
				Assert::AreEqual(0U, data1.Depth());
				Assert::AreEqual(0U, data2.Depth());
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
			Assert::AreEqual(0U, data1.Depth());
			Assert::AreEqual(0U, data2.Depth());
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
				parser1.Parse(xml);
			}
		}

		TEST_METHOD(TestClone)
		{
			ScopeSharedData data1;
			XmlParseMaster parser1(data1);
			ScopeParserHelper helper1;
			parser1.AddHelper(helper1);
			parser1.Parse(TestXmlStrings[0]);
			Assert::AreEqual(0U, data1.Depth());

			ScopeSharedData& data2 = *data1.Clone()->As<ScopeSharedData>();
			Assert::AreEqual(data2.Depth(), data1.Depth());
			AnonymousEngine::Scope& scope1 = *(data2.mScope);
			AnonymousEngine::Scope& scope2 = *(data1.mScope);
			Assert::AreEqual(0U, data2.Depth());
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
		static const AnonymousEngine::Vector<std::string> InvalidXmls;
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
					<matrix name=\"transform\">\
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

	const AnonymousEngine::Vector<std::string> ScopeXmlParserTest::InvalidXmls = {
		"<scope></scope>",
		"<integer name=\"age\" value=\"10\"/>"
	};

	const AnonymousEngine::Vector<std::string> ScopeXmlParserTest::TestXmlFiles = {
		"TestData/scope.xml"
	};

	const std::string ScopeXmlParserTest::TestScopeDataString = "{\"sector1\": {\"entity1\": {\"name\": \"hero\", \"age\": \"27\", \"attack\": \"10.500000\", \"position\": \"0.500000,10.200000,100.000000,1.000000\", \"transform\": \"1.200000,10.200000,0.005000,1.000000,3.600000,102.000000,0.010000,1.000000,1000.000000,177.199997,101.000000,1.000000,11.000000,13.600000,100.000351,1.000000\"}, \"entity2\": {\"name\": \"minion\", \"position\": \"50.400002,12.300000,10.000000,1.000000\"}}, \"sector2\": {\"entity100\": {\"name\": \"boss\", \"position\": \"77.040001,27.900000,20.000000,1.000000\"}}, \"sectors\": \"2\"}";
}
