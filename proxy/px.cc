#include <iostream>
#include <string>

class subject {
public: virtual void request() const = 0;
};

class realSubject: public subject {
public: 
    void request() const override {
        std::cout << "realSubject: Handling request" << std::endl;
    }
};

class proxy: public subject {
private:
    realSubject* rs_;
    bool checkAccess() const {
        std::cout << "proxy: check access prior to firing a real request" << std::endl;
        return true;
    }
    void logAccess() const {
        std::cout << "proxy: logging the time of request" << std::endl;
    }
public:
    proxy(realSubject* rs): rs_(new realSubject(*rs)) {}
    ~proxy() { if(rs_) delete rs_; }
    void request() const override {
        if(this->checkAccess()) {
            this->rs_->request();
            this->logAccess();
        }
    }
};

void test(const subject& sj) {
    sj.request();
}

int main() {
    std::cout << "Client: Executing the client code with a real subject." << std::endl;
    realSubject* rs = new realSubject;
    test(*rs);

    std::cout << "Client: Executing the same client code with a proxy." << std::endl;
    proxy* px = new proxy(rs);
    test(*px);

    delete rs;
    delete px; 

    return 0;
}
