#include <iostream>
#include <string>

class baseComponent;
class mediator{
public:
    virtual void notify(baseComponent* sender, std::string event) const = 0;
    virtual ~mediator(){}
};

class baseComponent {
protected:
    mediator* my_md_;
public:
    baseComponent(mediator* m = nullptr): my_md_(m){}
    void set_mediator(mediator* m) {
        if (my_md_) { delete my_md_; }
        my_md_ = m;
    }
    virtual ~baseComponent(){}
};

class ComponentA: public baseComponent {
public:
    void DoA() {
        std::cout << "ComponentA" << std::endl;
        this->my_md_->notify(this, "A");
    }
    void DoB() {
        std::cout << "ComponentB" << std::endl;
        this->my_md_->notify(this, "B");
    }
};

class ComponentB: public baseComponent {
public:
    void DoC() {
        std::cout << "ComponentC" << std::endl;
        this->my_md_->notify(this, "C");
    }
    void DoD() {
        std::cout << "ComponentD" << std::endl;
        this->my_md_->notify(this, "D");
    }
};

class ConcreteMediator: public mediator {
private:
    ComponentA* ca_;
    ComponentB* cb_;
public:
    ConcreteMediator(ComponentA* ca, ComponentB* cb): ca_(ca), cb_(cb){
        this->ca_->set_mediator(this);
        this->cb_->set_mediator(this);
    }
    void notify(baseComponent* sender, std::string event) const override {
        /* 
            catch "A" "D"
        */
        if(event == "A") {
            ca_->DoB();
        } else if (event == "D") {
            ca_->DoA();
            ca_->DoB();
            cb_->DoC();
            // cb_->DoD(); // loop
        }
    }
};

int main() {
    ComponentA* ca = new ComponentA;
    ComponentB* cb = new ComponentB;
    ConcreteMediator* m = new ConcreteMediator(ca, cb);

    ca->DoA();
    cb->DoD();

    delete ca;
    delete cb;
    delete m;
}