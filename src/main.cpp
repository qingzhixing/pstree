#include <iostream>
#include <getopt.h>
#include <string>
#include <arguments_handler.h>

int main(int argc, char *argv[])
{
    auto pstree_options = ArgumentsHandler::HandleArguments(argc, argv);
    if (pstree_options.show_help)
    {
        ArgumentsHandler::PrintHelp();
        return 0;
    }
    if (pstree_options.show_version)
    {
        ArgumentsHandler::PrintVersion();
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
    return 0;
}