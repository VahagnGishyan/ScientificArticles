
#include "Logger.hpp"

namespace PerformanceTesting
{
	Logger::Logger() /*{ except { std::string } }*/
	{

	}

	void Logger::Prepare()
	{
		std::string path = LogDirPath + "messages.txt";
		file.open(path);
		if (!file)
		{
			throw(std::string("Can't open file[") + path + "]");
		}
	}

	void Logger::WriteLine()
	{
		std::cout << std::endl;
		file << std::endl;
	}

	void Logger::Write(const char symbol)
	{
		std::cout << symbol;
		file << symbol;
	}
	void Logger::WriteLine(const char symbol)
	{
		std::cout << symbol << std::endl;
		file << symbol << std::endl;
	}

	void Logger::Write(const std::string& message)
	{
		std::cout << message;
		file << message;
	}
	void Logger::Write(const std::string&& message)
	{
		std::cout << message;
		file << message;
	}

	void Logger::WriteLine(const std::string& message)
	{
		std::cout << message << std::endl;
		file << message << std::endl;
	}
	void Logger::WriteLine(const std::string&& message)
	{
		std::cout << message << std::endl;
		file << message << std::endl;
	}
}

std::ofstream PerformanceTesting::Logger::file;
const std::string PerformanceTesting::Logger::LogDirPath = "D:/Projects/Temp/test6/loging/";
