#ifndef PSTREE_DISPLAY_H
#define PSTREE_DISPLAY_H

#include <vector>
#include <process_scanner.h>
#include <string>
#include <arguments_handler.h>
#include <map>
#include <iostream>
#include <format>
#include <testkit.h>

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
		// 第一个进程的 pid 一定是 1
		PreorderTraversal(1, pstree_options);
	}

private:
	void PreorderTraversal(int pid, const PstreeOptions &pstree_options)
	{
		// 记录当前节点的深度，以便打印出树的形状

		// 用于管理打印时的连接线
		static std::vector<bool> is_connector_required = {};

		// 连接线前缀
		if (!is_connector_required.empty())
		{
			for (int i = 0; i < is_connector_required.size() - 1; i++)
			{
				if (is_connector_required[i])
				{
					std::cout << " |  ";
				}
				else
				{
					std::cout << "    ";
				}
			}
			std::cout << " +--";
		}

		// 打印当前节点的信息
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
		for (int i = 0; i < node_children[pid].size(); i++)
		{
			int child_pid = node_children[pid][i];

			// 打印单独一行的连接线
			if (!is_connector_required.empty())
			{
				for (int i = 0; i < is_connector_required.size(); i++)
				{
					if (is_connector_required[i])
					{
						std::cout << " |  ";
					}
					else
					{
						std::cout << "    ";
					}
				}
			}
			std::cout << " |" << std::endl;

			bool is_last_child = (i == node_children[pid].size() - 1);

			is_connector_required.push_back(!is_last_child);
			PreorderTraversal(child_pid, pstree_options);
			is_connector_required.pop_back();
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