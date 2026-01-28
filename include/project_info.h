#ifndef PROJECT_INFO_H
#define PROJECT_INFO_H

#include <string>
#include <iostream>
#include <format>

class ProjectInfo
{
public:
	static inline const std::string project_name = "pstree";
	static inline const std::string description = "把系统中的进程按照父亲-孩子的树状结构打印到终端。";
	static inline const std::string ascii_art =
		R"(
██████╗ ███████╗████████╗██████╗ ███████╗███████╗
██╔══██╗██╔════╝╚══██╔══╝██╔══██╗██╔════╝██╔════╝
██████╔╝███████╗   ██║   ██████╔╝█████╗  █████╗  
██╔═══╝ ╚════██║   ██║   ██╔══██╗██╔══╝  ██╔══╝  
██║     ███████║   ██║   ██║  ██║███████╗███████╗
╚═╝     ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝                                               
)";
	static inline const std::string author = "qingzhixing";
	static inline const std::string mail = "qzsqqmail@qq.com";
	static inline const std::string license = "MIT License";
	static inline const std::string github_link = "https://github.com/qingzhixing/pstree";

public:
	static void PrintHelp()
	{
		std::cout << std::format("✨ Usage: {} [options]\n", project_name)
				  << "Options:\n"
				  << "  -p, --show-pids       打印每个进程的进程号.\n"
				  << "  -n, --numeric-sort    按照 pid 的数值从小到大顺序输出一个进程的直接孩子.\n"
				  << "  -v, --version         打印版本信息.\n"
				  << "  -h, --help            打印帮助信息.\n";
	}

	static void PrintVersion()
	{
		std::cout << ascii_art << "\n";
		std::cout << std::format("🌲 {}: \n", project_name);
		std::cout << std::format("📸 Description: {}\n", description);
		std::cout << std::format("❤️‍🔥 Author: @{} \n", author);
		std::cout << std::format("📧 Mail: {}\n", mail);
		std::cout << std::format("📜 License: {}\n", license);
		std::cout << std::format("🔗 GitHub Link: {}\n", github_link);
	}
};

#endif // PROJECT_INFO_H