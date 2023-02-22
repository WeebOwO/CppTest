#include <iostream>

#define CACHE_LINE 32

__declspec(align(CACHE_LINE)) struct Vec4 {
    float x, y, z, w;
};

int main() {
    Vec4 v;
    std::cout << &v;
    return 0;
}