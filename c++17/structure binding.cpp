/*
 * structure binding test
 */

#include <iostream>
#include <map>
#include <tuple>
#include <vector>

struct foo {
    int    x;
    double y;
};

std::tuple<int, double> func() { return {1, 2.2}; }

void bindFromTuple() {
    std::cout << "Bind from tuple!\n";
    auto [x, y] = func();
}

void bindFromStruct() {
    std::cout << "Bind from struct!";
    auto [x, y] = foo(1, 2.2);
}

void bindFromMap() {
    std::map<int, int> hash{{1, 1}};
    for (const auto& [key, value] : hash) {
        // to do
    }
}

void bindFromPair() {
    std::pair<int, int> pairTest{1, 1};
    auto [x, y] = pairTest;
}

class Entry {
public:
    void Init() {
        name_ = "name";
        age_  = 10;
    }

    std::string GetName() const { return name_; }
    int         GetAge() const { return age_; }

private:
    std::string name_;
    int         age_;
};

template <size_t I> auto get(const Entry& e) {
    if constexpr (I == 0) return e.GetName();
    else if constexpr (I == 1)
        return e.GetAge();
}

namespace std {
template <> struct tuple_size<Entry> : integral_constant<size_t, 2> {};
template <> struct tuple_element<0, Entry> {
    using type = std::string;
};
template <> struct tuple_element<1, Entry> {
    using type = int;
};
} // namespace std

int main() {
    Entry e;
    e.Init();
    auto [name, age] = e;
    std::cout << name << " " << age << std::endl;
    return 0;
}