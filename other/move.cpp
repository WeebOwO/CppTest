#include <iostream>
#include <utility>

struct Foo {
    int data;
};

// c++11 move
template <typename T>
typename std::remove_reference<T>::type && move11(T&& param) {
    using returnType = typename std::remove_reference<T>::type&&;
    return static_cast<returnType&&>(param);
}

template<typename T>
decltype(auto) move14(T&& param) {
    using returnType = std::remove_reference_t<T>;
    return static_cast<returnType&&>(param);
}

void MoveC11Test() {
    Foo t{};
    decltype(auto) moveFoo = move11(t);
    std::cout << std::is_same_v<Foo&&, decltype(moveFoo)> << std::endl;
}

void MoveC14Test() {
    Foo t{};
    decltype(auto) moveFoo = move14(t);
    std::cout << std::is_same_v<Foo&&, decltype(moveFoo)> << std::endl;
}

int main() {
    MoveC11Test();
    MoveC14Test();
    return 0;
}