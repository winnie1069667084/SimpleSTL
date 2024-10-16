/*
【题目描述】
设计一个名为 List 的 List 类，该类具有以下功能和特性：
1、基础成员函数
构造函数：初始化 List 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 List 末尾添加元素
在 List 开头添加元素
获取 List 中节点的数量
删除 List 末尾的元素
删除 List 开头的元素
删除 List 中指定值的节点
3、迭代与遍历
打印链表中的元素
4、辅助功能
重载[]运算符以对链表进行索引访问
重载<<运算符以打印链表

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
push_back 命令：
格式：push_back [value]
功能：在链表末尾添加值为 value 的元素
push_front 命令：
格式：push_front [value]
功能：在链表开头添加值为 value 的元素
pop_back 命令：
格式：pop_back
功能：删除链表末尾的元素
pop_front 命令：
格式：pop_front
功能：删除链表开头的元素
remove 命令：
格式：remove [value]
功能：删除链表中值为 value 的元素
clear 命令：
格式：clear
功能：清空链表
size 命令：
格式：size
功能：获取链表中节点的数量
get 命令：
格式：get [index]
功能：获取链表中索引为 index 的节点的值
print 命令：
格式：print
功能：打印链表中的元素

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
push_back 命令：无输出
push_front 命令：无输出
pop_back 命令：无输出
pop_front 命令：无输出
remove 命令：无输出
clear 命令：无输出
size 命令：输出一个整数，独占一行，代表当前 List 中元素的数量
get 命令：输出一个整数，独占一行，代表 List 中索引为 index 的元素，如果索引无效，则输出 -1
print 命令：按照顺序打印当前 List 包含的所有元素，每个元素后都跟一个空格，打印结果独占一行；如果当前的 vector 为空，则打印 empty
*/

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class List {
public:
    template <typename L>
    friend std::ostream& operator<<(std::ostream& os, const List<L>& list);
    
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value, Node* next_node = nullptr, Node* prev_node = nullptr)
            : data(value), next(next_node), prev(prev_node) {}
    };
    Node* head;
    Node* tail;
    size_t size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    
    ~List() { clear(); }
    
    void clear() {
        while(head) {
            Node* cur = head;
            head = head->next;
            delete cur;
        }
        tail = nullptr;
        size = 0;
    }
    
    void push_back(const T& val) {
        Node* new_node = new Node(val, nullptr, tail);
        if (tail) tail->next = new_node;
        else head = new_node;
        tail = new_node;
        ++size;
    }
    
    void push_front(const T& val) {
        Node* new_node = new Node(val, head, nullptr);
        if (head) head->prev = new_node;
        else tail = new_node;
        head = new_node;
        ++size;
    }
    
    size_t get_size() { return size; }
    
    void pop_back() {
        if (size == 0) return;
        Node* new_tail = tail->prev;
        delete tail;
        tail = new_tail;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        --size;
    }
    
    void pop_front() {
        if (size == 0) return;
        Node* new_head = head->next;
        delete head;
        head = new_head;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        --size;
    }
    
    void remove(const T& value) {
        Node* node = head;
        while (node && node->data != value) node = node->next;
        if (node == nullptr) {
            return;
        } else if (node != head && node != tail) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        } else if (node == head && node == tail) {
            head = nullptr;
            tail = nullptr;
        } else if (node == head) {
            head = node->next;
            head->prev = nullptr;
        } else if (node == tail) {
            tail = node->prev;
            tail->next = nullptr;
        }
        delete node;
        --size;
    }
    
    void print_elements() const{
        for (Node* node = head; node; node = node->next) {
            std::cout << node->data << " ";
        }
        std::cout << std::endl;
    }
    
    T& operator[](size_t index) {
        Node* cur = head;
        while (index--) {
            if (cur == nullptr) throw std::out_of_range("Index out of range");
            cur = cur->next;
        }
        return cur->data;
    }
    
    const T& operator[](size_t index) const{
        Node* cur = head;
        while (index--) {
            if (cur != nullptr) throw std::out_of_range("Index out of range");
            cur = cur->next;
        }
        return cur->data;
    }
};

template <typename L>
std::ostream& operator<<(std::ostream& os, const List<L>& list) {
    for (typename List<L>::Node* cur = list.head; cur; cur = cur->next) {
        os << cur->data << " ";
    }
    os << std::endl;
    return os;
}

int main() {
    List<int> my_list;
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
            my_list.push_back(val);
        } else if (command == "push_front") {
            iss >> val;
            my_list.push_front(val);
        } else if (command == "pop_back") {
            my_list.pop_back();
        } else if (command == "pop_front") {
            my_list.pop_front();
        } else if (command == "remove") {
            iss >> val;
            my_list.remove(val);
        } else if (command == "clear") {
            my_list.clear();
        } else if (command == "size") {
            std::cout << my_list.get_size() << std::endl;
        } else if (command == "get") {
            iss >> val;
            if ((size_t)val >= my_list.get_size()) {
                std::cout << -1 << std::endl;
                continue;
            }
            std::cout << my_list[val] << std::endl;
        } else if (command == "print") {
            if (my_list.get_size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            my_list.print_elements();
        }
    }
}
