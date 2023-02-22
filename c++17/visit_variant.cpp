/*
 * std::variant and std::visit test
 */

#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

using var_t = std::variant<int, long, double, std::string>;

template <typename T> constexpr bool always_false_v = false;

template <class... Ts> struct overloaded : public Ts... {
    using Ts::operator()...;
};

#define Test2

int main() {
    std::vector<var_t> vec = {10, 15l, 2.0, "Hello"};

#ifdef Test1
    for (auto& val : vec) {
        // 1. basic void test
        // std::visit([&](auto&& args) {std::cout << args << std::endl;}, val);
        // 2. constexpr test
        std::visit(
            [&](auto&& args) {
                using T = std::decay_t<decltype(args)>;
                if constexpr (std::is_same_v<T, int>) {
                    std::cout << "This is int type!\n";
                } else if constexpr (std::is_same_v<T, long>) {
                    std::cout << "This is long type!\n";
                } else if constexpr (std::is_same_v<T, double>) {
                    std::cout << "This is dobule type!\n";
                } else if constexpr (std::is_same_v<T, std::string>) {
                    std::cout << "This is string type!\n";
                } else {
                    static_assert(always_false_v<T>, "No match!\n");
                }
            },
            val);
    }
#endif

#ifdef Test2
    for (auto& val : vec) {
        std::visit(overloaded{[](auto arg) { std::cout << arg << ' '; },
                              [](double arg) { std::cout << std::fixed << arg << ' '; },
                              [](const std::string& arg) { std::cout << std::quoted(arg) << ' '; }},
                   val);
    }
#endif
    return 0;
}