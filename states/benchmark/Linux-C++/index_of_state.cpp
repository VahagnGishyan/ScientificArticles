
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <memory> // always use smart pointers

//////////////////////////////////////////////////////////////

struct Test {
	int    testCount;
	int    iterCount;
	std::string name;
};

//////////////////////////////////////////////////////////////

enum class /*state*/ ErrorStates
{
        Unset,
        IncorrectInput,
	NotFound
};

int index_of(const char* const array, const char symbol, ErrorStates& state)
{
	if (array == nullptr)
        {
        	state = ErrorStates::IncorrectInput;
		return (-1);
       	}

        int index = 0;
        while (array[index] != '\0')
        {
        	if (array[index] == symbol)
                {
                	return (index);
                }
                ++index;
        }
	state = ErrorStates::NotFound;
	return (-1);
}

void run()
{
        const char* const array[] = { nullptr, "", "a", "abc", "qwertyuiopasdfghjklzxcvbnm" };
        char symbols[] = { 'a', '0', '=' };

        const int sarr = sizeof(array) / sizeof(array[0]);
        const int ssym = sizeof(symbols) / sizeof(symbols[0]);
        for (int iarr = 0; iarr < sarr; ++iarr)
  	{
                for (int isym = 0; isym < ssym; ++isym)
           	{
			ErrorStates state = ErrorStates::Unset;
    	              	index_of(array[iarr], symbols[isym], state);
      			if(state == ErrorStates::IncorrectInput)
       			{
       	        		//handling
        		}
			else if (state == ErrorStates::NotFound)
			{	
       	        		//handling
			}
        	}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////

int benchmark_overhead()
{
	const int size = 10000;
	std::chrono::nanoseconds duration = std::chrono::nanoseconds::zero();
	for (int index = 0; index < size; ++index)
	{
		auto start = std::chrono::system_clock::now();
                auto end = std::chrono::system_clock::now();
		duration += (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start));
	}
	return (duration.count() / size);
}

void benchmark_save_results(const Test& test, const std::vector<long>& result, std::ofstream& file)
{
	int avg = 0;

	for (int index = 0; index < test.testCount; ++index)
	{
		file << "[" << index << "] " << result[index] 
		     << " nsecs" << std::endl;
		std::cout << "[" << index << "] " << result[index] 
		     << " nsecs" << std::endl;
		
		avg += result[index];
	}
	
	file << std::endl;
	std::cout << std::endl;

	avg /= test.testCount;
	file << "Avg is " << avg << " nsecs" << std::endl;
	std::cout << "Avg is " << avg << " nsecs" << std::endl;
	
	const long overhead = benchmark_overhead();
	file << "Overhead is " << overhead << std::endl;
	std::cout << "Overhead is " << overhead << std::endl;
}

void benchmark_main(const Test& test)
{
	using std::cout;
	
	std::vector<long> result;
	result.resize(test.testCount);
	
	std::string filepath = std::string("benchmark_") + "cpp_" + test.name + ".txt"; 
	std::ofstream file;
       	file.open(filepath);
	if (!file)
	{
		throw std::string("Can't open file{" + filepath + "}");
	}	
        
	file << "Dureations for test case " << test.name << std::endl;
	cout << "Dureations for test case " << test.name << std::endl;


	for (int itest = 0; itest < test.testCount; ++itest)
	{
		file << "[" << itest << "] " << "{ ";
		cout << "[" << itest << "] " << "{ ";
		
		std::chrono::nanoseconds duration = std::chrono::nanoseconds::zero();
		for (int iiter = 0; iiter < test.iterCount; ++iiter)
		{
			auto start = std::chrono::system_clock::now();
        		run();
                        auto end = std::chrono::system_clock::now();
                       	duration += (std::chrono::duration_cast
			<std::chrono::nanoseconds>(end - start));

                        if (/*(test.iterCount <= 10 && iiter <= 10) ||*/ ((iiter + 1) % (test.iterCount / 10) == 0))
                        {
                                file << '#';
                                cout << '#';
                        }
               	}
                file << " }" << std::endl;
                cout << " }" << std::endl;

                result[itest] = (duration.count() / test.iterCount);
	}
	
	file << std::endl;
	cout << std::endl;

	benchmark_save_results(test, result, file);
	file << std::endl;
}


int main()
{
	std::cout << "Start \"index_of_func_state\" main()" << std::endl;
	
	Test test;
	test.name = "index_of_function_state";
	test.testCount = 10;
	test.iterCount = 1000000;

	benchmark_main(test);
	
	std::cout << "Close main()" << std::endl;
	return (0);
}

