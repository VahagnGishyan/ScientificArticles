
package main

import "fmt"
import "time"
import "os"
import "strconv"

func panic_func() {
	panic("")
}

func foo0() { panic_func() }
func foo1() { foo0() }
func foo2() { foo1() }
func foo3() { foo2() }
func foo4() { foo3() }
func foo5() { foo4() }
func foo6() { foo5() }
func foo7() { foo6() }
func foo8() { foo7() }
func foo9() { foo8() }

func run() {
        defer func() {
                if err := recover(); err != nil {
			// handling
		}
        }()
	foo9()
}

func check(e error) {
    if e != nil {
        panic(e)
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

func benchmark_overhead() int {
	result := 0
	const size = 10000
	for index := 0; index < size; index++ {
		start := time.Now()
	        end := time.Now()
		elapsed := end.Sub(start)
		result += int(elapsed.Nanoseconds())
	}
	result /= size
	return result
}

func benchmark_save_results(test Test, result []int, file *os.File) {
	avg := 0

	for index := 0; index < test.testCount; index++ {
		file.WriteString("[" + strconv.Itoa(index) + "] " + strconv.Itoa(result[index]) + " nsecs\n")
		fmt.Println("[" + strconv.Itoa(index) + "] " + strconv.Itoa(result[index]) + " nsecs")

		avg += result[index]
	}
	fmt.Println()
	file.WriteString("\n")

	avg /= test.testCount
	file.WriteString ("Avg is " + strconv.Itoa(avg) + " nsecs\n\n")
	fmt.Println("Avg is " + strconv.Itoa(avg) + " nsecs\n")

	overhead := benchmark_overhead()
	file.WriteString ("Overhead is " + strconv.Itoa(overhead) + "\n")
	fmt.Println("Overhead is " + strconv.Itoa(overhead))
}

func benchmark_main(test Test) {
	result := make([]int, test.testCount)

	filepath := "benchmark_" + "golang_" + test.name + ".txt"
	file, err := os.Create(filepath)
	check(err)
	defer file.Close()

	file.WriteString("Dureationis for test case " + test.name + " { ")
	fmt.Print ("Dureationis for test case " + test.name + " { ")

	for itest := 0; itest < test.testCount; itest++ {
		for iiter := 0; iiter < test.iterCount; iiter++ {
			start := time.Now()
			run()
			end := time.Now()

			elapsed := end.Sub(start)
			result[itest] += int(elapsed.Nanoseconds())
		}
		result[itest] /= test.iterCount

		if ((itest % int(test.testCount / 10)) == 0) {
			file.WriteString("#");
			fmt.Print("#");
		}
	}
	fmt.Println (" }\n")
	file.WriteString(" }\n\n")

	benchmark_save_results(test, result, file)

	file.WriteString("\n")
}


type Test struct {
	testCount int
	iterCount int
	name	  string
}

func main() {
	fmt.Println("Start main()\n")

	var test Test
	test.name = "ten_function"
	test.testCount = 10
	test.iterCount = 1000000

	benchmark_main(test)
	fmt.Println("\nClose main()")
}

