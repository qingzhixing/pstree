#ifndef PSTREE_DISPLAY_H
#define PSTREE_DISPLAY_H

#include <vector>
#include <process_scanner.h>
#include <string>
#include <arguments_handler.h>
#include <map>
#include <iostream>
#include <format>

struct TreeNodeInfo
{
	int pid;
	std::string process_name;
};

class PstreeDisplay
{
public:
	PstreeDisplay(const std::vector<ProcessInfo> &processes)
	{
		BuildTree(processes);
	}

	void DisplayTree(const PstreeOptions &pstree_options)
	{
		// 前序遍历
		PreorderTraversal(1, pstree_options);
	}

private:
	void PreorderTraversal(int pid, const PstreeOptions &pstree_options)
	{
		// 记录当前节点的深度，以便打印出树的形状
		static int depth = 0;

		// 打印当前节点的信息
		std::cout << std::string(depth * 2, ' ');
		std::cout << tree_nodes[pid].process_name;
		if (pstree_options.show_pids)
		{
			std::cout << std::format(" (pid: {})", tree_nodes[pid].pid);
		}
		std::cout << std::endl;

		if (pstree_options.numeric_sort)
		{
			std::sort(node_children[pid].begin(), node_children[pid].end());
		}

		// 递归遍历子节点
		for (int child_pid : node_children[pid])
		{
			depth++;
			PreorderTraversal(child_pid, pstree_options);
			depth--;
		}
	}

	void BuildTree(const std::vector<ProcessInfo> &processes)
	{
		for (const auto &process : processes)
		{
			tree_nodes[process.pid] = {process.pid, process.process_name};
			node_children[process.ppid].push_back(process.pid);
		}
	}

private:
	std::map<int, TreeNodeInfo> tree_nodes;
	std::map<int, std::vector<int>> node_children;
};

#endif // PSTREE_DISPLAY_H