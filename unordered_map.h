/*
【题目描述】
本题需要设计一个 unordered_map 类，实现如下功能
1、基础功能
构造函数：初始化 unordered_map 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 unordered_map 中插入一个元素
在 unordered_map 中删除元素
判断一个元素是否在 unordered_map 中
判断 unordered_map 是否为空
获取 unordered_map 的大小

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
insert 命令：
格式：insert [key] [value]
功能：在 map 中添加 key-value 键值对，如果对应的 key 已经存在，则不进行任何操作
erase 命令：
格式：erase [key]
功能：删除 unordered_map 中 key 对应的键值对，如果 key 不存在，则不进行任何操作
find 命令：
格式：find [key]
功能：查询 unordered_map 是否存在 key 对应的键值对
empty 命令：
格式：empty
功能：判断 unordered_map 是否为空
size 命令：
格式：size
功能：获取 unordered_map 的大小

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
insert 命令：无输出
erase 命令：无输出
empty 命令：如果 unordered_map 为空，则输出 true，否则输出 false，输出独占一行
size 命令：输出一个整数，独占一行，代表 unordered_map 的大小
find 命令：如果 key 存在，则输出 true，否则输出 false，输出独占一行
*/

#include "hash_table.h"

template <typename Key, typename Value> class UnorderedMap {
private:
    HashTable<Key, Value> hash_table;

public:
    UnorderedMap() : hash_table() {}

    void insert(const Key& key, const Value& value) { hash_table.insert(key, value); }

    void erase(const Key& key) { hash_table.erase(key); }

    bool find(const Key& key) { return hash_table.find(key) != nullptr; }

    bool empty() const noexcept { return hash_table.size() == 0; }

    size_t size() const noexcept { return hash_table.size(); }

    void clear() noexcept { hash_table.clear(); }

    Value& operator[](const Key& key) {
        Value* val = hash_table.find(key);
        if (val != nullptr) return *val;
        hash_table.insert_key(key);
        val = hash_table.find(key);
        return *val;
    }
};

int main() {
    UnorderedMap<int, int> u_map;
    int N;
    std::cin >> N;
    getchar();
    std::string line;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        int key, value;
        std::string command;
        iss >> command;
        if (command == "insert") {
            iss >> key >> value;
            u_map.insert(key, value);
        } else if (command == "erase") {
            iss >> key;
            u_map.erase(key);
        } else if (command == "empty") {
            std::cout << (u_map.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << u_map.size() << std::endl;
        } else if (command == "find") {
            iss >> key;
            std::cout << (u_map.find(key) ? "true" : "false") << std::endl;
        }
    }
}

// 本题是对哈希表的简单封装
