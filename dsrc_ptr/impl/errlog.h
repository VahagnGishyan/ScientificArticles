#pragma once

#include <iostream>
#include <string>

namespace dsrc
{
	namespace errlog
	{
		void writeln();
		void writeln(const std::string& message);
		void writeln(std::string&& message);
	}
}