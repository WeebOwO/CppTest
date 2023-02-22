/*
*   memory control
*/

#include <iostream>
#include <vector>

struct Foo {
    Foo () {
       std::cout << "Construct!\n"; 
    }
    ~Foo() {
        std::cout << "Deconstruct!\n";
    }

    void* operator new(size_t size) {
        std::cout << size << std::endl;
        return malloc(size);
    }    
    void* operator new[](size_t size) {
        std::cout << size << std::endl;
        return malloc(size);
    } 
    void operator delete(void* pointer) {
        std::cout << "delete!\n";
        delete(pointer);
    }
    void operator delete[](void* pointer) {
        free(pointer);
    }
    int data;
};

int main() {
    // test new and placement new
    Foo* foo = new Foo();
    int backup = 5;
    int* targetInt = new(&backup) int;
    *targetInt = 3; 

    // backup should be 3
    std::cout << backup << std::endl;

    // array new and array delete test
    auto fooVec = new Foo[5];
    // delete fooVec will call ~Foo() only once but delete[] is different
    delete [] fooVec;
    return 0;
}