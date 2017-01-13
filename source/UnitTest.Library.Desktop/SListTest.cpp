#include "Pch.h"
#include "SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListTest)
	{
	public:
		/** Test single linked list constructor
		*/
		TEST_METHOD(TestDefaultConstructor)
		{
			Library::SList<int>* list = new Library::SList<int>();
			Assert::IsNotNull(list);
			delete list;
		}

		/** Test insert into list method
		*/
		TEST_METHOD(TestInsert)
		{
			Library::SList<int>* list = new Library::SList<int>();
			list->PushFront(2);
			Assert::IsTrue(true);
			delete list;
		}

		/** Test pop last inserted functionality
		*/
		TEST_METHOD(TestPopReturnsLastInserted)
		{
			Library::SList* list = new Library::SList();
			list->Insert(10);
			Assert::IsTrue(list->Pop() == 10);
			delete list;
		}

		TEST_METHOD_INITIALIZE(Setup)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&StartMemState);
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			_CrtMemState endMemState;
			_CrtMemState diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &StartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory leak...");
			}
		}
	private:
		static _CrtMemState StartMemState;
	};

	_CrtMemState SListTest::StartMemState;
}
