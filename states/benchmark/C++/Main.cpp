
#include <iostream>
#include <thread>

#include "Benchmark.hpp"
#include "TestFunctions.hpp"

int main()
{
	PerformanceTesting::Logger::Prepare();
	PerformanceTesting::Logger::WriteLine("Start main()");

	PerformanceTesting::Settings settings(10, 1000000);

	PerformanceTesting::Benchmark benchmark;
	{
		//benchmark.CreateTestCase<TestFunctions::OneFunction::Enum::RunExcept>     ("one_func_except_enum", settings);
		//benchmark.CreateTestCase<TestFunctions::OneFunction::Enum::RunState>      ("one_func_state_enum",  settings);

		//benchmark.CreateTestCase<TestFunctions::OneFunction::SameType::RunExcept> ("one_func_except_same", settings);
		//benchmark.CreateTestCase<TestFunctions::OneFunction::SameType::RunState>  ("one_func_state_same",  settings);

		//benchmark.CreateTestCase<TestFunctions::OneFunction::SomeTypes::RunExcept>("one_func_except_some", settings);
		//benchmark.CreateTestCase<TestFunctions::OneFunction::SomeTypes::RunState> ("one_func_state_some",  settings);
	}


	{
		//benchmark.CreateTestCase<TestFunctions::TenFunction::Enum::RunExcept>     ("ten_func_except_enum", settings);
		//benchmark.CreateTestCase<TestFunctions::TenFunction::Enum::RunState>      ("ten_func_state_enum",  settings);

		//benchmark.CreateTestCase<TestFunctions::TenFunction::SameType::RunExcept> ("ten_func_except_same", settings);
		//benchmark.CreateTestCase<TestFunctions::TenFunction::SameType::RunState>  ("ten_func_state_same",  settings);

		//benchmark.CreateTestCase<TestFunctions::TenFunction::SomeTypes::RunExcept>("ten_func_except_some", settings);
		//benchmark.CreateTestCase<TestFunctions::TenFunction::SomeTypes::RunState> ("ten_func_state_some",  settings);
	}

	{
		benchmark.CreateTestCase<TestFunctions::IndexOfFunc::RunExcept>     ("index_of_except", settings);
		benchmark.CreateTestCase<TestFunctions::IndexOfFunc::RunState>      ("index_of_state",  settings);
	}

	PerformanceTesting::Benchmark::ResultList smresults = benchmark.RunTest();
	PerformanceTesting::Benchmark::SaveResults(*smresults);

	PerformanceTesting::Logger::WriteLine("Close main()");
}
