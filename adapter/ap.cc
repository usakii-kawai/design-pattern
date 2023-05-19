#include <algorithm>
#include <iostream>

class Target {
public:
    virtual ~Target(){}
    virtual std::string request() const { return "Target: The default target's behavior."; }
};

class Adaptee {
public:
    std::string specificRequest() const { return ".eetpadA eht fo roivaheb laicepS"; }
};

/* class Adapter: public Target {
private:
    Adaptee* ap_;
public:
    Adapter(Adaptee* ap): ap_(ap) {}
    std::string request() const override {
        std::string reStr = this->ap_->specificRequest();
        std::reverse(reStr.begin(), reStr.end());
        return "after:(TRANSLATED) " + reStr;
    }
}; */

class Adapter: public Target, public Adaptee {
public:
    Adapter(){}
    std::string request() const override {
        std::string reStr = specificRequest();
        std::reverse(reStr.begin(), reStr.end());
        return "after:(TRANSLATED) " + reStr;
    }

};

int main() {
    Target* t = new Target;
    std::cout << t->request() << std::endl;

    Adaptee* ad = new Adaptee;
    std::cout << ad->specificRequest() << std::endl;

    // Adapter* ap = new Adapter(ad);
    Adapter* ap =new Adapter;
    std::cout << ap->request() << std::endl;

    delete t;
    delete ad;
    delete ap;
}