#ifndef ARGUMENTS_HANDLER_H
#define ARGUMENTS_HANDLER_H

#include <iostream>
#include <string>
#include <getopt.h>

class ArgumentsHandler
{
public:
	static void PrintHelp()
	{
		std::cout << "✨ Usage: " << "pstree" << " [options]\n"
				  << "Options:\n"
				  << "  -p, --show-pids       打印每个进程的进程号.\n"
				  << "  -n, --numeric-sort    按照 pid 的数值从小到大顺序输出一个进程的直接孩子.\n"
				  << "  -v, --version         打印版本信息.\n"
				  << "  -h, --help            打印帮助信息.\n";
	}

	static void PrintVersion()
	{
		std::cout << "🌲 pstree: ";
		std::cout << "把系统中的进程按照父亲-孩子的树状结构打印到终端。 \n";
		std::cout << "❤️‍🔥 Author: qingzhixing <qzsqqmail@qq.com>\n";
	}

	struct PstreeOptions
	{
		bool show_pids = false;
		bool numeric_sort = false;
		bool show_version = false;
		bool show_help = false;
	};

	/**
	 * @brief 处理命令行参数
	 * @param argc 命令行参数数量
	 * @param argv 命令行参数数组
	 *
	 * -p 或 --show-pids: 打印每个进程的进程号。
	 * -n 或 --numeric-sort: 按照 pid 的数值从小到大顺序输出一个进程的直接孩子。
	 * -v 或 --version: 打印版本信息。
	 * -h 或 --help: 打印帮助信息。
	 */
	static PstreeOptions HandleArguments(int argc, char *argv[])
	{
		PstreeOptions pstree_options;

		int opt;
		// long options
		static struct option long_options[] = {
			{"show-pids", no_argument, nullptr, 'p'},
			{"numeric-sort", no_argument, nullptr, 'n'},
			{"version", no_argument, nullptr, 'v'},
			{"help", no_argument, nullptr, 'h'},
			{nullptr, 0, nullptr, 0}};
		const char *optstring = "pnhv";

		while ((opt = getopt_long(argc, argv, optstring, long_options, nullptr)) != -1)
		{
			switch (opt)
			{
			case 'p':
				pstree_options.show_pids = true;
				break;

			case 'n':
				pstree_options.numeric_sort = true;
				break;

			case 'v':
				pstree_options.show_version = true;
				break;

			case 'h':
				pstree_options.show_help = true;
				break;

			default:
				// Invalid options
				return {.show_help = true};
			}
		}
		return pstree_options;
	}
};

#endif // ARGUMENTS_HANDLER_H