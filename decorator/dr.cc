#include <iostream>

class component {
public:
    virtual ~component(){}
    virtual std::string operation() const = 0;
};

class concreteComponent: public component {
public:
    std::string operation() const override {
        return "concreteComponent";
    };
};

class decorator: public component {
protected:
    component* c_;
public:
    decorator(component* c): c_(c) {}
    std::string operation() const override { return this->c_->operation(); }
};

class concreteDecoratorA: public decorator {
public:
    concreteDecoratorA(component* c): decorator(c) {}
    std::string operation() const override {
        return "concreteDecoratorA(" + decorator::operation() + ")";
    }
};

class concreteDecoratorB: public decorator {
public:
    concreteDecoratorB(component* c): decorator(c) {}
    std::string operation() const override {
        return "concreteDecoratorB(" + decorator::operation() + ")"; 
    }
};

void test(component* c) {
    std::cout << "RESULT: " << c->operation() << std::endl;
}

int main() {
    auto simple = new concreteComponent;
    test(simple);

    auto decorator1 = new concreteDecoratorA(simple);
    auto decorator2 = new concreteDecoratorB(decorator1);
    test(decorator2);

    delete simple;
    delete decorator1;
    delete decorator2;
}