#include <iostream>
#include <memory>
#include <vector>

struct Foo {
    int data{0};
};

struct Bar : std::enable_shared_from_this<Bar> {
    int                     data{1};
    void                    processed() { processedVec.emplace_back(this); }
    static std::vector<Bar> processedVec;
};

void ExpiredTest() {
    auto               spw = std::make_shared<Foo>();
    std::weak_ptr<Foo> weak(spw);
    spw = nullptr;
    // expired test
    if (weak.expired()) { std::cout << "expried!\n"; }

    std::shared_ptr<Foo> spw1 = weak.lock();
    // expired test
    if (spw1 == nullptr) { std::cout << "expried!\n"; }

    std::shared_ptr<Foo> swp2(weak);
    return;
}

int main() {
    ExpiredTest();
    return 0;
}