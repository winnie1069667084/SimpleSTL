/*
【题目描述】
本题需要设计一个 stack 类，实现如下功能：
1、基础功能
构造函数：初始化 stack 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
压入元素到栈顶
弹出栈顶元素
获取栈顶元素
检查栈是否为空
返回栈的大小

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
push 命令：
格式：push [element]
功能：将 element 压到栈顶
pop 命令：
格式：pop
功能：弹出栈顶元素
top 命令：
格式：top
功能：获取栈顶元素，为空则输出 null
empty 命令：
格式：empty
功能：检查栈是否为空
size 命令：
格式：size
功能：返回栈的大小

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
push 命令：无输出
pop 命令：无输出
top 命令：输出一个整数，独占一行，表示栈顶元素
empty 命令：为空输出 true，不为空输出 false，输出独占一行
size 命令：输出一个整数，独占一行，表示栈内的元素数量
*/

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T, typename Container = std::deque<T>> class Stack {
private:
    Container data; // 使用底层容器存储栈的元素

public:
    void push(const T& value) { data.push_back(value); }

    void pop() {
        if (!data.empty()) data.pop_back();
        else throw std::runtime_error("Stack is empty.");
    }

    T& top() {
        if (!data.empty()) return data.back();
        else throw std::runtime_error("Stack is empty.");
    }

    bool empty() { return data.empty(); }

    size_t size() const { return data.size(); }
};

int main() {
    Stack<int> stack;
    int N;
    std::cin >> N;
    getchar();
    std::string line;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int key;
        if (command == "push") {
            iss >> key;
            stack.push(key);
        } else if (command == "pop") {
            try {
                stack.pop();
            } catch(const std::runtime_error& e) {
                continue;
            }
        } else if (command == "top") {
            try {
                std::cout << stack.top() << std::endl;
            } catch(const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        } else if (command == "empty") {
            std::cout << (stack.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << stack.size() << std::endl;
        }
    }
}

// 本题是对容器（vector, list, deque）的简单封装
