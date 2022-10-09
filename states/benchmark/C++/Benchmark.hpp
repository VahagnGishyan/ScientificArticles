#pragma once

//////////////////////////////////////////////////////////////////////////

#include "Logger.hpp"

//////////////////////////////////////////////////////////////////////////

//#define DEBUG_MODE
//#define ENV_NAME_DEBUG_LOG_SET  "DEBUG_LOG_SET"
//#define ENV_VALUE_DEBUG_LOG_ON  "ON"
//#define ENV_VALUE_DEBUG_LOG_OFF "OFF"

//////////////////////////////////////////////////////////////////////////

namespace PerformanceTesting
{

	class Settings
	{
	public:

		Settings(const long count, const long iterCount);
		Settings(const long count);
		virtual ~Settings();

		////////////////////////////////////////////////////////////////////////////////////////////

		const long         GetTestCount() const;
		const long         GetTestIterCount() const;

		////////////////////////////////////////////////////////////////////////////////////////////

	private:
		long        m_count;
		long        m_iterCount;
	};

	class TestInfo
	{
	public:
		TestInfo(const std::string& name);

	public:
		const std::string& GetName() const;

	private:
		std::string	m_name;
	};

	class Results
	{
	private:
		using CaseResult = long long;
		using Container = std::list<CaseResult>;

	public:
		Results(const TestInfo& tinfo, const Settings& settings);

		////////////////////////////////////////////////////////////////////////////////////////////

	public:
		CaseResult& operator[](const int index);
		const CaseResult operator[](const int index) const;

		////////////////////////////////////////////////////////////////////////////////////////////

	public:
		const Container& GetContainer() const;
		const TestInfo&  GetTestInfo()  const;
		const Settings&  GetSettings()  const;

		////////////////////////////////////////////////////////////////////////////////////////////

	public:
		void Save() const;
		const unsigned int Size() const;

		////////////////////////////////////////////////////////////////////////////////////////////

	private:
		Container m_results;
		TestInfo  m_testinfo;
		Settings  m_settings;
	};

	using SmartResult = std::unique_ptr<Results>;

	class Test : public TestInfo
	{
	public:
		Test(const std::string& name, const Settings& settings);
		virtual ~Test();

		////////////////////////////////////////////////////////////////////////////////////////////

		virtual SmartResult Run() = 0;

		////////////////////////////////////////////////////////////////////////////////////////////

		const Settings& GetSettings() const { return (m_settings); }

		////////////////////////////////////////////////////////////////////////////////////////////

	protected:
		Settings	m_settings;
	};

	////////////////////////////////////////////////////////////////////////////////////////////

	template<void (*TestFunction)(void)>
	SmartResult TestRunner(
		const TestInfo& test,
		const Settings& settings)
	{
		SmartResult sm_results = std::make_unique<Results>(test, settings);
		Results& results = *sm_results;
		const int   tCount = settings.GetTestCount();
		const int   iCount = settings.GetTestIterCount();
		//const auto& overhead = settings.getOverhead();

		Logger::WriteLine(std::string("TestCase :: ") + test.GetName());

		for (int tIndex = 0; tIndex < tCount; ++tIndex)
		{
			Logger::Write('[' + std::to_string(tIndex) + "] :: { ");
			//Logger::WriteLine('[' + Tester::getIndexAsStringWithSpaces(tCount, tIndex) + "] :: { ");
			std::chrono::nanoseconds duration = std::chrono::nanoseconds::zero();

			for (int iIndex = 0; iIndex < iCount; ++iIndex)
			{
				auto start = std::chrono::system_clock::now();
				TestFunction();
				auto end = std::chrono::system_clock::now();
				duration += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start));

				if ((iCount <= 10 && iIndex <= 10) || ((iIndex + 1) % (iCount / 10) == 0))
				{
					Logger::Write('#');
				}
			}
			Logger::WriteLine('}');

			results[tIndex] = (duration.count() / iCount);
		}
		Logger::WriteLine();
		return (std::move(sm_results));
	}

	template<void (*TestFunction)(void)>
	SmartResult TestRunner(const Test& test)
	{
		SmartResult sm_results = std::make_unique<Results>(test, test.GetSettings());
		Results& results = *sm_results;
		const int   tCount = test.GetSettings().GetTestCount();
		const int   iCount = test.GetSettings().GetTestIterCount();
		//const auto& overhead = settings.getOverhead();

		Logger::WriteLine(std::string("TestCase :: ") + test.GetName());

		for (int tIndex = 0; tIndex < tCount; ++tIndex)
		{
			Logger::Write('[' + std::to_string(tIndex) + "] :: { ");
			//Logger::WriteLine('[' + Tester::getIndexAsStringWithSpaces(tCount, tIndex) + "] :: { ");
			std::chrono::nanoseconds duration = std::chrono::nanoseconds::zero();

			for (int iIndex = 0; iIndex < iCount; ++iIndex)
			{
				auto start = std::chrono::system_clock::now();
				TestFunction();
				auto end = std::chrono::system_clock::now();
				duration += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start));

				if ((iCount <= 10 && iIndex <= 10) || ((iIndex + 1) % (iCount / 10) == 0))
				{
					Logger::Write('#');
				}
			}
			Logger::WriteLine(" }");

			results[tIndex] = (duration.count() / iCount);
		}
		Logger::WriteLine();
		return (std::move(sm_results));
	}

	const long GetOverhead();

	////////////////////////////////////////////////////////////////////////////////////////////

	template <void (*TestFunction)(void)>
	class TestCase : public Test
	{
	public:
		TestCase(const std::string& name, const Settings& settings) : Test(name, settings)
		{ }

		virtual SmartResult Run() override
		{
			return (TestRunner<TestFunction>(*this));
		}
	};

	class Benchmark
	{
	public:
		template <typename Type>
		using Array = std::list<Type>;
		using ResultListContent = std::list<SmartResult>;
		using ResultList = std::unique_ptr<ResultListContent>;

		static void SaveResults(const ResultListContent& results);


	public:
		virtual ~Benchmark();

		//////////////////////////////////////////////////////////////////////////////////

	public:

		template <void (*TestFunction)(void)>
		void CreateTestCase(const std::string& name, const Settings& settings)
		{
			testcases.push_back(std::make_unique<PerformanceTesting::TestCase<TestFunction>>(name, settings));
		}

		//template <void (*TestFunction)(void)>
		//void CreateTestCase(const std::string& name, const int tcount, const int titrcount)
		//{
		//	testcases.push_back(std::make_unique<TestCase<TestFunction>>(name, Settings(tcount, titrcount)));
		//}

		//////////////////////////////////////////////////////////////////////////////////

		ResultList RunTest();

	private:
		Array <std::unique_ptr<Test>> testcases;
	};
}

//////////////////////////////////////////////////////////////////////////

