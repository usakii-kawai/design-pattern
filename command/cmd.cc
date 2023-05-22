#include <iostream>
#include <string>

class Command {
public:
    virtual ~Command(){}
    virtual void Execute() const = 0;
};

class SimpleCommand: public Command {
private:
    std::string pay_load_;
public:
    explicit SimpleCommand(const std::string& msg): pay_load_(msg){}
    void Execute() const override {
        std::cout << "in simple_command: " << pay_load_ << std::endl;
    }
};

class Other {
public:
    std::string work_featureA(const std::string& a) {
        return "work featureA: " + a;
    }
    std::string work_featureB(const std::string& b) {
        return "work featureA: " + b;
    }
};

class ComplexCommand: public Command {
private:
    Other* my_other;
    std::string stra;
    std::string strb;
public:
    ComplexCommand(Other* o, const std::string& a, const std::string& b ): my_other(o), stra(a), strb(b){}
    void Execute() const override {
        std::cout << "in complex command: " << my_other->work_featureA(stra) << " : " << my_other->work_featureB(strb) << std::endl;
    }
    ~ComplexCommand() {
        if(my_other) delete my_other;
    }
};

int main() {
    Command* sc = new SimpleCommand ("hello");
    Command* cc= new ComplexCommand(new Other, "kunkun", "chicken");
    sc->Execute();
    cc->Execute();
    delete sc;
    delete cc;
}