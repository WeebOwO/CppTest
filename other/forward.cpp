#include <iostream>
#include <utility>

struct Foo {

};

void Process(Foo& foo) {
    std::cout << "Lvalue here!\n";
}
void Process(Foo&& foo) {
    std::cout << "Rvalue here!\n";
}

template<typename T>
T&& forward(std::remove_reference_t<T>& parms) {
    return static_cast<T&&>(parms);
}

template<typename T>
void ProcessHelper(T&& parms) {
    Process(forward<T>(parms));
}

int main() {
    Foo a;
    ProcessHelper(a);
    ProcessHelper(std::move(a));
    return 0;
}