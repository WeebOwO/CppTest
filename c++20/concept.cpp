/*
 * C++20 concept
 */
#include <concepts>
#include <iostream>
#include <memory>
#include <utility>

// 简洁的concept使用
bool is_power_of_2(std::integral auto target) {
    std::cout << "Integral part!\n";
    return (target > 0) && (target & (target - 1)) == 0;
}

bool is_power_of_2(std::floating_point auto target) {
    std::cout << "Float part!\n";
    int     exponent;
    const T mantissa = std::frexp(target, &exponent);
    return mantissa == T(0.5);
}

// concept的组合
template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

auto test_func(arithmetic auto target) {
    cout << "Arithmetic part!\n";
    return;
}

// 用requires子句来定义concept
template <typename T>
concept hashable = requires(T t) {
                       { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
                   };

template <hashable T> class hash_map;

template <typename T> int main() {
    std::cout << is_power_of_2(0.25) << std::endl;
    return 0;
}