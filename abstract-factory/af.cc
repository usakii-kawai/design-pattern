//go:build ignore
#include <iostream>
#include <memory>
#include <string>

class AbstractProductA {
public:
    virtual ~AbstractProductA(){}
    virtual std::string UsefulFunctionA() const = 0;
};
class AbstractProductB {
public:
    virtual ~AbstractProductB(){}
    virtual std::string UsefulFunctionB() const = 0;
};

class ProductA1: public AbstractProductA {
public:
    std::string UsefulFunctionA() const override {
        return "run by product A1";
    }
};
class ProductA2: public AbstractProductA {
public: 
    std::string UsefulFunctionA() const override {
        return "run by product A2";
    }
};

class ProductB1: public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "work by product B1";
    }
};

class ProductB2: public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "work by product B2";
    }
};

class AbstractFactory {
public:
    virtual AbstractProductA* createProductA() const = 0;
    virtual AbstractProductB* createProductB() const = 0;
};

class FactoryFeature1: public AbstractFactory {
public:
    AbstractProductA* createProductA() const override {
        return new ProductA1();
    }
    AbstractProductB* createProductB() const override {
        return new ProductB1();
    }
};

class FactoryFeature2: public AbstractFactory {
public:
    AbstractProductA* createProductA() const override {
        return new ProductA2();
    }
    AbstractProductB* createProductB() const override {
        return new ProductB2();
    }
};

int main() {
    auto f1 = FactoryFeature1();
    auto f2 = FactoryFeature2();
    auto pa1 = f1.createProductA();
    auto pa2 = f2.createProductA();
    std::cout << pa1->UsefulFunctionA() << std::endl;
    std::cout << pa2->UsefulFunctionA() << std::endl;
    delete pa1;
    delete pa2;
}
