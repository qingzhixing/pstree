#ifndef PROCESS_SCANNER_H
#define PROCESS_SCANNER_H

#include <fstream>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <vector>
#include <process_info.h>

namespace fs = std::filesystem;

class ProcessScanner
{
public:
	static std::string trim(const std::string &str)
	{
		size_t start = str.find_first_not_of(" \t\n\r");
		size_t end = str.find_last_not_of(" \t\n\r");

		if (start == std::string::npos)
		{
			return ""; // String is all whitespace
		}

		return str.substr(start, end - start + 1);
	}

	/**
	 * @brief 解析 /proc/[pid]/status 文件，获取进程信息
	 * @param status_file_path status 文件路径
	 * @return 解析得到的进程信息，或 解析错误信息
	 */
	static std::pair<ProcessInfo, std::optional<std::string>> ParseStatusFile(const fs::path &status_file_path)
	{
		if (!fs::exists(status_file_path) ||
			!fs::is_regular_file(status_file_path))
		{
			return {{}, "status 文件不存在 或 是目录"};
		}

		// 获取pid ppid name
		std::ifstream status_file(status_file_path);
		if (!status_file.is_open())
		{
			return {{}, "无法打开 status 文件"};
		}

		ProcessInfo process_info;
		std::string line;
		while (std::getline(status_file, line))
		{
			if (line.starts_with("Pid:"))
			{
				process_info.pid = std::stoi(line.substr(4));
			}
			else if (line.starts_with("PPid:"))
			{
				process_info.ppid = std::stoi(line.substr(5));
			}
			else if (line.starts_with("Name:"))
			{
				process_info.process_name = trim(line.substr(5));
			}
		}
		status_file.close();

		return {process_info, {}};
	}

	/**
	 * @brief 扫描系统进程，获取所有进程信息
	 * @return 所有进程信息的列表
	 */
	static std::vector<ProcessInfo> ScanProcess()
	{
		std::vector<ProcessInfo> processes;

		// 遍历 /proc/[pid]
		auto proc_path = fs::path("/proc/");
		if (!fs::exists(proc_path) || !fs::is_directory(proc_path))
		{
			std::cerr << "✖️ 无法打开 /proc/ 目录\n";
			return {};
		}

		for (const auto &entry : fs::directory_iterator(proc_path))
		{
			if (!fs::is_directory(entry.status()))
				continue;

			std::string pid = entry.path().filename().string();

			// 不是pid目录
			if (!std::all_of(pid.begin(), pid.end(), ::isdigit))
			{
				continue;
			}

			// Parse status
			auto status_file_path = entry.path() / "status";
			auto [process_info, parse_error] = ParseStatusFile(status_file_path);
			if (parse_error.has_value())
			{
				std::cerr << "✖️ Parse Failed, pid:" << pid << ", error: " << parse_error.value() << "\n";
				continue;
			}
			processes.push_back(process_info);
		}

		return std::move(processes);
	}
};

#endif // PROCESS_SCANNER_H