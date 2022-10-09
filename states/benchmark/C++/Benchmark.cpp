
#include "Benchmark.hpp"

namespace PerformanceTesting
{
	Settings::Settings(const long count, const long iterCount) :
		m_count(count), m_iterCount(iterCount) { }
	Settings::Settings(const long count) :
		m_count(count), m_iterCount(1) { }
	Settings::~Settings() {}

	////////////////////////////////////////////////////////////////////////////////////////////

	const long         Settings::GetTestCount()     const { return (m_count); }
	const long         Settings::GetTestIterCount() const { return (m_iterCount); }

	////////////////////////////////////////////////////////////////////////////////////////////

	static const long Overhead()
	{
		using namespace std::chrono;
		constexpr int count = 1000000;
		std::chrono::nanoseconds duration = std::chrono::nanoseconds::zero();
		std::chrono::time_point<std::chrono::system_clock> start, end;
		for (int index = 0; index < count; ++index)
		{
			start = system_clock::now();
			end = system_clock::now();
			duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		}
		return (duration.count() / count);
	}

	const long GetOverhead()
	{
		static const long result = Overhead();
		return (result);
	}

	////////////////////////////////////////////////////////////////////////////////////////////

	Results::Results(const TestInfo& tinfo, const Settings& settings) : 
		m_testinfo(tinfo), m_settings(settings)
	{
		const unsigned int tcount  /*test count*/ = settings.GetTestCount();
		const unsigned int ticount /*test iteration count*/ = settings.GetTestCount();
		m_results.resize(tcount);

		for (auto& element : m_results)
		{
			element = 0;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////

	Results::CaseResult& Results::operator[](const int index)
	{
		auto front = m_results.begin();
		std::advance(front, index);
		return (*front);
	}

	const Results::CaseResult Results::operator[](const int index) const
	{
		auto front = m_results.begin();
		std::advance(front, index);
		return (*front);
	}

	//////////////////////////////////////////////////////////////////////////////////

	const Results::Container& Results::GetContainer() const { return (m_results); }
	const TestInfo& Results::GetTestInfo() const { return (m_testinfo); }
	const Settings& Results::GetSettings() const { return (m_settings); }

	//////////////////////////////////////////////////////////////////////////////////

	std::string GetOS()
	{
#ifdef __linux__ 
		return ("linux");
#elif _WIN32
		return ("windows");
#else
		return ("unknown"); // temp
#endif
	}

	std::string GetBuildMod()
	{
#ifdef __linux__ 
#ifdef  DEBUG
		return ("debug");
#else   // RELEASE 
		return ("release");
#endif
#elif _WIN32
#ifdef  _DEBUG
		return ("debug");
#else   // RELEASE 
		return ("release");
#endif
#else
		return ("unknown"); // temp 
#endif
	}

	static std::string GetFilePath(const std::string& testCaseName)
	{
		std::string filename = "results_";
		std::string osystem  = GetOS() + '_'; // or windows
		std::string buildmod = GetBuildMod() + '_'; // or release
		return (Logger::LogDirPath + filename + osystem + buildmod + testCaseName + ".txt");
	}

	std::string ToUpper(const std::string& value)
	{
		std::string duplicate = value;
		std::transform(duplicate.begin(), duplicate.end(), duplicate.begin(), [](unsigned char c) { return std::toupper(c); });
		return (duplicate);
	}

	static void SaveTestCaseInfo(std::ofstream& file, const Results& results)
	{
		file << '[' << ToUpper(GetBuildMod()) << ']' << std::endl;
		file << "Performance testing { " << results.GetTestInfo().GetName() << " } " << std::endl;
		file << "Settings :: TestCount { " << results.GetSettings().GetTestCount() << " } and " <<
			"IterCount { " << results.GetSettings().GetTestIterCount() << " }" << std::endl;
		file << "Overhead[std::chrono] :: " << GetOverhead() << "ns" << std::endl;
		file << std::endl;
	}

	static void SaveResults(std::ofstream& file, const Results& results)
	{
		const int size = results.Size();
		for (int index = 0; index < size; ++index)
		{
			file << "Test [" << index << "] :: " << results[index] << "ns"  << std::endl;
		}
		file << std::endl;
	}

	static void SaveDetails(std::ofstream& file, const Results& results)
	{
		file << "More details" << std::endl;
		auto durations = results.GetContainer();
		long long awg =  std::accumulate(durations.begin(), durations.end(), 0) / durations.size();
		long long max = *std::max_element(durations.begin(), durations.end());
		long long min = *std::min_element(durations.begin(), durations.end());

		file << "AWG of Test Case :: " << awg << "ns" << std::endl;
		file << "MAX of Test Case :: " << max << "ns" << std::endl;
		file << "MIN of Test Case :: " << min << "ns" << std::endl;
	}

	void Results::Save() const
	{
		std::string filepath = GetFilePath(m_testinfo.GetName());
		std::ofstream file;
		file.open(filepath);
		if (!file)
		{
			throw(std::string("Can't open file[") + filepath + "]");
		}

		SaveTestCaseInfo(file, *this);
		SaveResults(file, *this);
		SaveDetails(file, *this);

		file.close();
	}

	const unsigned int Results::Size() const
	{
		return (m_results.size());
	}

	//////////////////////////////////////////////////////////////////////////////////

	TestInfo::TestInfo(const std::string& name) : m_name(name) { }

	const std::string& TestInfo::GetName() const { return (m_name); }

	//////////////////////////////////////////////////////////////////////////////////

	Test::Test(const std::string& name, const Settings& settings) : TestInfo(name), m_settings(settings)
	{ }

	Test::~Test() {}

	//////////////////////////////////////////////////////////////////////////////////

	void Benchmark::SaveResults(const Benchmark::ResultListContent& results)
	{
		for (auto& element : results)
		{
			(*element).Save();
		}
	}

	Benchmark::~Benchmark() {}

	//////////////////////////////////////////////////////////////////////////////////

	Benchmark::ResultList Benchmark::RunTest()
	{
		ResultList results = std::make_unique<ResultListContent>();
		for (const auto& testcase : testcases)
		{
			(*results).push_back(testcase->Run());
		}
		return (std::move(results));
	}

	//////////////////////////////////////////////////////////////////////////////////
}

//
//	std::chrono::nanoseconds Settings::CalculateOverhead() const
//	{
//		using namespace std::chrono;
//		constexpr int count = 1000000;
//		std::chrono::nanoseconds duration = Timer::zero();
//		std::chrono::time_point<std::chrono::system_clock> start, end;
//		for (int index = 0; index < count; ++index)
//		{
//			start = system_clock::now();
//			end   = system_clock::now();
//			duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
//		}
//		return (duration / count);
//	}
