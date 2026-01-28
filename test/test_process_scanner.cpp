#include <testkit.h>
#include <process_scanner.h>
#include <unistd.h>

UnitTest(Test_Trim)
{
	assert(ProcessScanner::trim("   Hello World   ") == "Hello World");
	assert(ProcessScanner::trim("\n\t  Trim Me \r\n") == "Trim Me");
}

UnitTest(Test_ParseStatusFile_Valid)
{
	// 创建一个临时的 status 文件
	std::string temp_status_content =
		"Name:\tmy_process\n"
		"Pid:\t1234\n"
		"PPid:\t567\n";

	auto temp_file_path = "/tmp/test_status_file" + std::to_string(getpid()) + ".txt";
	std::ofstream temp_file(temp_file_path);
	temp_file << temp_status_content;
	temp_file.close();

	auto [process_info, parse_error] = ProcessScanner::ParseStatusFile(temp_file_path);
	assert(!parse_error.has_value());
	assert(process_info.pid == 1234);
	assert(process_info.ppid == 567);
	assert(process_info.process_name == "my_process");

	// 删除临时文件
	fs::remove(temp_file_path);
}

UnitTest(Test_ParseStatusFile_Invalid)
{
	// 测试不存在的文件
	auto [process_info, parse_error] = ProcessScanner::ParseStatusFile("/nonexistent/" + std::to_string(getpid()) + "/path/status");
	assert(parse_error.has_value());
}

UnitTest(Test_ScanProcess)
{
	auto processes = ProcessScanner::ScanProcess();
	assert(!processes.empty()); // Assuming there is at least one process running
}