#include <iostream>

class subSystem1 {
public:
    std::string operation1() const { return "subSystem1: Ready!\n"; }
    std::string operationN() const { return "subSystem1: GO!\n"; }
};

class subSystem2 {
public:
    std::string operation1() const { return "subSystem1: Get ready!\n"; }
    std::string operationZ() const { return "subSystem2: Fly!\n"; }
};

class Facade {
protected:
    subSystem1* s1_;
    subSystem2* s2_;
public:
    ~Facade() { if(s1_) delete s1_; if(s2_) delete s2_; }
    Facade(subSystem1* s1 = nullptr, subSystem2* s2 = nullptr) {
        s1_ = s1 ?: new subSystem1;
        s2_ = s2 ?: new subSystem2;
    }
    std::string operation() {
        std::string result = "facade initializes subsystems: \n";
        result += this->s1_->operation1();
        result += this->s2_->operation1();
        result += "---------------\n";
        result += this->s1_->operationN();
        result += this->s2_->operationZ();
        return result;
    }
};

void test(Facade* f) {
    std::cout << f->operation();
}

int main() {
    auto s1 = new subSystem1;
    auto s2 = new subSystem2;
    Facade* f = new Facade(s1, s2);
    test(f);
    delete(f);
}