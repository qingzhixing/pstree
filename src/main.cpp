#include <iostream>
#include <getopt.h>
#include <string>
#include <arguments_handler.h>
#include <project_info.h>

#include <fstream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

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

    // 遍历 /proc/[pid]
    auto proc_path = fs::path("/proc/");
    if (!fs::exists(proc_path) || !fs::is_directory(proc_path))
    {
        std::cerr << "✖️ 无法打开 /proc/ 目录\n";
        return 1;
    }

    for (const auto &entry : fs::directory_iterator(proc_path))
    {
        if (fs::is_directory(entry.status()))
        {
            std::string pid = entry.path().filename().string();
            if (std::all_of(pid.begin(), pid.end(), ::isdigit))
            {
                std::cout << "Find PID: " << pid << std::endl;
            }
        }
    }

    return 0;
}