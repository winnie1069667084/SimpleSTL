/*
【题目描述】
本题需要设计一个 priority_queue 类，实现如下功能：
1、基础功能
构造函数：初始化 priority_queue 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
将元素添加到 priority_queue 中
弹出 priority_queue 中的最大元素
获取 priority_queue 中的最大元素
获取 priority_queue 中元素的个数
判断 priority_queue 是否为空

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
push 命令：
格式：push [element]
功能：将 element 添加到 priority_queue 中
pop 命令：
格式：pop
功能：弹出 priority_queue 中的最大元素
top 命令：
格式：top
功能：访问 priority_queue 中的最大元素
empty 命令：
格式：empty
功能：检查 priority_queue 是否为空
size 命令：
格式：size
功能：返回 priority_queue 的大小

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
push 命令：无输出
pop 命令：无输出
top 命令：输出一个整数，独占一行，代表 priority_queue 中最大的元素，如果 priority_queue 为空，则输出 null
empty 命令：为空输出 true，不为空输出 false，输出独占一行
size 命令：输出一个整数，独占一行，代表 priority_queue 的大小
*/

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T, typename Container = std::vector<T>> class PriorityQueue {
private:
    Container data;

    void heapifyUp() {
        int index = data.size() - 1;
        while (index > 0) {
            int parent_index = (index - 1) / 2;
            if (data[index] > data[parent_index]) {
                std::swap(data[index], data[parent_index]);
                index = parent_index;
            } else {
                break;
            }
        }
    }

    void heapifyDown() {
        int index = 0;
        int size = data.size();
        while (true) {
            int left_child = 2 * index + 1;
            int right_child = 2 * index + 2;
            int largest = index;
            if (left_child < size && data[left_child] > data[largest]) largest = left_child;
            if (right_child < size && data[right_child] > data[largest]) largest = right_child;
            if (largest != index) {
                std::swap(data[index], data[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    PriorityQueue() {}

    void push(const T& value) {
        data.push_back(value);
        heapifyUp();
    }

    void pop() {
        if (!empty()) {
            std::swap(data[0], data[data.size() - 1]);
            data.pop_back();
            heapifyDown();
        } else {
            throw std::runtime_error("Priority queue is empty.");
        }
    }

    T& top() {
        if (!empty()) return data[0];
        else throw std::runtime_error("Priority queue is empty.");
    }

    bool empty() const { return data.size() == 0; }

    size_t size() const { return data.size(); }
};

int main() {
    PriorityQueue<int> priority_queue;
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
            priority_queue.push(key);
        } else if (command == "pop") {
            try {
                priority_queue.pop();
            } catch(const std::runtime_error& e) {
                continue;
            }
        } else if (command == "top") {
            try {
                std::cout << priority_queue.top() << std::endl;
            } catch(const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        } else if (command == "empty") {
            std::cout << (priority_queue.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << priority_queue.size() << std::endl;
        }
    }
}

// C++ STL中直接使用std::make_heap, std::push_heap, std::pop_heap来实现priority_queue
// 本题中先自己实现堆，再实现优先级队列
// 此代码只实现了大顶堆priority_queue，无法接受比较函数变为其他类型
// 此代码只有默认构造函数，无法将一个序列初始化为堆
