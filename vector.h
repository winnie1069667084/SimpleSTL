/*
【题目描述】
设计一个名为 MyVector 的 Vector 类，该类应具备以下功能和特性：
1、基础成员函数：
构造函数：初始化 Vector 实例
析构函数：清理资源，确保无内存泄露
拷贝构造函数：允许通过现有的 MyVector 实例来创建一个新实例
拷贝赋值操作符：实现 MyVector 实例之间的赋值功能
2、核心功能：
添加元素到末尾：允许在 Vector 的末尾添加新元素
获取元素个数：返回 Vector 当前包含的元素数量
获取容量：返回 Vector 可以容纳的元素总数
访问指定索引处的元素：通过索引访问特定位置的元素
在指定位置插入元素：在 Vector 的特定位置插入一个新元素
删除数组末尾元素：移除 Vector 末尾的元素
清空数组：删除 Vector 中的所有元素，重置其状态
3、迭代与遍历：
使用迭代器遍历：实现迭代器以支持对 Vector 从开始位置到结束位置的遍历
遍历并打印数组元素：提供一个函数，通过迭代器遍历并打印出所有元素
4、高级特性：
容器扩容：当前容量不足以容纳更多元素时，自动扩展 Vector 的容量以存储更多元素

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
push 命令：
格式：push [element]
功能：将 element 添加到 Vector 的末尾
size 命令：
格式：size
功能：返回 Vector 当前包含的元素数量
get 命令：
格式：get [index]
功能：返回 index 索引处的元素
insert 命令：
格式：insert [index] [element]
功能：在 Vector 的 index 索引处插入一个 element
pop 命令：
格式：pop
功能：移除 Vector 末尾的元素
clear 命令：
格式：clear
功能：删除 Vector 中的所有元素，重置其状态
print 命令：
格式：print
功能：提供一个函数，遍历并打印出所有元素
iterator 命令：
格式：iterator
功能：实现迭代器以支持对 Vector 从开始位置到结束位置的遍历
foreach 命令：
格式：foreach
功能：遍历并打印出所有元素

【输出描述】
题目包含 N 行输出，不同命令需要给出明确的反馈，输入格式如下：
push 命令：无输出
size 命令：输出一个整数，独占一行，代表当前 vector 中的元素数量
get 命令：输出一个整数，独占一行，如果索引有效，则输出指定索引处的元素，如果索引无效，则输出 -1
insert 命令：无输出
pop 命令：无输出
clear 命令：无输出
print 命令：按照顺序打印当前 vector 包含的所有元素，每个元素后都跟一个空格，打印结果独占一行；如果当前的 vector 为空，则打印 empty
iterator 命令：按照顺序打印当前 vector 包含的所有元素，每个元素后都跟一个空格，打印结果独占一行；如果当前的 vector 为空，则打印 empty
foreach 命令：按照顺序打印当前 vector 包含的所有元素，每个元素后都跟一个空格，打印结果独占一行；如果当前的 vector 为空，则打印 empty
*/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* elements; // 指向动态数组的指针
    size_t capacity; // 数组的容量
    size_t size; // 数组中的元素个数
    
public:
    // 1.基础成员函数
    // 构造函数
    Vector() : elements(nullptr), capacity(0), size(0) {}
    // 析构函数
    ~Vector() {
        delete[] elements;
    }
    //拷贝构造函数
    Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
        elements = new T[capacity];
        std::copy(other.elements, other.elements + size, elements);
    }
    // 拷贝赋值操作符
    Vector& operator=(const Vector& other) {
        if (this != &other) { // 检查自赋值，&other的用于取址比较
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
        return *this;
    }
    
    // 2.核心功能
    // 添加元素到末尾
    void push_back(const T& value) {
        if (size == capacity) reserve(capacity == 0 ? 1 : 2 * capacity);
        elements[size++] = value;
    }
    // 获取元素个数
    size_t get_size() const {
        return size;
    }
    // 获取容量
    size_t get_capacity() const {
        return capacity;
    }
    // 访问指定索引处的元素
    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return elements[index];
    }
    const T& operator[](size_t index) const{
        if (index >= size) throw std::out_of_range("Index out of range");
        return elements[index];
    }
    // 在指定位置插入元素 
    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (size == capacity) reserve(capacity == 0 ? 1 : 2 * capacity);
        for (size_t i = size; i > index; --i) {
            elements[i] = elements[i - 1];
        }
        elements[index] = value;
        ++size;
    }
    // 删除数组末尾元素
    void pop_back() {
        if (size > 0) --size;
    }
    // 清空数组
    void clear() {
        size = 0;
    }
    
    // 3.迭代与遍历
    T* begin() {
        return elements;
    }
    T* end() {
        return elements + size;
    }
    const T* begin() const{
        return elements;
    }
    const T* end() const{
        return elements + size;
    }
    void print_elements() const{
        for (size_t i = 0; i < size; ++i) std::cout << elements[i] << " ";
        std::cout << std::endl;
    }
    
    // 4.高级特性
    // 容器扩容
private:
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            T* new_elements = new T[new_capacity];
            std::copy(elements, elements + size, new_elements);
            delete[] elements;
            elements = new_elements;
            capacity = new_capacity;
        }
    }
};

int main() {
    Vector<int> my_vector;
    int N;
    std::cin >> N;
    getchar();
    std::string line;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        
        if (command == "push") {
            int value;
            iss >> value;
            my_vector.push_back(value);
        } else if (command == "print") {
            if (my_vector.get_size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            my_vector.print_elements();
        } else if (command == "size") {
            std::cout << my_vector.get_size() << std::endl;
        } else if (command == "get") {
            int index;
            iss >> index;
            std::cout << my_vector[index] << std::endl;
        } else if (command == "insert") {
            int index, value;
            iss >> index >> value;
            my_vector.insert(index, value);
        } else if (command == "pop") {
            my_vector.pop_back();
        } else if (command == "iterator") {
            if (my_vector.get_size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (auto it = my_vector.begin(); it != my_vector.end(); ++it) {
                std::cout << *it << std::endl;
            }
        } else if (command == "foreach") {
            if (my_vector.get_size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto &element : my_vector) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        } else if (command == "clear") {
            my_vector.clear();
        } 
    }
}

// Q&A

// Q:为何要用capacity size的类型要选用size_t而非int?
// A:size_t表示无符号整型，int是整形。size_t能表示更大的整形范围，并避免潜在的负值问题。

// Q:拷贝赋值操作符重载为什么参数和返回值类型要使用Vector&并最终return *this?
// A:1.返回值使用Vector&类型，以返回一个当前对象的引用（*this），可以支持链式赋值，如v1 = v2 = v3;
//   2.参数使用const Vector&可以避免修改传入对象和非必要的拷贝提升性能

// Q:在自定义STL时是否推荐使用using namespace std;?
// A:不推荐。使用 using namespace std; 会将标准库中的所有名称引入到当前作用域。这可能导致与用户自定义的名称发生冲突，特别是在大型项目或与其他库结合使用时。
