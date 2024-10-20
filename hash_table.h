/*
【题目描述】
在STL中，HashTable 是一个重要的底层数据结构，本题需要设计一个 HashTable，并实现以下功能：
1、基础功能
构造函数：初始化 HashTable 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 HashTable 中添加键值对
删除 HashTable 中的键值对
查询 HashTable 中的键值对
获取 HashTable 中键值对的数量
获取 HashTable 中的所有键值对
3、高级功能
实现键值对数量达到一定的阈值后，自动扩容的功能

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
insert 命令：
格式：insert [key] [value]
功能：在 HashTable 中添加键值对，如果键已经存在，则不进行任何操作
erase 命令：
格式：erase [key]
功能：删除 HashTable 中的键值对，如果键不存在，则不进行任何操作
find 命令：
格式：find [key]
功能：查询 HashTable 中的键值对
size 命令：
格式：size
功能：输出 HashTable 中键值对的数量
print 命令：
格式：print
功能：输出 HashTable 中所有键值对
clear 命令：
格式：clear
功能：清空哈希表

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
insert 命令: 无输出
erase 命令: 无输出
find 命令： 输出一个整数，独占一行，代表 key 对应的 value 值，如果 HashTable 中不存在对应的 key，则输出 not exsit
size 命令: 输出一个整数，独站一行，表示 HashTable 中键值对的数量
print 命令: 打印哈希表中所有键值对，格式为 [key1] [value1] [key2] [value2]...每个数字后都有一个空格，打印结果独占一行，如果 HashTable 中不存在键值对，则打印 empty
clear 命令: 无输出
*/

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
    class HashNode {
    public:
        Key key;
        Value value;
        
        explicit HashNode(const Key& key) : key(key), value() {}
        
        HashNode(const Key& key, const Value& value) : key(key), value(value) {}
        
        bool operator==(const HashNode& other) const { return key == other.key; }
        
        bool operator!=(const HashNode& other) const { return key == other.key; }
        
        bool operator<(const HashNode& other) const { return key < other.key; }
        
        bool operator>(const HashNode& other) const { return key > other.key; }
        
        bool operator==(const Key& key_) const { return key == key_; }
        
        void print() const { std::cout << key << " " << value << " "; }
    };
    
private:
    using Bucket = std::list<HashNode>;
    std::vector<Bucket> buckets;
    Hash hash_function;
    size_t table_size;
    size_t num_elements;
    float max_load_elements = 0.75;
    
    size_t hash(const Key& key) const { return hash_function(key) % table_size; }
    
    void rehash(size_t new_size) {
        std::vector<Bucket> new_buckets(new_size);
        for (Bucket& bucket : buckets) {
            for(HashNode& hash_node : bucket) {
                size_t new_index = hash_function(hash_node.key) % new_size;
                new_buckets[new_index].push_back(hash_node);
            }
        }
        buckets = std::move(new_buckets);
        table_size = new_size;
    }
    
public:
    HashTable(size_t size = 10, const Hash& hash_func = Hash())
        : buckets(size), hash_function(hash_func), table_size(size), num_elements(0) {}
        
    void insert(const Key& key, const Value& value) {
        if ((num_elements + 1) > max_load_elements * table_size) {
            rehash(table_size == 0 ? 2 : 2 * table_size);
        }
        size_t index = hash(key);
        std::list<HashNode>& bucket = buckets[index];
        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
            bucket.push_back(HashNode(key, value));
            ++num_elements;
        }
    }
    
    void insert_key(const Key& key) { insert(key, Value{}); }
    
    void erase(const Key& key) {
        size_t index = hash(key);
        std::list<HashNode>& bucket = buckets[index];
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end()) {
            bucket.erase(it);
            --num_elements;
        }
    }
    
    Value* find(const Key& key) {
        size_t index = hash(key);
        std::list<HashNode>& bucket = buckets[index];
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end()) return &it->value;
        return nullptr;
    }
    
    size_t size() const { return num_elements; }
    
    void print() const {
        for (size_t i = 0; i < table_size; ++i) {
            for (const HashNode& hash_node : buckets[i]) {
                hash_node.print();
            }
        }
        std::cout << std::endl;
    }
    
    void clear() {
        buckets.clear();
        num_elements = 0;
        table_size = 0;
    }
};

int main() {
    HashTable<int, int> hash_table;
    int N;
    std::cin >> N;
    getchar();
    std::string line;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int key, value;
        if (command == "insert") {
            iss >> key >> value;
            hash_table.insert(key, value);
        } else if (command == "erase") {
            if (hash_table.size() == 0) continue;
            iss >> key;
            hash_table.erase(key);
        } else if (command == "find") {
            if (hash_table.size() == 0) {
                std::cout << "not exist" << std::endl;
                continue;
            }
            iss >> key;
            int* res = hash_table.find(key);
            if (res == nullptr) std::cout << "not exist" << std::endl;
            else std::cout << *res << std::endl;
        } else if (command == "size") {
            std::cout << hash_table.size() << std::endl;
        } else if (command == "print") {
            if (hash_table.size() == 0) std::cout << "empty" << std::endl;
            else hash_table.print();
        } else if (command == "clear") {
            hash_table.clear();
        }
    }
}
