# 打印进程树 (pstree)

## ❤️‍🔥 项目信息
本项目来自 jyy OS 2025 课程的 [M2 实验](https://jyywiki.cn/OS/2025/labs/M2.md)

![Cover](static/Cover.png)

## 🎵 描述
把系统中的进程按照父亲-孩子的树状结构打印到终端。  

* -p 或 --show-pids: 打印每个进程的进程号。

* -n 或 --numeric-sort: 按照 pid 的数值从小到大顺序输出一个进程的直接孩子。

* -v 或 --version: 打印版本信息。

## 🌈 运行效果图
![Version Screenshot](static/Version%20Screenshot.png)

![Usage Screenshot](static/Usage%20Screenshot.png)

## ▶️ 编译及运行
> 本项目使用 C++ 编写，使用 XMake 进行编译。

👾 普通运行:
``` bash
xmake f -p linux -a x86_64 -m debug
xmake run pstree
```

🔧 运行测试 (需要准备 `valgrind`，或者请自行修改脚本跳过 `valgrind` 检查的测试) :
``` bash
./run_test.py
```