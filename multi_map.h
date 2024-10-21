/*
【题目描述】
本题需要设计一个 multimap 类，实现如下功能
1、基础功能
构造函数：初始化 multimap 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 multimap 中插入一个元素
在 multimap 中删除指定的键值
在 multimap 中删除所有的值
判断 multimap 是否为空
获取 multimap 的大小
遍历打印 multimap 中的key 对应的 values
获取 multimap 中 key 对应的 values

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
insert 命令：
格式：insert [key] [value]
功能：在 map 中添加 key-value 键值对，如果对应的 key 已经存在，则不进行任何操作
remove 命令：
格式：remove [key] [value]
功能：在 map 中删除 key 对应的 value
remove_all 命令：
格式：remove_all [key]
功能：在 map 中删除 key 对应的所有 value
at 命令：
格式：at [key]
功能：在 map 中获取 key 对应的 value
empty 命令：
格式：empty
功能：判断 multimap 是否为空
size 命令：
格式：size
功能：获取 multimap 的大小

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
insert 命令：无输出
remove 命令：无输出
remove_all 命令：无输出
empty 命令：如果 multimap 为空，则输出 true，否则输出 false，输出独占一行
size 命令：输出一个整数，独占一行，表示 multimap 的大小
at 命令：在 map 中获取 key 对应的 value，如果有多个 value，则打印所有的 value，每个 value 后都拥有一个空格，如果不存在，则输出 not exist，输出独占一行
*/

#include <red_black_tree.h>
#include <list>

template <typename Key, typename Value> class MultiMap {
public:
    using ValueType = std::list<Value>;

    MultiMap() : rb_tree(), _size(0) {};

    void insert(const Key& key, const Value& value) {
        ValueType* existing_values = rb_tree.at(key);
        if (existing_values) {
            existing_values->push_back(value);
        } else {
            ValueType values;
            values.push_back(value);
            rb_tree.insert(key, values);
        }
        ++_size;
    }

    void remove(const Key& key) {
        ValueType* existing_values = rb_tree.at(key);
        if (existing_values) {
            _size -= existing_values->size();
            rb_tree.remove(key);
        }
    }

    void remove(const Key& key, const Value& value) {
        ValueType* existing_values = rb_tree.at(key);
        if (existing_values) {
            existing_values->remove(value);
            --_size;
            if (existing_values->empty()) {
                rb_tree.remove(key);
            }
        }
    }

    ValueType* at(const Key& key) { return rb_tree.at(key); }

    bool empty() { return _size == 0; }

    size_t size() { return _size; }

private:
    RedBlackTree<Key, ValueType> rb_tree;
    size_t _size;
};

int main() {
    MultiMap<int, int> m_map;
    int N;
    std::cin >> N;
    getchar();
    std::string line;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        int key, value;
        iss >> command;
        if (command == "insert") {
            iss >> key >> value;
            m_map.insert(key, value);
        } else if (command == "remove") {
            iss >> key >> value;
            m_map.remove(key, value);
        } else if (command == "remove_all") {
            iss >> key;
            m_map.remove(key);
        } else if (command == "empty") {
            std::cout << (m_map.empty() ? "true" : "false") << std::endl;
        } else if (command == "size") {
            std::cout << m_map.size() << std::endl;
        } else if (command == "at") {
            iss >> key;
            auto* val_list = m_map.at(key);
            if (val_list) {
                for (auto val : *val_list) std::cout << val << " ";
                std::cout << std::endl;
            } else {
                std::cout << "not exsit" << std::endl;
            }
        }
    }
}

// 本题是对红黑树的简单封装
// 测试样例的 "not exist" 错拼成了 "not exsit" 因此代码里只能这么写
