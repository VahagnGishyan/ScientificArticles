
//Compilation mods
//DEBUG
//RELEASE

#include "dsrc_ptr.h"
#include "errlog.h"
#include "test.h"

///////////////////////////////////////////////
//
// Mods
//
 //#define NO_RUN_MAIN		// no run function run_main
//
// #define RUN_TESTS_SUCCES // run success tests
 //#define RUN_TESTS_FAIL   // run fail tests
// #define RUN_TESTS		// run succes and fail tests
///////////////////////////////////////////////
#ifndef NO_RUN_MAIN
void run_main(const int, char**); 
#endif
///////////////////////////////////////////////

int main(int argc, char** argv)
{
	std::cout << "Start main()" << std::endl;

	try
	{
#if defined RUN_TESTS || defined RUN_TESTS_SUCCES
		test::success_run();
#endif

#if defined RUN_TESTS || defined RUN_TESTS_FAIL
		test::fail_run();
#endif

#ifndef NO_RUN_MAIN
		run_main(argc, argv); 
#endif
	}
	catch (const std::string& message)
	{
		errlog::writeln(std::string("main catch exception type string, messige is ") + message);
	}
	catch(...)
	{
		errlog::writeln("main catch unknown type exception");
	}
	std::cout << "Close main()" << std::endl;
	return (0);
}

///////////////////////////////////////////////

#ifndef NO_RUN_MAIN

void run_main(const int argc, char** argv)
{

}

#endif
///////////////////////////////////////////////
