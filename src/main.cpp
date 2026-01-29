#include <iostream>
#include <getopt.h>
#include <string>
#include <arguments_handler.h>
#include <project_info.h>
#include <process_scanner.h>
#include <pstree_display.h>

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

    auto processes = ProcessScanner::ScanProcess();

    PstreeDisplay pstree_display(processes);
    pstree_display.DisplayTree(pstree_options);

    return 0;
}