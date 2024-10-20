/*
【题目描述】
本题需要设计一个 unordered_set 类，实现如下功能：
1、基础功能
构造函数：初始化 unordered_set 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 unordered_set 中插入一个元素
在 unordered_set 中删除一个元素
判断一个元素是否在 unordered_set 中
判断 unordered_set 是否为空
获取 unordered_set 的大小

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
insert 命令：
格式：insert [element]
功能：在 unordered_set 中添加元素，如果元素已经存在，则不进行任何操作
erase 命令：
格式：erase [element]
功能：删除 unordered_set 中的元素，如果元素不存在，则不进行任何操作
find 命令：
格式：find [element]
功能：查询 unordered_set 中的元素
empty 命令：
格式：empty
功能：判断无序集合是否为空
size 命令：
格式：size
功能：获取无序集合的大小

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
insert 命令：无输出
erase 命令：无输出
find 命令：如果元素存在，则输出 true，否则输出 false
empty 命令：如果 unordered_set 为空，则输出 true，否则输出 false
size 命令：输出 unordered_set 的大小

*/

#include <hash_table.h>

template <typename Key> class UnorderedSet {
public:
    UnorderedSet() : hash_table() {}

    void insert(const Key& key) { hash_table.insert_key(key); }

    void erase(const Key& key) { hash_table.erase(key); }

    bool find(const Key& key) { return hash_table.find(key) != nullptr; }

    bool empty() const noexcept { return hash_table.size() == 0; }

    size_t size() const noexcept { return hash_table.size(); }

    void clear() noexcept { hash_table.clear(); }

private:
    HashTable<Key, Key> hash_table;
};

int main() {
    UnorderedSet<int> u_set;
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
        if (command == "insert") {
            iss >> key;
            u_set.insert(key);
        } else if (command == "erase") {
            iss >> key;
            u_set.erase(key);
        } else if (command == "find") {
            iss >> key;
            std::cout << (u_set.find(key) ? "true" : "false") << std::endl;
        } else if (command == "empty") {
            std::cout << (u_set.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << u_set.size() << std::endl;
        }
    } 
}

// 对哈希表的简单封装
