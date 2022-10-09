
cmake_minimum_required (VERSION 3.8)

#set the project name
project ("RunBenchmark")

# Add source to this project's executable.
add_executable (RunBenchmark
	"Logger.cpp" "Logger.hpp"
	"Benchmark.cpp" "Benchmark.hpp"
	"OneFunction.cpp" "TenFunction.cpp" "IndexOfFunc.cpp" "TestFunctions.hpp"
	"Main.cpp")

