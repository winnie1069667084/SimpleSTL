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
    size_t size; // 数组中的元素个数  // 为何要用size_t?
    
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
    Vector& operator=(const Vector& other) { // Vector&的作用？
        if (this != &other) { // 检查自赋值，&other的作用？
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
        return *this; // *this的作用？
    }
    
    // 2.核心功能
    // 添加元素到末尾
    void push_back(const T& value) {
        if (size == capacity) reverse(capacity == 0 ? 1 : 2 * capacity);
        elements[size++] = value;
    }
    // 获取元素个数
    size_t get_size() const { // const的作用？
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
    const T& operator[](size_t index) { // 为什么要const和non-const版本分开写
        if (index >= size) throw std::out_of_range("Index out of range");
        return elements[index];
    }
    // 在指定位置插入元素 
    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (size == capacity) reverse(capacity == 0 ? 1 : 2 * capacity);
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
    const T* begin() {
        return elements;
    }
    const T* end() {
        return elements + size;
    }
    void print_elements() const{
        for (size_t i = 0; i < size; ++i) std::cout << elements[i] << " ";
        std::cout << std::endl;
    }
}
