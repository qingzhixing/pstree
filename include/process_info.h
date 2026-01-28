#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#include <string>

class ProcessInfo
{
public:
	int pid;
	int ppid;
	std::string process_name;
};

#endif // PROCESS_INFO_H