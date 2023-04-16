#include "reserving_allocator.h"
#include "custom_container.h"

#include <map>

template<typename Alloc, size_t n>
void fill_factorial_map(std::map<int, int, std::less<int>, Alloc>& input_map) {
    if (n == 0) { return; }
    int fact_value = 1;
    input_map[0] = 1;
    for(size_t i = 1; i < n; ++i) {
        fact_value *= i;
        input_map[i] = fact_value;
    }
}

template<typename Alloc>
void print_factorial_map(std::map<int, int, std::less<int>, Alloc>& input_map) {
    for(size_t i = 0; i < input_map.size(); ++i) {
        std::cout << i << " " << input_map[i] << std::endl;
    }
}

void test_allocator() {
    std::cout << "Standard allocator section" << std::endl;

    std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int> > > factorialMap;
    fill_factorial_map<std::allocator<std::pair<const int, int> >, 10>(factorialMap);
    print_factorial_map<std::allocator<std::pair<const int, int> > >(factorialMap);

    std::cout << "Custom allocator section" << std::endl;

    std::map<int, int, std::less<int>, reserving_allocator<std::pair<const int,int>, 10 > > customAllocFactorialMap;
    fill_factorial_map<reserving_allocator<std::pair<const int,int>, 10>, 10>(customAllocFactorialMap);
    print_factorial_map<reserving_allocator<std::pair<const int, int>, 10> >(customAllocFactorialMap);
}

void test_container() {
    const int n = 10;

    std::cout << "Standard allocator section" << std::endl;

    CustomContainer<int, std::allocator<Node<int> > > container_std;
    for (int i = 0; i < n; ++i) {
        container_std.add(i);
    }
    container_std.print();

    std::cout << "Custom allocator section" << std::endl;

    CustomContainer<int, reserving_allocator<Node<int>, n> > container_custom;
    for (int i = 0; i < n; ++i) {
        container_custom.add(i);
    }
    container_custom.print();

}

int main(int, char**) {
    test_allocator();
    test_container();

    return 0;
}