/*
【题目描述】
在STL中，红黑树是一个重要的底层数据结构，本题需要设计一个 RedBlackTree 类，实现如下功能：
1、基础功能
构造函数：初始化 RedBlackTree 实例
析构函数：清理资源，确保无内存泄露
2、核心功能
在 RedBlackTree 中插入一个节点
在 RedBlackTree 中删除一个节点
查询 RedBlackTree 中某个节点是否存在
获取 RedBlackTree 中节点的数量
获取 RedBlackTree 中所有的节点
RedBlackTree 中的节点拥有两个属性，一个是 key，一个是 value，本题题意规定如果 key 相同，则代表是同一个节点。

【输入描述】
题目的包含多行输入，第一行为正整数 N, 代表后续有 N 行命令序列。
接下来 N 行，每行包含一个命令，命令格式为 [operation] [parameters] ，具体命令如下：
insert 命令：
格式：insert [key] [value]
功能：在 RedBlackTree 中添加节点，如果节点已经存在，则不进行任何操作
remove 命令：
格式：remove [key]
功能：删除 RedBlackTree 中的节点，如果节点不存在，则不进行任何操作
at 命令：
格式：at [key]
功能：查询 RedBlackTree 中的节点
size 命令：
格式：size
功能：获取 RedBlackTree 中节点的数量
print 命令：
格式：print
功能：按照中序遍历输出 RedBlackTree 中所有节点，格式为 [key1] [value1] [key2] [value2]

【输出描述】
输出为每行命令执行后的结果，具体输出格式如下：
insert 命令: 无输出
remove 命令: 无输出
at 命令: 输出一个整数，独占一行，代表 RedBlackTree 中 key 对应的 value，如果 key 不存在，则输出 not exsit
size 命令: 输出一个整数，独占一行，代表 RedBlackTree 中节点的数量
print 命令: 按照中序遍历输出 RedBlackTree 中所有节点的 key 和 value，格式为 [key1] [value1] [key2] [value2]...每个数字后都跟有一个空格，输出独占一行，如果 RedBlackTree 中不包含任何节点，则输出 empty
*/

#include <iostream>
#include <sstream>
#include <string>

enum class Color { RED, BLACK } ;

