/*
【题目描述】
设计一个名为 Deque 的 Deque 类，该类具有以下功能和特性：
1、基础成员函数
构造函数：初始化 Deque 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 Deque 末尾添加元素
在 Deque 开头添加元素
删除 Deque 末尾的元素
删除 Deque 开头的元素
获取 Deque 中节点的数量
删除 Deque 中所有的元素
3、迭代与遍历
打印 Deque 中的元素
4、辅助功能
重载[]运算符以对 Deque 进行索引访问

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
push_back 命令：
格式：push_back [value]
功能：在双端队列末尾添加值为 value 的元素
push_front 命令：
格式：push_front [value]
功能：在双端队列开头添加值为 value 的元素
pop_back 命令：
格式：pop_back
功能：删除双端队列末尾的元素
pop_front 命令：
格式：pop_front
功能：删除双端队列开头的元素
clear 命令：
格式：clear
功能：清空双端队列
size 命令：
格式：size
功能：获取双端队列中节点的数量
get 命令：
格式：get [index]
功能：获取双端队列中索引为 index 的节点的值
print 命令：
格式：print
功能：打印双端队列中的元素

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
push_back 命令：无输出
push_front 命令：无输出
pop_back 命令：无输出
pop_front 命令：无输出
clear 命令：无输出
size 命令：输出一个整数，独占一行，代表 Deque 中元素的数量
get 命令：输出双端队列中索引为 index 的节点的值
print 命令：输出双端队列中的元素
*/

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Deque {
private:
    T* elements;
    size_t capacity;
    size_t size;
    size_t front_index;
    size_t back_index;

public:
    Deque() : elements(nullptr), capacity(0), size(0), front_index(0), back_index(0) {}
    
    ~Deque() {
        clear();
        delete[] elements;
    }
    
    void clear() {
        front_index = back_index = 0;
        size = 0;
    }
    
    void push_back(const T& val) {
        if (size == capacity) resize();
        elements[back_index] = val; // 注意这行与push_front()相反，因为back_index指向的是未赋值的数组元素
        back_index = (back_index + 1) % capacity;
        ++size;
    }
    
    void push_front(const T& val) {
        if (size == capacity) resize();
        front_index = (front_index - 1 + capacity) % capacity;
        elements[front_index] = val;
        ++size;
    }
    
    void pop_back() {
        if (size == 0) throw std::out_of_range("Deque is empty");
        back_index = (back_index - 1 + capacity) % capacity;
        --size;
    }
    
    void pop_front() {
        if (size == 0) throw std::out_of_range("Deque is empty");
        front_index = (front_index + 1) % capacity;
        --size;
    }
    
    size_t get_size() const {
        return size;
    }
    
    void print_elements() const {
        size_t index = front_index;
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
    }
    
    T& operator[](size_t index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return elements[(front_index + index) % capacity];
    }
    
    const T& operator[](size_t index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return elements[(front_index + index) % capacity];
    }
    
private:
    void resize() {
        size_t new_capacity = capacity == 0 ? 1 : 2 * capacity;
        T* new_elements = new T[new_capacity];
        size_t index = front_index;
        for (size_t i = 0; i < size; ++i) {
            new_elements[i] = elements[index];
            index = (index + 1) % capacity;
        }
        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
        front_index = 0;
        back_index = size;
    }
};

int main() {
    Deque<int> my_deque;
    int N;
    std::cin >> N;
    getchar();
    std::string line;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int val;
        if (command == "push_back") {
            iss >> val;
            my_deque.push_back(val);
        } else if (command == "push_front") {
            iss >> val;
            my_deque.push_front(val);
        } else if (command == "pop_back") {
            if (my_deque.get_size() == 0) continue;
            my_deque.pop_back();
        } else if (command == "pop_front") {
            if (my_deque.get_size() == 0) continue;
            my_deque.pop_front();
        } else if (command == "clear") {
            my_deque.clear();
        } else if (command == "size") {
            std::cout << my_deque.get_size() << std::endl;
        } else if (command == "get") {
            iss >> val;
            std::cout << my_deque[val] << std::endl;
        } else if (command == "print") {
            if (my_deque.get_size() == 0) std::cout << "empty" << std::endl;
            else my_deque.print_elements();
        }
    }
}

// Q&A
// Q:双端队列循环数组实现的push_front()为什么要加上一个capacity再取余，直接取余不行吗
// A:在 C++ 中负数取余的结果是可能返回负值，这会导致数组访问越界，从而引发未定义行为。
