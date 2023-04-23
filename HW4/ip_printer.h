#include <iostream>
#include <type_traits>
#include <string>
#include <cstddef>

template <typename I>
typename std::enable_if_t<std::is_integral<I>::value>
print_ip(I num) {
    size_t s = sizeof(num);
    const auto byteArray = reinterpret_cast<const std::byte*>(&num);;
    for (size_t i = s - 1; i > 0; --i) {
        std::cout << (int)byteArray[i] << ".";
    }
    if (s > 0) {
        std::cout << (int)byteArray[0] << std::endl;
    }
}

template<typename S>
typename std::enable_if_t<std::is_same<std::string, S>::value>
print_ip(S str) {
  std::cout << str << std::endl;
}

template<typename T>
struct has_c_iterator
{
private:
    typedef char                      yes;
    typedef struct { char array[2]; } no;

    template<typename C> static yes test(typename C::const_iterator*);
    template<typename C> static no  test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template<typename T> 
struct is_container : std::integral_constant<bool, has_c_iterator<T>::value and !std::is_same<std::string, T>::value> {};

template <typename C>
typename std::enable_if_t<is_container<C>::value>
print_ip(const C& container) {
    if (container.size() == 0) {
        return;
    }
    auto it =  container.begin();
    std::cout << *it;
    it++;
    while (it != container.end()) {
        std::cout << "." << *it;
        it++;
    }
    std::cout << std::endl;
}