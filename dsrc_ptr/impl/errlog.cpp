
#include "errlog.h"

namespace dsrc
{
	namespace errlog
	{
		void writeln()
		{
			std::cout << std::endl;
		}

		void writeln(const std::string& message)
		{
			std::cout << message << std::endl;
		}

		void writeln(std::string&& message)
		{
			std::cout << message << std::endl;
		}
	}
}