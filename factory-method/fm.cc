//go:build ignore
#include <iostream>
#include <memory>

class product {
public:
    // virtual void setInterface() const = 0;
    virtual ~product(){}
    virtual void run() const = 0;
};

class productA: public product {
public:
    void run() const { std::cout << "run by productA" << std::endl; }
    ~productA() { std::cout << "delete productA" << std::endl; }
};

class productB: public product {
public:
    void run() const { std::cout << "run by productB" << std::endl; }
    ~productB() { std::cout << "delete productB" << std::endl; }
};

class factory {
public:
    ~factory() { 
        // std::cout << "delete factory, in and by " + this->name << std::endl; 
    } 
    virtual std::shared_ptr<product> createProduct() const = 0;
protected:
    // virtual void setname() = 0;
    std::string name;
};

class creatorA: public factory {
public:
    // creatorA() { setname(); }
    ~creatorA() { std::cout << "delete creatorA" << std::endl; } 
    std::shared_ptr<product> createProduct() const override { 
        return std::make_shared<productA>();
    }
private:
    // void setname() override { factory::name = "creatorA"; }
};

class creatorB: public factory {
public:
    // creatorB() { setname(); }
    ~creatorB() { std::cout << "delete creatorB" << std::endl; } 
    std::shared_ptr<product> createProduct() const override {
        return std::make_shared<productB>();
    }
private:
    // void setname() override { factory::name = "creatorB"; }
};

int main() {
    auto fa = std::make_unique<creatorA>();
    auto a = fa->createProduct();
    a->run();
    auto fb = std::make_unique<creatorB>();
    auto b = fb->createProduct();
    b->run();
}