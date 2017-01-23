#include "Pch.h"
#include "SList.h"
#include "Foo.h"
#include "ToStringTemplates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListIteratorTest)
	{
	public:
		TEST_METHOD(TestIteration)
		{
			// primitive type test
			{
				std::uint32_t testData[3];
				AnonymousEngine::SList<std::uint32_t> list;
				for (std::uint32_t i = 0; i < 3; i++)
				{
					testData[i] = static_cast<std::uint32_t>((*mDistribution)(*mGenerator));
					list.PushBack(testData[i]);
				}
				std::uint32_t index = 0;
				for (auto value : list)
				{
					Assert::AreEqual(testData[index], value);
					index++;
				}
			}
			// pointer type test
			{
				std::uint32_t testData[3];
				AnonymousEngine::SList<std::uint32_t*> list;
				for (std::uint32_t i = 0; i < 3; i++)
				{
					testData[i] = (*mDistribution)(*mGenerator);
					list.PushBack(&testData[i]);
				}
				std::uint32_t index = 0;
				for (auto value : list)
				{
					Assert::AreEqual(&testData[index], value);
					index++;
				}
			}
			// user defined type test
			{
				std::uint32_t testData[3];
				AnonymousEngine::SList<Foo> list;
				for (std::uint32_t i = 0; i < 3; i++)
				{
					testData[i] = static_cast<std::uint32_t>((*mDistribution)(*mGenerator));
					list.PushBack(Foo(testData[i]));
				}
				std::uint32_t index = 0;
				for (auto value : list)
				{
					Assert::AreEqual(Foo(testData[index]), Foo(value));
					index++;
				}
			}
		}

		TEST_METHOD(TestCopyConstructor)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(value);
				auto iterator1 = list.begin();
				auto iterator2 = iterator1;
				Assert::AreEqual(*iterator1, *iterator2);
				Assert::AreEqual(iterator1, iterator2);
			}
			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(&value);
				auto iterator1 = list.begin();
				auto iterator2 = iterator1;
				Assert::AreEqual(*iterator1, *iterator2);
				Assert::AreEqual(iterator1, iterator2);
			}
			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(Foo(value));
				auto iterator1 = list.begin();
				auto iterator2 = iterator1;
				Assert::AreEqual(*iterator1, *iterator2);
				Assert::AreEqual(iterator1, iterator2);
			}
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(value);
				auto iterator1 = list.begin();
				AnonymousEngine::SList<std::uint32_t>::Iterator iterator2;
				iterator2 = iterator1;
				Assert::AreEqual(*iterator1, *iterator2);
				Assert::AreEqual(iterator1, iterator2);
			}
			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(&value);
				auto iterator1 = list.begin();
				AnonymousEngine::SList<std::uint32_t*>::Iterator iterator2;
				iterator2 = iterator1;
				Assert::AreEqual(*iterator1, *iterator2);
				Assert::AreEqual(iterator1, iterator2);
			}
			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				std::uint32_t value = (*mDistribution)(*mGenerator);
				list.PushFront(Foo(value));
				auto iterator1 = list.begin();
				AnonymousEngine::SList<Foo>::Iterator iterator2;
				iterator2 = iterator1;
				Assert::AreEqual(*iterator1, *iterator2);
				Assert::AreEqual(iterator1, iterator2);
			}
		}

		TEST_METHOD(TestPostAndPreIncrementOperators)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				list.PushFront(value2);
				list.PushFront(value1);
				//test post increment
				auto iterator = list.begin();
				Assert::AreEqual(value1, list.Front());
				Assert::AreEqual(value1, *iterator);
				auto it = iterator++;
				Assert::AreEqual(value1, *it);
				Assert::AreEqual(value2, *iterator);
				// test pre increment
				iterator = list.begin();
				it = ++iterator;
				Assert::AreEqual(value2, *iterator);
				Assert::AreEqual(value2, list.Back());
			}
			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				list.PushFront(&value2);
				list.PushFront(&value1);
				//test post increment
				auto iterator = list.begin();
				Assert::AreEqual(&value1, list.Front());
				Assert::AreEqual(&value1, *iterator);
				auto it = iterator++;
				Assert::AreEqual(&value1, *it);
				Assert::AreEqual(&value2, *iterator);
				// test pre increment
				iterator = list.begin();
				it = ++iterator;
				Assert::AreEqual(&value2, *iterator);
				Assert::AreEqual(&value2, list.Back());
			}
			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				list.PushFront(Foo(value2));
				list.PushFront(Foo(value1));
				//test post increment
				auto iterator = list.begin();
				Assert::AreEqual(Foo(value1), list.Front());
				Assert::AreEqual(Foo(value1), *iterator);
				auto it = iterator++;
				Assert::AreEqual(Foo(value1), *it);
				Assert::AreEqual(Foo(value2), *iterator);
				// test pre increment
				iterator = list.begin();
				it = ++iterator;
				Assert::AreEqual(Foo(value2), *iterator);
				Assert::AreEqual(Foo(value2), list.Back());
			}
		}

		TEST_METHOD(TestIncrementOperatorsThrowsException)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list;
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				list.PushFront(value1);
				auto iterator = list.end();
				Assert::AreEqual(value1, list.Front());
				Assert::ExpectException<std::out_of_range>([&iterator]() { ++iterator; });
				Assert::ExpectException<std::out_of_range>([&iterator]() { iterator++; });
			}
			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list;
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				list.PushFront(&value1);
				auto iterator = list.end();
				Assert::AreEqual(&value1, list.Front());
				Assert::ExpectException<std::out_of_range>([&iterator]() { ++iterator; });
				Assert::ExpectException<std::out_of_range>([&iterator]() { iterator++; });
			}
			// user defined type test
			{
				AnonymousEngine::SList<Foo> list;
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				list.PushFront(Foo(value1));
				auto iterator = list.end();
				Assert::AreEqual(Foo(value1), list.Front());
				Assert::ExpectException<std::out_of_range>([&iterator]() { ++iterator; });
				Assert::ExpectException<std::out_of_range>([&iterator]() { iterator++; });
			}
		}

		TEST_METHOD(TestDereferenceOperator)
		{
			// primitive type test
			{
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				// Test for non const version
				AnonymousEngine::SList<std::uint32_t> list1;
				Assert::ExpectException<std::domain_error>([&list1]() { *(list1.begin()); });
				list1.PushFront(value1);
				Assert::AreEqual(value1, *(list1.begin()));
				list1.PushFront(value2);
				Assert::AreEqual(value2, *(list1.begin()));
				// Test for const version
				const AnonymousEngine::SList<std::uint32_t>::Iterator constIt(list1.begin());
				Assert::AreEqual(value2, *constIt);
				Assert::ExpectException<std::domain_error>([&list1]()
				{
					const AnonymousEngine::SList<std::uint32_t>::Iterator it;
					*it;
				});
			}
			// pointer type test
			{
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				// Test for non const version
				AnonymousEngine::SList<std::uint32_t*> list1;
				Assert::ExpectException<std::exception>([&list1]() { *(list1.begin()); });
				list1.PushFront(&value1);
				Assert::AreEqual(&value1, *(list1.begin()));
				list1.PushFront(&value2);
				Assert::AreEqual(&value2, *(list1.begin()));
				// Test for const version
				const AnonymousEngine::SList<std::uint32_t*>::Iterator constIt(list1.begin());
				Assert::AreEqual(&value2, *constIt);
				Assert::ExpectException<std::exception>([&list1]()
				{
					const AnonymousEngine::SList<std::uint32_t*>::Iterator it;
					*it;
				});
			}
			// user defined type test
			{
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				// Test for non const version
				AnonymousEngine::SList<Foo> list1;
				Assert::ExpectException<std::exception>([&list1]() { *(list1.begin()); });
				list1.PushFront(Foo(value1));
				Assert::AreEqual(Foo(value1), *(list1.begin()));
				list1.PushFront(Foo(value2));
				Assert::AreEqual(Foo(value2), *(list1.begin()));
				// Test for const version
				const AnonymousEngine::SList<Foo>::Iterator constIt(list1.begin());
				Assert::AreEqual(Foo(value2), *constIt);
				Assert::ExpectException<std::exception>([&list1]()
				{
					const AnonymousEngine::SList<Foo>::Iterator it;
					*it;
				});
			}
		}

		TEST_METHOD(TestEqualAndNotEqualOperators)
		{
			// primitive type test
			{
				AnonymousEngine::SList<std::uint32_t> list1;
				AnonymousEngine::SList<std::uint32_t> list2;
				list1.PushFront((*mDistribution)(*mGenerator));
				list2.PushFront((*mDistribution)(*mGenerator));
				//equals operator
				Assert::AreEqual(list1.begin(), list1.begin());
				Assert::AreEqual(list1.end(), list1.end());
				Assert::AreNotEqual(list1.begin(), list2.begin());
				Assert::AreNotEqual(list1.end(), list2.end());
				//not equals operator
				Assert::AreEqual(list1.begin(), list1.begin());
				Assert::AreEqual(list1.end(), list1.end());
				Assert::AreNotEqual(list1.begin(), list2.begin());
				Assert::AreNotEqual(list1.end(), list2.end());
				AnonymousEngine::SList<Foo>::Iterator it1;
				AnonymousEngine::SList<Foo>::Iterator it2;
				Assert::AreEqual(it1, it2);
				Assert::AreEqual(it1, it2);
			}
			// pointer type test
			{
				AnonymousEngine::SList<std::uint32_t*> list1;
				AnonymousEngine::SList<std::uint32_t*> list2;
				std::uint32_t value1 = (*mDistribution)(*mGenerator);
				std::uint32_t value2 = (*mDistribution)(*mGenerator);
				list1.PushFront(&value1);
				list2.PushFront(&value2);
				//equals operator
				Assert::AreEqual(list1.begin(), list1.begin());
				Assert::AreEqual(list1.end(), list1.end());
				Assert::AreNotEqual(list1.begin(), list2.begin());
				Assert::AreNotEqual(list1.end(), list2.end());
				//not equals operator
				Assert::AreEqual(list1.begin(), list1.begin());
				Assert::AreEqual(list1.end(), list1.end());
				Assert::AreNotEqual(list1.begin(), list2.begin());
				Assert::AreNotEqual(list1.end(), list2.end());
				AnonymousEngine::SList<Foo>::Iterator it1;
				AnonymousEngine::SList<Foo>::Iterator it2;
				Assert::AreEqual(it1, it2);
				Assert::AreEqual(it1, it2);
			}
			// user defined type test
			{
				AnonymousEngine::SList<Foo> list1;
				AnonymousEngine::SList<Foo> list2;
				list1.PushFront(Foo((*mDistribution)(*mGenerator)));
				list2.PushFront(Foo((*mDistribution)(*mGenerator)));
				//equals operator
				Assert::AreEqual(list1.begin(), list1.begin());
				Assert::AreEqual(list1.end(), list1.end());
				Assert::AreNotEqual(list1.begin(), list2.begin());
				Assert::AreNotEqual(list1.end(), list2.end());
				//not equals operator
				Assert::AreEqual(list1.begin(), list1.begin());
				Assert::AreEqual(list1.end(), list1.end());
				Assert::AreNotEqual(list1.begin(), list2.begin());
				Assert::AreNotEqual(list1.end(), list2.end());
				AnonymousEngine::SList<Foo>::Iterator it1;
				AnonymousEngine::SList<Foo>::Iterator it2;
				Assert::AreEqual(it1, it2);
				Assert::AreEqual(it1, it2);
			}
		}

		TEST_CLASS_INITIALIZE(BeginClass)
		{
			std::random_device mDevice;
			mGenerator = new std::default_random_engine(mDevice());
			mDistribution = new std::uniform_int_distribution<std::uint32_t>(0, UINT32_MAX);
		}

		TEST_CLASS_CLEANUP(EndClass)
		{
			delete mGenerator;
			delete mDistribution;
		}

#if _DEBUG
		TEST_METHOD_INITIALIZE(Setup)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&mStartMemState);
		}

		TEST_METHOD_CLEANUP(Teardown)
		{
			_CrtMemState endMemState;
			_CrtMemState diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &mStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory leak...");
			}
		}
	private:
		_CrtMemState mStartMemState;
#else
	private:
#endif
		static std::default_random_engine* mGenerator;
		static std::uniform_int_distribution<std::uint32_t>* mDistribution;
	};

	std::default_random_engine* SListIteratorTest::mGenerator;
	std::uniform_int_distribution<std::uint32_t>* SListIteratorTest::mDistribution;
}
