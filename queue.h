/*
【题目描述】
本题需要设计一个 queue 类，实现如下功能：
1、基础功能
构造函数：初始化 queue 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
将元素添加到 queue 队尾
移除 queue 队头元素
访问 queue 队头元素
访问 queue 队尾元素
获取 queue 大小
判断 queue 是否为空

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
push 命令：
格式：push [element]
功能：将 element 添加到队尾
pop 命令：
格式：pop
功能：移除队头元素
front 命令：
格式：front
功能：获取队头元素，为空则输出 null
back 命令：
格式：back
功能：获取队尾元素，为空则输出 null
empty 命令：
格式：empty
功能：检查队列是否为空
size 命令：
格式：size
功能：返回队列的大小

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
push 命令：无输出
pop 命令：无输出
front 命令：输出一个整数，独占一行，表示队头元素
back 命令：输出一个整数，独占一行，表示队尾元素
empty 命令：为空输出 true，不为空输出 false，输出独占一行
size 命令：输出一个整数，独占一行，表示队列的大小
*/

#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T, typename Container = std::deque<T>> class Queue{
private:
    Container data;

public:
    void push(const T& value) { data.push_back(value); }

    void pop() {
        if (!data.empty()) data.pop_front();
        else throw std::runtime_error("Queue is empty.");
    }

    T& front() {
        if (!data.empty()) return data.front();
        else throw std::runtime_error("Queue is empty.");
    }

    T& back() {
        if (!data.empty()) return data.back();
        else throw std::runtime_error("Queue is empty.");
    }

    bool empty() const { return data.empty(); }

    size_t size() const { return data.size(); }
};

int main() {
    Queue<int> queue;
    int N;
    std::cin >> N;
    getchar();
    std::string line;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        int key;
        iss >> command;
        if (command == "push") {
            iss >> key;
            queue.push(key);
        } else if (command == "pop") {
            try {
                queue.pop();
            } catch(const std::runtime_error& e) {
                continue;
            }
        } else if (command == "front") {
            try {
                std::cout << queue.front() << std::endl;
            } catch(const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        } else if (command == "back") {
            try {
                std::cout << queue.back() << std::endl;
            } catch(const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        } else if (command == "empty") {
            std::cout << (queue.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << queue.size() << std::endl;
        }
    }
}

// 本题是对容器（deque, vector, list）的简单封装
