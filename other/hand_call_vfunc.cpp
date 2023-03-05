#include <iostream>
#include <functional>

class Base {
public:
    virtual void Show() {
        std::cout << "i am base\n";
    }
};

class Derived : public Base {
public:
    void Show() override {
        std::cout << "i am derived\n";
    }    
};


int main() {
    using VoidFunc = void(*)();
    Derived de;
    VoidFunc vi = (VoidFunc)(*(int*)(*(int*)(&de)));
    vi();
    return 0;
}