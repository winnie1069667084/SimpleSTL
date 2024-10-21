/*
【题目描述】
本题需要设计一个 multiset 类，实现如下功能：
1、基础功能
构造函数：初始化 multiset 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 multiset 中插入一个元素
在 multiset 中删除元素
判断一个元素是否在 multiset 中
判断 multiset 是否为空
获取 multiset 的大小

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
insert 命令：
格式：insert [element]
功能：在 multiset 中添加 element，如果元素已经存在，则不进行任何操作
erase 命令：
格式：erase [element]
功能：删除 multiset 中的所有 element ，如果 element 不存在，则不进行任何操作
count 命令：
格式：count [element]
功能：查询 multiset 中 element 的数量
empty 命令：
格式：empty
功能：判断 multiset 是否为空
size 命令：
格式：size
功能：获取 multiset 的大小

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
insert 命令：无输出
erase 命令：无输出
count 命令：输出一个整数，独占一行，代表 multiset 中该元素的数量
empty 命令：如果 multiset 为空，则输出 true，否则输出 false
size 命令：输出一个整数，独占一行，表示 multiset 中所有元素的数量
*/

#include <red_black_tree.h>

template <typename Key> class MultiSet {
private:
    RedBlackTree<Key, size_t> _rb_tree;
    size_t _size;

public:
    MultiSet() : _size(0) {}

    void insert(const Key& key) {
        auto count = _rb_tree.at(key);
        if (count != nullptr) {
            ++*count;
            ++_size;
            return;
        }
        _rb_tree.insert(key, 1);
        ++_size;
    }

    void erase(const Key& key) {
        auto count = _rb_tree.at(key);
        if (count == nullptr) return;
        _size -= *count;
        _rb_tree.remove(key);
    }

    size_t count(const Key& key) {
        auto num = _rb_tree.at(key);
        if (num != nullptr) return *num;
        return 0;
    }

    bool empty() const { return _size == 0; }

    size_t size() const { return _size; }

    void clear() {
        _size = 0;
        _rb_tree.clear();
    }
};

int main() {
    MultiSet<int> m_set;
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
            m_set.insert(key);
        } else if (command == "erase") {
            iss >> key;
            m_set.erase(key);
        } else if (command == "count") {
            iss >> key;
            std::cout << m_set.count(key) << std::endl;
        } else if (command == "empty") {
            std::cout << (m_set.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << m_set.size() << std::endl;
        }
    }
}

// 本题是对红黑树的简单封装
