#include <atomic>
#include <iostream>

template <typename T> class shared_ptr {
public:
    shared_ptr(T* ptr = nullptr) : m_ptr(ptr), m_refCount(new std::atomic<int>(1)) {}
    ~shared_ptr() { Release(); }

    shared_ptr(const shared_ptr& other) { (*m_refCount)++; }

    shared_ptr& operator=(const shared_ptr& other) {
        if (&other != this) {
            Release();
            m_ptr      = other.m_ptr;
            m_refCount = other.m_refCount;
            (*m_refCount)++;
        }
        return *this;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }

private:
    void Release() {
        (*m_refCount)--;
        if (*m_refCount == 0) {
            delete m_ptr;
            delete m_refCount;
        }
    }

    T*                m_ptr;
    std::atomic<int>* m_refCount;
};

struct Foo {
    int val;
};

int main() { 
    shared_ptr<Foo> foo(new Foo(5)); 
    std::cout << foo->val;
    return 0;
}