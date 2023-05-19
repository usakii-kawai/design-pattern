#include <iostream>
#include <list>
#include <memory>
#include <string>

class component {
protected:
    component* parent_;
public:
    virtual ~component(){}
    void setParent(component* p) { parent_ = p; }
    component* getParent() const { return parent_; }
    virtual void add(component* p) {}
    virtual void remove(component* p) {}
    virtual bool isComposite() const { return false; }
    virtual std::string operation() const = 0;
};

class leaf: public component {
public:
    std::string operation() const override { return "leaf"; }
};

class composite: public component {
protected:
    std::list<component*> children_;
public:
    void add(component* p) override {
        this->children_.push_back(p);
        p->setParent(this);
    }
    void remove(component* p) override {
        this->children_.remove(p);
        p->setParent(nullptr);
    }
    bool isComposite() const override {
       return true;
    }
    std::string operation() const override {
        std::string result;
        for(const component* c: children_) {
            if(c == children_.back()) {
                result += c->operation();
            } else {
                result += c->operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
    ~composite() {
        while(true) {
            if(children_.begin() != children_.end()) {
                delete children_.back();
                children_.pop_back();
            } else {
                break;
            }
        }
    }
};

void test(component* c) {
    std::cout << "RESULT: " << c->operation() << std::endl;
}

int main() {
    auto simple = new leaf;
    std::cout << "Client: I've got a simple component:\n";
    test(simple);
    std::cout << "\n\n";
    delete simple;

    std::unique_ptr<composite> tree = std::make_unique<composite>();
    auto branch1 = new composite;
    auto branch2 = new composite;

    auto leaf1 = new leaf;
    auto leaf2 = new leaf;
    auto leaf3 = new leaf;

    tree->add(branch1);
    tree->add(branch2);

    branch1->add(leaf1);
    branch1->add(leaf2);
    branch2->add(leaf3);

    test(tree.get());
    test(branch1);
    test(branch2);

}
