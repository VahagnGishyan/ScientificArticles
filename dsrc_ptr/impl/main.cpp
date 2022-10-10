
//Compilation mods
//DEBUG
//RELEASE

#include "dsrc_ptr.h"
#include "errlog.h"
#include "tests.h"

#include <list>
#include <algorithm>

int main()
{
	std::cout << "Start main()" << std::endl;

	try
	{
		dsrc::unique_test::success_run();
		dsrc::unique_test::fail_run();
		dsrc::shared_test::success_run();
		dsrc::shared_test::fail_run();
	}
	catch (const std::string& message)
	{
		dsrc::errlog::writeln(std::string("catch exception type string, messige is ") + message);
	}

	std::cout << "Close main()" << std::endl;
	return (0);
}
