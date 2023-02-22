/*
 * std::span test
 */

#include <array>
#include <iostream>
#include <span>
#include <vector>

// imitate std::span
namespace m_std {
template <typename T> class Span {
public:
    template <size_t N> Span(T (&arr)[N]) : m_arr(arr), m_size(N) {}

    template <size_t N> Span(std::array<T, N>& arr) : m_arr(arr), m_size(N) {}

    Span(T* arr, size_t n) : m_arr(arr), m_size(n) {}

    T*     data() { return m_arr; }
    size_t size() { return m_size; }

private:
    T*     m_arr;
    size_t m_size;
};
} // namespace m_std

void PrintSpan(std::span<int> span) {
    for (auto val : span) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 1. Init test data
    int                  cStyle[5] = {1, 2, 3, 4, 5};
    std::unique_ptr<int> pointerType(new int[5]{1, 2, 3, 4, 5});
    std::vector<int>     vecStyle = {1, 2, 3, 4, 5};
    std::array<int, 5>   stdArray = {1, 2, 3, 4, 5};

    // 2. Test different vec
    PrintSpan(vecStyle);
    PrintSpan(cStyle);
    PrintSpan(stdArray);
    PrintSpan({pointerType.get(), 5});

    return 0;
}
