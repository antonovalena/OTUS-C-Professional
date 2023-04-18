#include <iostream>
#include <exception>


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

    Node<T>* getNodes() { return nodes_; }

    void extract() {
        if (empty()) {
            throw std::runtime_error("Cannot extract from empty container");
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
            throw std::runtime_error("Failed to allocate memory");
        }

        allocator_.construct(nodes_, val, cur_top);
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