template <typename Key, typename Value> class RedBlackTree {
    class Node {
    public:
        Key key;
        Value value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        
        Node(const Key& k, const Value& v, Color c, Node* p = nullptr)
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p) {}
        
        Node() : color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
private:
    Node* _root;
    Node* _nil; // 虚拟叶子节点
    size_t _size;
    
public:
    RedBlackTree() : _root(nullptr), _nil(new Node()), _size(0) { _nil->color = Color::BLACK; }
    
    ~RedBlackTree() { deleteTree(_root); }
    
    void insert(const Key& key, const Value& value) { insertNode(key, value); }
    
    void remove(const Key& key) {
        Node* node = lookUp(key);
        if (node != nullptr) {
            deleteNode(node);
            --_size;
        }
    }
    
    Value* at(const Key& key) {
        Node* node = lookUp(key);
        if (node != nullptr) return &node->value;
        return nullptr;
    }
    
    size_t getSize() { return _size; }
    
    bool empty() { return _size == 0; }

    void print() {
        inorderTraversal(_root);
        std::cout << std::endl;
    }
    
    void clear() {
        deleteTree(_root); // 范例代码给出的deleteNode(_root)我认为是错误的
        _size = 0;
    }
    
private:
    void deleteTree(Node* node) { // 递归删除只能选择后序遍历，其他顺序会引发未定义行为
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
    
    Node* lookUp(const Key& key) {
        Node* node = _root;
        while (node) {
            if (key < node->key) node = node->left;
            else if (key > node->key) node = node->right;
            else return node;
        }
        return nullptr;
    }
    
    void rightRotate(Node* node) {
        if (!node || !node->left) return;
        Node* l_son = node->left;
        node->left = l_son->right; // l_son->right一定存在吗？
        if (l_son->right) l_son->right->parent = node;
        l_son->parent = node->parent;
        if (!node->parent) _root = l_son;
        else if (node == node->parent->left) node->parent->left = l_son;
        else node->parent->right = l_son;
        l_son->right = node;
        node->parent = l_son;
    }
    
    void leftRotate(Node* node) {
        if (!node || !node->right) return;
        Node* r_son = node->right;
        node->right = r_son->left;
        if (r_son->left) r_son->left->parent = node;
        r_son->parent = node->parent;
        if (!node->parent) _root = r_son;
        else if (node == node->parent->left) node->parent->left = r_son;
        else node->parent->right = r_son;
        r_son->left = node;
        node->parent = r_son;
    }
    
    void insertNode(const Key& key, const Value& value) {
        Node* new_node = new Node(key, value, Color::RED);
        Node* parent = nullptr; // 新节点的父节点指针
        Node* node = _root;
        while (node) { // 遍历，找到新节点的父节点正确位置
            parent = node;
            if (key < node->key) {
                node = node->left;
            } else if (key > node->key) {
                node = node->right;
            } else {
                delete new_node;
                return;
            }
        }
        ++_size;
        new_node->parent = parent;
        if (!parent) _root = new_node;
        else if (key < parent->key) parent->left = new_node;
        else parent->right = new_node;
        insertFixup(new_node);
    }
    
    void insertFixup(Node* target) {
        // 目标节点父节点为红，违反不红红，需要修复
        while (target->parent && target->parent->color == Color::RED) {
            if (target->parent == target->parent->parent->left) { // L
                Node* uncle = target->parent->parent->right;
                if (uncle && uncle->color == Color::RED) { // 插入节点的叔叔是红色，叔父爷变色，爷爷变插入结点
                    flipColor(uncle);
                    flipColor(target->parent);
                    flipColor(target->parent->parent);
                    target = target->parent->parent;
                } else { // 插入节点的叔叔是黑色，判断形态（LL, RR, LR, RL），并变色
                    if (target == target->parent->right) { // LR
                        target = target->parent;
                        leftRotate(target);
                    }
                    flipColor(target->parent); // LL
                    flipColor(target->parent->parent);
                    rightRotate(target->parent->parent);
                }
            } else { // R
                Node* uncle = target->parent->parent->left;
                if (uncle && uncle->color == Color::RED) {
                    flipColor(uncle);
                    flipColor(target->parent);
                    flipColor(target->parent->parent);
                    target = target->parent->parent;
                } else {
                    if (target == target->parent->left) { // RR
                        target = target->parent;
                        rightRotate(target);
                    }
                    flipColor(target->parent); // RL
                    flipColor(target->parent->parent);
                    leftRotate(target->parent->parent);
                }
            }
        }
        _root->color = Color::BLACK; // 始终保持根节点为黑色
    }

    void deleteNode(Node* del) {
        Node* rep = del; // 替代节点
        Node* child = nullptr; // 替代节点的孩子节点
        Node* rep_parent; // 替代节点的父节点
        Color orig_color = rep->color; // 保存删除节点的原初颜色
    
        // 如果删除节点没有左孩子
        if (!del->left) {
            rep = del->right;
            rep_parent = del->parent;
            orig_color = getColor(rep);
            replaceNode(del, rep);
        } else if (!del->right) {
            rep = del->left;
            rep_parent = del->parent;
            orig_color = getColor(rep);
            replaceNode(del, rep);
        } else {
            rep = findMinimumNode(del->right);
            orig_color = rep->color;
            // 如果rep不是del的直接右孩子
            if (rep != del->right) {
                rep_parent = rep->parent;
                child = rep->right;
                rep->parent->left = child;
                if (child != nullptr) child->parent = rep_parent;
                del->left->parent = rep;
                del->right->parent = rep;
                rep->left = del->left;
                rep->right = del->right;
                if (del->parent != nullptr) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                        rep->parent = del->parent;
                    } else {
                        del->parent->right = rep;
                        rep->parent = del->parent;
                    }
                } else { // 如果删除节点没有父节点说明其为根节点
                    _root = rep;
                    rep->parent = nullptr;
                }
            } else { // 如果rep是del的直接右孩子
                child = rep->right;
                rep->left = del->left;
                del->left->parent = rep;
                if (del->parent != nullptr) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                        rep->parent = del->parent;
                    } else {
                        del->parent->right = rep;
                        rep->parent = del->parent;
                    }
                } else {
                    _root = rep;
                    rep->parent = nullptr;
                }
                rep_parent = rep;
            }
        }
    
        if (rep != nullptr) rep->color = del->color;
        else orig_color = del->color;
    
        if (orig_color == Color::BLACK) {
            if (child != nullptr) {
                deleteFixup(child);
            } else {
                _nil->parent = rep_parent;
                if (rep_parent != nullptr) {
                    if (rep_parent->left == nullptr) rep_parent->left = _nil;
                    else rep_parent->right = _nil;
                }
                deleteFixup(_nil);
                dieConnectNil();
            }
        }
        delete del;
    }
  
    void deleteFixup(Node* node) {
        if (node == _nil && node->parent == nullptr) return;
        while (node != _root) {
            if (node == node->parent->left) { // 讨论node为左节点情况
                Node* brother = node->parent->right;
                // 1.兄弟节点是红色
                if (getColor(brother) == Color::RED) {
                    // 兄父变色，朝node旋转，更新兄弟节点
                    flipColor(brother);
                    flipColor(node->parent);
                    leftRotate(node->parent);
                    brother = node->parent->right;
                }
                // 2.兄弟节点是黑色，兄弟的孩子都是黑色
                if (getColor(brother->left) == Color::BLACK && getColor(brother->right) == Color::BLACK) {
                    // 兄弟变红，双黑上移
                    flipColor(brother);
                    node = node->parent;
                    if (getColor(node) == Color::RED) {
                        flipColor(node);
                        break;
                    }
                } else {
                    // 3.兄弟节点是黑色，左孩子红色，右孩子黑色（RL）
                    if (getColor(brother->right) == Color::BLACK) {
                        flipColor(brother->left);
                        flipColor(brother);
                        rightRotate(brother);
                        brother = node->parent->right;
                    }
                    // 4.兄弟节点是黑色，左孩子黑色，右孩子红色（RR）
                    setColor(brother, getColor(node->parent));
                    setColor(node->parent, Color::BLACK);
                    setColor(brother->right, Color::BLACK);
                    leftRotate(node->parent);
                    break;
                }
            } else { // 讨论node为右节点情况
                Node* brother = node->parent->left;
                if (getColor(brother) == Color::RED) {
                    flipColor(brother);
                    flipColor(node->parent);
                    rightRotate(node->parent);
                    brother = node->parent->left;
                }
                if (getColor(brother->right) == Color::BLACK && getColor(brother->left) == Color::BLACK) {
                    flipColor(brother);
                    node = node->parent;
                    if (getColor(node) == Color::RED) {
                        flipColor(node);
                        break;
                    }
                } else {
                    if (getColor(brother->left) == Color::BLACK) {
                        flipColor(brother->right);
                        flipColor(brother);
                        leftRotate(brother);
                        brother = node->parent->left;
                    }
                    setColor(brother, getColor(node->parent));
                    setColor(node->parent, Color::BLACK);
                    setColor(brother->left, Color::BLACK);
                    rightRotate(node->parent);
                    break;
                }
            }
        }
        setColor(node, Color::BLACK);
    }
    
    void flipColor(Node* node) {
        if (node == nullptr) return;
        node->color = (node->color == Color::BLACK) ? Color::RED : Color::BLACK;
    }
    
    void setColor(Node* node, Color color) {
        if (node == nullptr) return;
        node->color = color;
    }
    
    Color getColor(Node* node) {
        return node == nullptr ? Color::BLACK : node->color;
    }
    
    void inorderTraversal(Node* node) const {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        std::cout << node->key << " " << node->value << " ";
        inorderTraversal(node->right);
    }
    
    void replaceNode(Node* target_node, Node* new_node) {
        if (!target_node->parent) _root = new_node;
        else if (target_node == target_node->parent->left) target_node->parent->left = new_node;
        else target_node->parent->right = new_node;
        if (new_node) new_node->parent = target_node->parent;
    }
    
    Node* findMinimumNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }
    
    void dieConnectNil() {
        if (_nil == nullptr) return;
        if (_nil->parent != nullptr) {
            if (_nil == _nil->parent->left) _nil->parent->left = nullptr;
            else _nil->parent->right = nullptr;
        }
    }
};

int main() {
    RedBlackTree<int, int> rb_tree;
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
            rb_tree.insert(key, value);
        } else if (command == "remove") {
            iss >> key;
            rb_tree.remove(key);
        } else if (command == "at") {
            iss >> key;
            int* res = rb_tree.at(key);
            if (res == nullptr) std::cout << "not exist" << std::endl;
            else std::cout << *res << std::endl;
        } else if (command == "size") {
            std::cout << rb_tree.getSize() << std::endl;
        } else if (command == "print") {
            if (rb_tree.empty()) std::cout << "empty" << std::endl;
            else rb_tree.print();
        }
    }
}

// 左根右，根叶黑，不红红，黑路同
// 
// 在写红黑树代码时，没有图像和情况分析是完全写不出来的
// 以下是写代码时参考的视频：
// 红黑树插入动画讲解 - www.bilibili.com/video/BV1Xm421x7Lg
// 红黑树删除动画讲解 - www.bilibili.com/video/BV16m421u7Tb
