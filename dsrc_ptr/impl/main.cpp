
//Compilation mods
//DEBUG
//RELEASE

#include "dsrc_ptr.h"
#include "errlog.h"
#include "test.h"

#include <list>
#include <algorithm>

int main()
{
	std::cout << "Start main()" << std::endl;

	try
	{
		test::success_run();
		test::fail_run();
	}
	catch (const std::string& message)
	{
		errlog::writeln(std::string("catch exception type string, messige is ") + message);
	}

	std::cout << "Close main()" << std::endl;
	return (0);
}
