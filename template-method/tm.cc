#include <iostream>

class abstractClass {
public:
    virtual ~abstractClass() = default;
    void TemplateMethod() const {
        this->BaseOperation1();
        this->RequiredOperation1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }
protected:
    void BaseOperation1() const {
        std::cout << "BaseOperation1" << std::endl;
    }
    void BaseOperation2() const {
        std::cout << "BaseOperation2" << std::endl;
    }
    void BaseOperation3() const {
        std::cout << "BaseOperation3" << std::endl;
    }
    virtual void RequiredOperation1() const = 0;
    virtual void RequiredOperation2() const = 0;
    virtual void Hook1() const {}
    virtual void Hook2() const {}
};

class concreteClass1: public abstractClass {
protected:
    void RequiredOperation1() const override {
        std::cout << "RequiredOperation1 implement by class1" << std::endl;
    }
    void RequiredOperation2() const override {
        std::cout << "RequiredOperation2 implement by class1" << std::endl;
    }
};

class concreteClass2: public abstractClass {
protected:
    void RequiredOperation1() const override {
        std::cout << "RequiredOperation1 implement by class2" << std::endl;
    }
    void RequiredOperation2() const override {
        std::cout << "RequiredOperation2 implement by class2" << std::endl;
    }
    void Hook1() const override {
        std::cout << "Hook1 by class2" << std::endl;
    }
};

int main() {
    abstractClass* cc1 = new concreteClass1;
    cc1->TemplateMethod();

    abstractClass* cc2 = new concreteClass2;
    cc2->TemplateMethod();

    delete cc1;
    delete cc2;
}