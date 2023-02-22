/*
 * C++ 20 ranges tset
 */

#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

void BasicViewTest() {
    // try ranges::view!
    std::cout << "Test basic view, We will try to generate first 10 even number!\n";
    using namespace std::ranges;
    auto is_even   = [&](int target) { return target % 2 == 0; };
    auto even_view = views::iota(1) | views::filter(is_even) | views::take(10);
    for (const auto& val : even_view) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return;
}

// Test range sort
struct Student {
    std::string name_;
    size_t      age_;
};
void BasicRangeSortTest() {
    std::cout << "Test range sort!\n";
    std::vector<int> test_layout = {1, 3, 5, 2, 4};
    std::ranges::sort(test_layout);
    for (auto&& val : test_layout) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Test range project sort!\n";
    std::vector<Student> students = {{"small_red", 10}, {"small_blue", 20}, {"small_black", 15}};
    std::ranges::sort(students, {}, &Student::age_);
    for (auto&& student : students) {
        std::cout << student.name_ << " " << student.age_ << std::endl;
    }
}

int main() {
    BasicViewTest();
    BasicRangeSortTest();
    return 0;
}