#include <iostream>
#include <ostream>
#include <string>

class Implementation {
public:
    virtual ~Implementation(){}
    virtual std::string OperatorImplementation() const = 0;
};

class ImplementationA: public Implementation {
public:
    std::string OperatorImplementation() const override {
        return "result on the platform A";
    }
};

class ImplementationB: public Implementation {
public:
    std::string OperatorImplementation() const override {
        return "result on the platform B";
    }
};

class Abstraction {
protected:
    Implementation* im_;
public:
    Abstraction(Implementation* im): im_(im) {}
    virtual ~Abstraction() {}
    virtual std::string Operation() const {
        return "Abstraction: " + this->im_->OperatorImplementation();
    }
};

class ExtendedAbstraction: public Abstraction {
public:
    ExtendedAbstraction(Implementation* im): Abstraction(im) {}
    std::string Operation() const override {
        return "Extended: " + this->im_->OperatorImplementation();
    }
};

void ClientCode(const Abstraction& ab) {
    std::cout << ab.Operation() << std::endl;
}

int main() {
    Implementation* im = new ImplementationA();
    Abstraction* ab = new Abstraction(im);
    ClientCode(*ab);
    delete im;
    delete ab;

    im = new ImplementationB();
    ab = new ExtendedAbstraction(im);
    ClientCode(*ab);
    delete im;
    delete ab;
}