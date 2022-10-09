
use std::time::SystemTime;
use std::time::Duration;
use std::convert::TryInto;
use std::fs::File;
use std::io::Write;

fn create_err() -> Result<i32, String> {
    return Err("".to_string());
}

fn run() {
    let result = create_err();
    match result {
        Ok(val)=>{
            // something
        },
        Err(message)=>{
            // handling
        }
    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////

fn benchmark_overhead() -> u128
{
	let mut result: u128 = 0;
	let size: i32 = 10000;
	
    let mut start = SystemTime::now();
    let mut end = SystemTime::now();
    for index in 1..=size {
	    start = SystemTime::now();
	    end = SystemTime::now();

        let dur :Duration = end.duration_since(start)
        .expect("Clock may have gone backwards"); 
		
        result += dur.as_nanos();
	}
	result /= size as u128;
	return result;
}
/*
fn benchmark_save_results(test :Test, result: Vec<u128>, mut file :File)
{
	
}
*/
fn benchmark_main(test: Test) -> std::io::Result<()> {
	let mut result :Vec<u128> = vec![0; (test.testCount as usize).try_into().unwrap()];
	
	let mut filepath :String = String::from("benchmark_");
    
    filepath.push_str("dlang_");
    filepath = format!("{}{}", filepath, test.name);
    filepath.push_str(".txt"); 
	
    let mut file = File::create(filepath)?;

	file.write_all(format!("Dureationis for test case {} {{ ", test.name).as_bytes())?;
	print!("Dureationis for test case {} {{ ", test.name);
    
    let mut start = SystemTime::now();
    let mut end = SystemTime::now();
	for itest in 0..test.testCount {
		result[itest as usize] = 0; 
        for iiter in 0..test.iterCount {
       	    start = SystemTime::now();
            run();
            end = SystemTime::now();
		    let dur :Duration = end.duration_since(start)
                .expect("Clock may have gone backwards"); 
	        	
            result[itest as usize] += dur.as_nanos() as u128;
		    //println!{"\tdifference is {dur:?}"};
            //println!("\tresult is {}", result[itest as usize]);
        }
        //println!("result is {}, count is {}", result[itest as usize], test.iterCount as u128);
        result[itest as usize] /= test.iterCount as u128;
		if (itest % (test.testCount / 10)) == 0 {
			file.write_all(b"#")?;
			print!("{}", '#');
		}
	}
	println!(" }}\n");
	file.write_all(b" }\n\n")?;

    {
        let mut avg :u128 = 0;

	    for index in 0..test.testCount {
		    file.write_all(format!("[{}] {} nsecs\n", index, result[index as usize]).as_bytes());
		    println!("[{index:?}] {} nsecs", result[index as usize]);
		    avg += result[index as usize];
	    }
	    println!();	
	    file.write_all(b"\n");	

	    avg /= test.testCount as u128;
	    file.write_all(format!("Avg is {} nsecs\n", avg).as_bytes());
	    println!("Avg is {} nsecs", avg);	
	
	    println!();	
	    file.write_all(b"\n");	
	    let overhead: i32 = benchmark_overhead().try_into().unwrap();
	    file.write_all(b"Overhead is {overhead})");
	    println!("Overhead is {}", overhead);	
    }

	file.write_all(b"\n")?;
    Ok(())
}


struct Test {
    pub testCount: i32,
	pub iterCount: i32,
	pub name: String,
}

impl Test {
    pub fn new(testCount :i32, iterCount :i32, name: String) -> Self {
        Self {
            testCount,
            iterCount,
            name,
        }
    }
}

fn main() {
	println!("Start main()\n");
	
	let mut test :Test = Test::new(10 as i32, 1000000 as i32, String::from("one_function")); 
	//test.testCount = 10;
	//test.iterCount = 1000000;
	//test.name = String::from("one_function").clone();

	benchmark_main(test);
	println!("\nClose main()");
}

