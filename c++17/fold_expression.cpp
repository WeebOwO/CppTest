/*
 * fold expression test
 */
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

template <typename... T> auto Add(T... args) { return (args + ...); }

template <typename T, typename... Args> void PushVec(std::vector<T>& v, Args&&... args) {
    static_assert((std::is_constructible_v<T, Args&&> && ...));
    (v.push_back(std::forward<Args>(args)), ...);
}

int main() {
    auto res = Add(1, 2, 3, 4);
    std::cout << res << std::endl;

    std::vector<int> t;
    PushVec(t, 1, 2, 3, 4);
    for (auto val : t)
        std::cout << val << " ";

    return 0;
}