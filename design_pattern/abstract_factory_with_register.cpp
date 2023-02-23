#include <iostream>
#include <map>
#include <string>

template <class AbstractProduct> 
class AbstractRegister {
public:
    AbstractRegister()                       = default;
    virtual AbstractProduct* createProduct() = 0;
};

template <class AbstractProduct> 
class Factory {
public:
    static AbstractProduct* createProduct(std::string name) {
        AbstractRegister<AbstractProduct>* factoryRegister =
            Factory<AbstractProduct>::name2Product[name];
        return factoryRegister->createProduct();
    }
    static void _factoryRegister(std::string name, AbstractRegister<AbstractProduct>* reg) {
        name2Product[name] = reg;
    }
    static std::map<std::string, AbstractRegister<AbstractProduct>*> name2Product;
};

template <class AbstractProduct>
std::map<std::string, AbstractRegister<AbstractProduct>*> Factory<AbstractProduct>::name2Product;

template <class AbstractProduct, class Product>
class FactoryRegister : virtual AbstractRegister<AbstractProduct> {
public:
    static void factoryRegister(std::string name) {
        Factory<AbstractProduct>::_factoryRegister(
            name,
            (AbstractRegister<AbstractProduct>*)new FactoryRegister<AbstractProduct, Product>());
    }
    AbstractProduct* createProduct() override { return (AbstractProduct*)new Product(); }
};

class Food {
public:
    Food()              = default;
    virtual ~Food()     = default;
    virtual void show() = 0;
};

class Cake : virtual Food {
public:
    Cake() { std::cout << "Food create" << std::endl; }
    ~Cake() override { std::cout << "Food delete" << std::endl; }
    void show() override { std::cout << "Cake" << std::endl; }
};

int main() {
    FactoryRegister<Food, Cake>::factoryRegister("cake");
    auto cake = Factory<Food>::createProduct("cake");
    cake->show();
}