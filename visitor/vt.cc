#include <iostream>
#include <istream>
#include <string>

class componentA;
class componentB;

class visitor {
public:
    virtual ~visitor() = default;
    virtual void visitComponentA(const componentA* element) const = 0;
    virtual void visitComponentB(const componentB* element) const = 0;
};

class component {
public:
    virtual ~component() = default;
    virtual void accept(visitor* v) const = 0;
};

class componentA: public component {
public: 
    void accept(visitor* v) const override { v->visitComponentA(this); }
    std::string exeMethodComponentA() const { return "A"; }
};

class componentB: public component {
public:
    void accept(visitor* v) const override { v->visitComponentB(this); }
    std::string exeMethodComponentB() const { return "B"; }
};

class visitor1: public visitor {
public:
    void visitComponentA(const componentA* ca) const override {
        std::cout << "in v1 " << ca->exeMethodComponentA() << std::endl;
    }
    void visitComponentB(const componentB* cb) const override {
        std::cout << "in v1 " <<cb->exeMethodComponentB() << std::endl;
    }
};

class visitor2: public visitor {
public:
    void visitComponentA(const componentA* ca) const override {
        std::cout << "in v2 " << ca->exeMethodComponentA() << std::endl;
    }
    void visitComponentB(const componentB* cb) const override {
        std::cout << "in v2 "<< cb->exeMethodComponentB() << std::endl;
    }
};

int main() {
    visitor* v1 = new visitor1;
    visitor* v2 = new visitor2;

    componentA* ca = new componentA;
    componentB* cb = new componentB;

    v1->visitComponentA(ca);
    v1->visitComponentB(cb);
    v2->visitComponentA(ca);
    v2->visitComponentB(cb);


    delete v1;
    delete v2;
    delete ca;
    delete cb;
}