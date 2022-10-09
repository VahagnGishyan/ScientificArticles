
import std.stdio;
import std.string;
import std.datetime;
import std.datetime.stopwatch : benchmark, StopWatch;

void throw_func()
{
	throw new Exception("");
}

void catch_func()
{
	try
	{
		throw_func();
	}
	catch(const Exception err)
	{
		//handling
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////

long benchmark_overhead()
{
	long result = 0;
	const int size = 10000;
	for (int index = 0; index < size; ++index)
	{
		auto sw = StopWatch(AutoStart.no);
       		sw.start();
        	sw.stop();
		result += sw.peek.total!"nsecs"; 
	}
	result /= size;
	return (result);
}

void benchmark_save_results(Test test, const long[] result, File* file)
{
	long avg = 0;

	for (int index = 0; index < test.testCount; ++index)
	{
		file.writefln("[%d] %d %s", index, result[index], "nsecs");
		writefln("[%d] %d %s", index, result[index], "nsecs");
		
		avg += result[index];
	}
	writeln();	
	file.writeln();	

	avg /= test.testCount;
	file.writefln("Avg is %d nsecs", avg);
	writefln("Avg is %d nsecs", avg);	
	
	writeln();	
	file.writeln();	
	const long overhead = benchmark_overhead();
	file.writefln("Overhead is %d", overhead);
	writefln("Overhead is %d", overhead);	
}

void benchmark_main(Test test)
{
	long[] result = new long[test.testCount];
	
	string filepath = "benchmark_" ~ "dlang_" ~ test.name ~ ".txt"; 
	File file = File(filepath, "w"); 
        
	file.writef("Dureationis for test case %s { ", test.name);
	writef("Dureationis for test case %s { ", test.name);
	
	//writefln("test count is %d", test.testCount);
	//writefln("iter count is %d", test.iterCount);

	for (int itest = 0; itest < test.testCount; ++itest)
	{
		//writef("[%d] : ", itest);
		for (int iiter = 0; iiter < test.iterCount; ++iiter)
		{
			//write('*');
			auto sw = StopWatch(AutoStart.no);
       			sw.start();
	        	catch_func();
        		sw.stop();
               		result[itest] += sw.peek.total!"nsecs";
		}
		//writeln();
		result[itest] /= test.iterCount;
		
		if ((itest % (test.testCount * 0.1)) == 0)
		{
			file.write('#');
			write('#');
		}
	}
	writeln(" }\n");
	file.writeln(" }\n");

	benchmark_save_results(test, result, &file);

	file.writeln();	
	file.close();
}


struct Test {
	int    testCount;
	int    iterCount;
	string name;
}

int main()
{
	writeln("Start main()\n");
	
	Test test;
	test.name = "one_function";
	test.testCount = 10;
	test.iterCount = 1000000;

	benchmark_main(test);
	writeln("\nClose main()");
	return (0);
}

