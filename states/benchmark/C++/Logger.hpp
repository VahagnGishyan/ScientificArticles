
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <memory> // always use smart pointers

namespace PerformanceTesting
{
	class Logger
	{
	private:
		Logger(); /*{ except { std::string } }*/

		//Logger(const std::string& path) /*{ except { std::string } }*/
		//{
		//	file.open(path);
		//	if (!file)
		//	{
		//		throw(std::string("Can't open file[") + path + "]");
		//	}
		//}
		//Logger(std::string&& path)
		//	/* except { std::string } */
		//{
		//	file.open(path);
		//	if (!file)
		//	{
		//		throw(std::string("Can't open file[") + path + "]");
		//	}
		//}
		//~Logger()
		//{
		//	file.close();
		//}

		////////////////////////////////////////////////////////////////////////////////////////////

	public:
		static void Prepare();

	public:
		static void WriteLine();

		static void Write(const char symbol);
		static void WriteLine(const char symbol);

		static void Write(const std::string& message);
		static void Write(const std::string&& message);

		static void WriteLine(const std::string& message);
		static void WriteLine(const std::string&& message);

	private:
		static std::ofstream file;
	public:
		static const std::string LogDirPath;
	};
}

