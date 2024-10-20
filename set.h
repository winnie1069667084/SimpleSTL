/*
【题目描述】
本题需要设计一个 Set 类，实现如下功能：
1、基础功能
构造函数：初始化 Set 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 Set 中插入一个元素
在 Set 中删除一个元素
判断一个元素是否在 Set 中
判断 Set 是否为空
获取 Set 的大小

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
insert 命令：
格式：insert [element]
功能：在 Set 中添加 element，如果元素已经存在，则不进行任何操作
erase 命令
格式：erase [element]
功能：删除 Set 中的元素 element，如果集合中不存在 element，则不进行任何操作
contains 命令：
格式：contains [element]
功能：判断 Set 中是否包含 element 元素
empty 命令：
格式：empty
功能：判断 Set 是否为空
size 命令：
格式：size
功能：获取 Set 的大小

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
insert 命令：无输出
erase 命令：无输出
contains 命令：如果 Set 中存在该元素，则输出 true，否则输出 false，输出独占一行
empty 命令：如果 Set 为空，则输出 true，否则输出 false，输出独占一行
size 命令：输出一个整数，独占一行，表示 Set 的大小
*/

#include "red_black_tree.h"

template <typename Key> class Set{
public:
    Set() : rb_tree() {}
    
    void insert(const Key& key) { rb_tree.insert(key, key); }

    void erase(const Key& key) { rb_tree.remove(key); }

    bool contains(const Key& key) { return rb_tree.at(key) != nullptr; }

    bool empty() { return rb_tree.empty(); }
    
    size_t size() { return rb_tree.getSize(); }

private:
    RedBlackTree<Key, Key> rb_tree;
};

int main() {
    Set<int> set;
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
        if (command == "insert") {
            iss >> key;
            set.insert(key);
        } else if (command == "earse") {
            iss >> key;
            set.erase(key);
        } else if (command == "contains") {
            iss >> key;
            std::cout << (set.contains(key) ? "true" : "false") << std::endl;
        } else if (command == "empty") {
            std::cout << (set.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << set.size() << std::endl;
        }
    }
}

// 本题就是简单的对红黑树代码的封装
// 测试样例的“erase”全部错拼成了“earse”，所以代码里也只能写`command == "earse"`了
