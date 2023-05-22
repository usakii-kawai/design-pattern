#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>

class AbstractHandler {
protected:
    bool check(const AbstractHandler* h) {
        if(h == nullptr) { return true; }
        return false;
    }
public:
    virtual AbstractHandler* SetNext(std::nullptr_t) = delete;
    virtual AbstractHandler* SetNext(AbstractHandler *handler) = 0;
    virtual AbstractHandler* GetNext() const = 0;
    virtual std::string Handle(const std::string& req) const = 0;
    virtual ~AbstractHandler(){}
};

class EmptyHandler: public AbstractHandler {
protected:
    AbstractHandler* next_;
    AbstractHandler* GetNext() const override {
        return this->next_;
    }
public:
    EmptyHandler(AbstractHandler* next = nullptr): next_(next){}
    AbstractHandler* SetNext(AbstractHandler* h) override {
        if(check(h)) {
            this->next_ = new EmptyHandler;
        } else {
            this->next_ = h;
        }
        return GetNext();
    }

    virtual std::string Handle(const std::string& req) const override {
        std::cout << "handle in empty node-> " ; 
        if(GetNext()) {
            return GetNext()->Handle(req);
        }
        
        return {};
    }
    virtual ~EmptyHandler() {
        if(next_) {
            delete next_;
        }
    }
};

class Handler: public AbstractHandler {
protected:
    AbstractHandler* next_;
    AbstractHandler* GetNext() const override {
        return this->next_;
    }
public:
    Handler(AbstractHandler* next = nullptr): next_(next){}
    AbstractHandler* SetNext(AbstractHandler* h) override {
        if(check(h)) {
            this->next_ = new EmptyHandler;
        } else {
            this->next_ = h;
        }
        return GetNext();
    }

    virtual std::string Handle(const std::string& req) const override {
        if(GetNext()) {
            return GetNext()->Handle(req);
        }
        
        return {};
    }
    virtual ~Handler() {
        if(next_) {
            delete next_;
        }
    }
};

class SinglerHandler: public Handler {
public:
    std::string Handle(const std::string& req) const override {
        std::cout << req;
        if(GetNext()) {
            std::cout << "-> ";
            return GetNext()->Handle(req);
        }
        return "end by singler";
    }
};

class DancerHandler: public Handler {
public:
    std::string Handle(const std::string& req) const override {
        std::cout << req;
        if(GetNext()) {
            std::cout << "-> ";
            return GetNext()->Handle(req);
        }
        return "end by dancer";
    }
};

class RapperHandler: public Handler {
public:
    std::string Handle(const std::string& req) const override {
        std::cout << req;
        if(GetNext()) {
            std::cout << "->";
            return GetNext()->Handle(req);
        }
        return "end by rapper";
    }
};

int main() {
    std::string s = "唱跳rap";


    AbstractHandler* p = new Handler;
    AbstractHandler* ps = new SinglerHandler;
    AbstractHandler* pd = new DancerHandler;
    AbstractHandler* pr = new RapperHandler;

    p->SetNext(ps)->SetNext((AbstractHandler*)nullptr)->SetNext(pr);
    auto end = p->Handle(s);
    std::cout << "\n" + end << std::endl;

    // AbstractHandler* p2 = nullptr;
    // p2->Handle(s);

    delete p;
    delete pd;
}