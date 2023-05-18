#include <iostream>
#include <memory>
#include <ostream>
#include <string>

class soldier {
public:
    virtual soldier* clone() const = 0;
    virtual std::string whoAmI() const = 0;
    virtual ~soldier(){}
};

class commodityAA: public soldier {
public:
    soldier* clone() const override {
        return new commodityAA(*this);
    }
    std::string whoAmI() const override {
        return "type is commodityAA";
    }

    commodityAA(const std::string& name): ptr_name(new std::string(name)) {}
    commodityAA(const commodityAA& other): ptr_name(new std::string(*other.ptr_name)) {}
    ~commodityAA() { if(ptr_name) delete ptr_name; }

private:
    std::string* ptr_name;
};

class commodityBB: public soldier {
public:
    soldier* clone() const override {
        return new commodityBB(*this);
    }
    std::string whoAmI() const override {
        return "type is commdityBB";
    }

    commodityBB(const std::string& name): ptr_name(new std::string(name)) {}
    commodityBB(const commodityBB& other): ptr_name(new std::string(*other.ptr_name)) {}
    ~commodityBB() { if(ptr_name) delete ptr_name; }
private:
    std::string* ptr_name;
};

int main() {
    auto cA = std::make_unique<commodityAA>("abcd");
    auto b = cA->clone();
    
    std::cout << cA->whoAmI() << std::endl;
    std::cout << b->whoAmI() << std::endl;

    soldier* s = new commodityBB("hhhh");
    std::cout << s->whoAmI() << std::endl;

    auto p = s->clone();
    std::cout << p->whoAmI() << std::endl;
    
    delete b;
    delete s;
    delete p;
}
