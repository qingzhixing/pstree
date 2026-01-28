#include <iostream>
#include <getopt.h>
#include <string>
#include <arguments_handler.h>
#include <project_info.h>
#include <process_scanner.h>

int main(int argc, char *argv[])
{
    auto pstree_options = ArgumentsHandler::HandleArguments(argc, argv);
    if (pstree_options.show_help)
    {
        ProjectInfo::PrintHelp();
        return 0;
    }
    if (pstree_options.show_version)
    {
        ProjectInfo::PrintVersion();
        return 0;
    }
    if (pstree_options.show_pids)
    {
        std::cout << "Showing PIDs is enabled.\n";
    }
    if (pstree_options.numeric_sort)
    {
        std::cout << "Numeric sort is enabled.\n";
    }

    auto processes = ProcessScanner::ScanProcess();

    // 打印进程信息
    for (const auto &process : processes)
    {
        std::cout << std::format("PID: {}, PPID: {}, Name: {}\n",
                                 process.pid,
                                 process.ppid,
                                 process.process_name);
    }

    return 0;
}