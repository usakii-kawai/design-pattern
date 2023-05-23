#include <iostream>
#include <typeinfo>

class context;
class state {
protected:
    context* con;
public:
    virtual ~state(){}
    void set_context(context* c) { con = c; }
    virtual void handle1() = 0;
    virtual void handle2() = 0;
};

class context {
private:
    state* st;
public:
    context(state* s): st(nullptr) {
        this->transitionTo(s);
    }
    ~context() {
        if(st) delete st;
    }
    void transitionTo(state* s) {
        std::cout << "context: Transition to " << typeid(*s).name() << std::endl;
        if(this->st != nullptr) {
            delete st;
        }
        this->st = s;
        this->st->set_context(this);
    }
    void request1() { this->st->handle1(); }
    void request2() { this->st->handle2(); }
};

class stateA: public state {
public:
    void handle1() override;
    void handle2() override {
        std::cout << "stateA handles request2" << std::endl;
    }
};

class stateB: public state {
public:
    void handle1() override {
        std::cout << "stateb handles request1" << std::endl;
    }
    void handle2() override {
        std::cout << "stateb handles request2, and tran to stateA" << std::endl;
        this->con->transitionTo(new stateA);
    }
};

void stateA::handle1() {
    std::cout << "stateA handles request1, and tran to stateB" << std::endl;
    this->con->transitionTo(new stateB);
}

int main() {
    auto c = new context(new stateA);
    c->request2();
    c->request1();
    c->request1();
    c->request2();

    delete c;
}