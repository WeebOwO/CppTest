#include <iostream>
#include <type_traits>
using namespace std;

// mayers lazy
class LazySingle {
public:
    static LazySingle& GetInstance() {
        static LazySingle instance;
        return instance;
    };
    LazySingle(const LazySingle& other) = delete;
    LazySingle& operator=(const LazySingle& other) = delete;
private:
    LazySingle() = default;
};


class EagerSingle {
public:
    EagerSingle(const LazySingle& other) = delete;
    EagerSingle& operator=(const LazySingle& other) = delete;
private:        
    EagerSingle() {std::cout << "Construct!\n";}
    static EagerSingle* instance;
};

EagerSingle* EagerSingle::instance = new EagerSingle();

int main() {
    std::cout << "main start!\n";
    return 0;
}