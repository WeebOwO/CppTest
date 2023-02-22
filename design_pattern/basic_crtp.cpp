/*
 * crtp implementation
 */
#include <iostream>

// common virutal function replace
template <typename child> class Base {
public:
    void Print() { Derived()->PrintImpl(); }
    void PrintImpl() { return; }

private:
    child* Derived() { return static_cast<child*>(this); }
};

class Derived : public Base<Derived> {
public:
    void PrintImpl() { std::cout << "Here is derived!\n"; }
};

// try to enhance base class function
template <typename child> struct NoTEqual {
    bool operator!=(const child& rhs) { return !static_cast<child*>(this)->operator==(rhs); }
};

struct D : public NoTEqual<D> {
    bool operator==(const D& rhs) { return value == rhs.value; }
    D(int value) : value(value) {}
    int value;
};

template <typename D>
class Registry { 
public:
    static size_t count;
    static D* head; 
    D* prev;
    D* next;
    
protected:
    Registry() { 
        ++count;
        prev = nullptr;
        next = head;
        head = static_cast<D*>(this);
        if (next) next->prev = head;
    }
    Registry(const Registry&) { 
        ++count;
        prev = nullptr;
        next = head;
        head = static_cast<D*>(this);
        if (next) next->prev = head;
    }
    ~Registry() {
        --count;
        if (prev) prev->next = next;
        if (next) next->prev = prev;
        if (head == this) head = next;
    }
};

template <typename D> size_t Registry<D>::count(0);
template <typename D> D* Registry<D>::head(nullptr);

int main() {
    Base<Derived>* p = new Derived;
    p->Print();

    D child1(1);
    D child2(2);
    std::cout << (child1 == child2);
    return 0;
}
