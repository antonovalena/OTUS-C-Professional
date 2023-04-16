#include <iostream>


template<typename T>
struct Node {
    Node(T value, Node<T>* prev) : value_(value), prev_(prev) {}

    T value() { return value_; }
    Node<T>* prev() { return prev_; }
    ~Node() {}

private:
    T value_;
    Node<T>* prev_;
};

template<typename T, typename Allocator>
struct CustomContainer {
    bool empty() const { return nodes_ == nullptr; }

    void extract() {
        if (empty()) {
            return;
        }
        Node<T>* prev_filled = nodes_->prev();
        allocator_.destroy(nodes_);
        allocator_.deallocate(nodes_, 1);
        nodes_ = prev_filled;
    }

    void add(T val) {
        Node<T>* cur_top = nodes_;
        try {
            nodes_ = allocator_.allocate(1);
        } catch (...) {
            std::cout << "Failed to allocate memory" << std::endl;
            return;
        }

        allocator_.construct(nodes_, val, cur_top);
    }

    void print() {
        Node<T>* cur_node = nodes_;
        while (cur_node != nullptr) {
            std::cout << cur_node->value() << std::endl;
            cur_node = cur_node->prev();
        }
    }

    ~CustomContainer() {
        while (!empty()) {
            extract();
        }
    }

    private:
    Allocator allocator_;
    Node<T>* nodes_ = nullptr;
};