#include <testkit.h>
#include <arguments_handler.h>
#include <iostream>
#include <string.h>

UnitTest(Test_HelpOption)
{
	// Test help option
	char *argv[] = {strdup("pstree"), strdup("-h")};
	auto options = ArgumentsHandler::HandleArguments(2, argv);

	assert(options.show_help == true);
	assert(options.show_version == false);
	assert(options.show_pids == false);
	assert(options.numeric_sort == false);
}

UnitTest(Test_VersionOption)
{
	// Test version option
	char *argv[] = {strdup("pstree"), strdup("-v")};
	auto options = ArgumentsHandler::HandleArguments(2, argv);

	assert(options.show_help == false);
	assert(options.show_version == true);
	assert(options.show_pids == false);
	assert(options.numeric_sort == false);
}

UnitTest(Test_ShowPidsOption)
{
	// Test show-pids option
	char *argv[] = {strdup("pstree"), strdup("-p")};
	auto options = ArgumentsHandler::HandleArguments(2, argv);

	assert(options.show_help == false);
	assert(options.show_version == false);
	assert(options.show_pids == true);
	assert(options.numeric_sort == false);
}

UnitTest(Test_NumericSortOption)
{
	// Test numeric-sort option
	char *argv[] = {strdup("pstree"), strdup("-n")};
	auto options = ArgumentsHandler::HandleArguments(2, argv);

	assert(options.show_help == false);
	assert(options.show_version == false);
	assert(options.show_pids == false);
	assert(options.numeric_sort == true);
}

UnitTest(Test_MultipleOptions)
{
	// Test multiple options
	char *argv[] = {strdup("pstree"), strdup("-p"), strdup("-n")};
	auto options = ArgumentsHandler::HandleArguments(3, argv);

	assert(options.show_help == false);
	assert(options.show_version == false);
	assert(options.show_pids == true);
	assert(options.numeric_sort == true);
}

UnitTest(Test_InvalidOption)
{
	// Test invalid option
	char *argv[] = {strdup("pstree"), strdup("-x")};
	auto options = ArgumentsHandler::HandleArguments(2, argv);

	assert(options.show_help == true); // Should show help on invalid option
	assert(options.show_version == false);
	assert(options.show_pids == false);
	assert(options.numeric_sort == false);
}