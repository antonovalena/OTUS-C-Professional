#include <memory>
#include <iostream>
#include <utility>
#include <cstddef>


template<typename T, size_t capacity=10>
struct reserving_allocator {
    using value_type = T;
	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

	template <typename U>
	struct rebind {
		using other = reserving_allocator<U>;
	};

    reserving_allocator() = default;
	~reserving_allocator() = default;

	template <typename U>
	reserving_allocator(const reserving_allocator<U> &) {}

	T *allocate(std::size_t n) {
        if (allocated_size + n > capacity) {
           throw std::bad_alloc(); 
        }
		auto p = &storage[allocated_size * sizeof(T)];
        allocated_size += n;
		if (!p) {
			throw std::bad_alloc();
        }
		return reinterpret_cast<pointer>(p);
	}

	void deallocate(T *, std::size_t) {}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		new (p) U(std::forward<Args>(args)...);
	}

	template <typename U>
	void destroy(U *p) {
		p->~U();
	}

private:
    size_t allocated_size = 0;
    std::byte storage[sizeof(T) * capacity];
};