#include <iostream>

class Shoe {
public:
    virtual void show() const = 0;
    virtual ~Shoe()           = default;
};

class Nike : public Shoe {
public:
    void show() const override { std::cout << "I am nike!\n"; }
};

class Clothe {
public:
    virtual void show() const = 0;
    virtual ~Clothe()         = default;
};

class Uniqlo : public Clothe {
public:
    void show() const override { std::cout << "I am Uniqlo\n"; }
};

template <typename AbstractProduct> class AbstractFactory {
public:
    [[nodiscard("you lost some product man")]] virtual AbstractProduct* CreateProduct() = 0;
    virtual ~AbstractFactory()               = default;
};

template <typename AbstractProduct, typename Product>
class Factory : AbstractFactory<AbstractProduct> {
public:
    AbstractProduct* CreateProduct() override {
        return static_cast<AbstractProduct*>(new Product());
    }
};

int main() {
    Factory<Shoe, Nike> nikeFactory;
    auto res = nikeFactory.CreateProduct();
    res->show();
    return 0;
}