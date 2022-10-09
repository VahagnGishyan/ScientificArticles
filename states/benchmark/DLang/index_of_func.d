
import std.stdio;
import std.string;
import std.datetime;
import std.datetime.stopwatch : benchmark, StopWatch;

        
class IncorrectInput : Exception
{
    this(string msg, string file = __FILE__, size_t line = __LINE__) {
        super(msg, file, line);
    }
}

class NotFound : Exception
{
    this(string msg, string file = __FILE__, size_t line = __LINE__) {
        super(msg, file, line);
    }
}

int index_of(const char[] array, const char symbol)
{
	if(array == null)
	{
		throw new IncorrectInput("");
	}

	for (int index = 0; index < array.length; ++index)
	{
		if(array[index] == symbol)
		{
			return (index);
		}
		++index;
	}
	
	throw new NotFound("");
}

       
void run()
{
	auto array   = [ "",  null, "a", "abc", "qwertyuiopasdfghjklzxcvbnm" ];
	auto symbols = [ 'a', '0', '=' ];

	const ulong sarr = array.length;
	const ulong ssym = symbols.length;
	for (ulong iarr = 0; iarr < sarr; ++iarr)
	{
		for(ulong isym = 0; isym < ssym; ++isym)
		{
			try
			{
				index_of(array[iarr], symbols[isym]);
			}
			catch(IncorrectInput obj) { /*handling*/ }
			catch(NotFound obj) { /*handling*/ }
		}
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
	        	run();
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
	test.name = "index_of";
	test.testCount = 10;
	test.iterCount = 100000;
	try
	{
		benchmark_main(test);
	}
	catch(Exception error)
	{	
		writefln("catch exception{type Exception} in main with message %s", error.msg);
	}

	writeln("\nClose main()");
	return (0);
}

