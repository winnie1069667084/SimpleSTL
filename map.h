/*
【题目描述】
本题需要设计一个 map 类，实现如下功能：
1、基础功能
构造函数：初始化 map 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 map 中插入一个元素
在 map 中删除元素
判断一个元素是否在 map 中
判断 map 是否为空
获取 map 的大小
获取 map 中 key 对应的 value

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
insert 命令：
格式：insert [key] [value]
功能：在 map 中添加 key-value 键值对，如果对应的 key 已经存在，则不进行任何操作
erase 命令：
格式：erase [key]
功能：删除 map 中 key 对应的键值对，如果 key 不存在，则不进行任何操作
contains 命令：
格式：contains [key]
功能：查询 map 中 element 的数量
empty 命令：
格式：empty
功能：判断 map 是否为空
size 命令：
格式：size
功能：获取 map 的大小
at 命令：
格式：at [key]
功能：查询 map 中 key 对应的 value


【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
insert 命令：无输出
erase 命令：无输出
empty 命令：如果 map 为空，则输出 true，否则输出 false，输出独占一行
size 命令：输出一个整数，独占一行，表示 map 的大小
at 命令：如果 key 存在，则输出 key 对应的 value，不存在则输出 not exist，输出独占一行
contains 命令：如果 key 存在，则输出 true，否则输出 false，输出独占一行
*/

#include "red_black_tree.h"

template <typename Key, typename Value> class Map {
private:
    RedBlackTree<Key, Value> rb_tree;

public:
    Map() : rb_tree() {}

    void insert(const Key& key, const Value& value) { rb_tree.insert(key, value); }

    void erase(const Key& key) { rb_tree.remove(key); }

    bool contains(const Key& key) { return rb_tree.at(key) != nullptr; }

    bool empty() { return rb_tree.empty(); }

    size_t size() { return rb_tree.getSize(); }

    Value& at(const Key& key) {
        Value* val = rb_tree.at(key);
        if (val) {
            return *val;
        } else {
            throw std::out_of_range("Key not found");
        }
    }

    Value& operator[](const Key& key) {
        Value* val = rb_tree.at(key);
        if (val) {
            return *val;
        } else {
            rb_tree.insert(key, Value());
            return *rb_tree.at(key);
        }
    }
};

int main() {
    Map<int, int> map;
    int N;
    std::cin >> N;
    std::string line;
    getchar();
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        int key, value;
        iss >> command;
        if (command == "insert") {
            iss >> key >> value;
            map.insert(key, value);
        } else if (command == "erase") {
            iss >> key;
            map.erase(key);
        } else if (command == "empty") {
            std::cout << (map.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << map.size() << std::endl;
        } else if (command == "at") {
            iss >> key;
            try {
                std::cout << map.at(key) << std::endl;
            } catch (const std::out_of_range& e) {
                std::cout << "not exist" << std::endl;
            }
        } else if (command == "contains") {
            iss >> key;
            std::cout << (map.contains(key) ? "true" : "false") << std::endl;
        }
    }
}

// 本题是对红黑树的简单封装
