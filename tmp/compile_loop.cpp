/*
 * Compile time loop test
 */

#include <iostream>
#include <utility>

constexpr int iter_times = 10;

int main() {
    constexpr auto do_something = [&](size_t i) { std::cout << i << " "; };

    constexpr auto do_another_thing = [&](size_t i) { return i; };
    // 普通循环
    for (size_t i = 0; i < iter_times; ++i) {
        do_something(i);
    }

    std::cout << std::endl;
    [&]<std::size_t... p>(std::index_sequence<p...>) { (do_something(p), ...); }
    (std::make_index_sequence<iter_times>{});

    // 更进一步！
    std::cout << std::endl;
    [&]<std::size_t... p>(std::index_sequence<p...>) { std::cout << (do_another_thing(p) + ...); }
    (std::make_index_sequence<iter_times>{});

    return 0;
}
