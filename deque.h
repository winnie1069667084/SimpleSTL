#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Deque {
private:
    T* elements;
    size_t capacity;
    size_t size;
    size_t front_index;
    size_t back_index;

public:
    Deque() : elements(nullptr), capacity(0), size(0), front_index(0), back_index(0) {}
    
    ~Deque() {
        clear();
        delete[] elements;
    }
    
    void clear() {
        front_index = back_index = 0;
        size = 0;
    }
    
    void push_back(const T& val) {
        if (size == capacity) resize();
        elements[back_index] = val; // 注意这行与push_front()相反，因为back_index指向的是未赋值的数组元素
        back_index = (back_index + 1) % capacity;
        ++size;
    }
    
    void push_front(const T& val) {
        if (size == capacity) resize();
        front_index = (front_index - 1 + capacity) % capacity;
        elements[front_index] = val;
        ++size;
    }
    
    void pop_back() {
        if (size == 0) throw std::out_of_range("Deque is empty");
        back_index = (back_index - 1 + capacity) % capacity;
        --size;
    }
    
    void pop_front() {
        if (size == 0) throw std::out_of_range("Deque is empty");
        front_index = (front_index + 1) % capacity;
        --size;
    }
    
    size_t get_size() const {
        return size;
    }
    
    void print_elements() const {
        size_t index = front_index;
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
    }
    
    T& operator[](size_t index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return elements[(front_index + index) % capacity];
    }
    
    const T& operator[](size_t index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return elements[(front_index + index) % capacity];
    }
    
private:
    void resize() {
        size_t new_capacity = capacity == 0 ? 1 : 2 * capacity;
        T* new_elements = new T[new_capacity];
        size_t index = front_index;
        for (size_t i = 0; i < size; ++i) {
            new_elements[i] = elements[index];
            index = (index + 1) % capacity;
        }
        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
        front_index = 0;
        back_index = size;
    }
};

int main() {
    Deque<int> my_deque;
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
            my_deque.push_back(val);
        } else if (command == "push_front") {
            iss >> val;
            my_deque.push_front(val);
        } else if (command == "pop_back") {
            if (my_deque.get_size() == 0) continue;
            my_deque.pop_back();
        } else if (command == "pop_front") {
            if (my_deque.get_size() == 0) continue;
            my_deque.pop_front();
        } else if (command == "clear") {
            my_deque.clear();
        } else if (command == "size") {
            std::cout << my_deque.get_size() << std::endl;
        } else if (command == "get") {
            iss >> val;
            std::cout << my_deque[val] << std::endl;
        } else if (command == "print") {
            if (my_deque.get_size() == 0) std::cout << "empty" << std::endl;
            else my_deque.print_elements();
        }
    }
}

// Q&A
// Q:双端队列循环数组实现的push_front()为什么要加上一个capacity再取余，直接取余不行吗
// A:在 C++ 中负数取余的结果是可能返回负值，这会导致数组访问越界，从而引发未定义行为。
