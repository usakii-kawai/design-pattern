#include <iostream>
#include <list>
#include <string>

class IObserver {
public:
    virtual ~IObserver(){}
    virtual void update(const std::string& msg_from_sub) = 0;
};

class ISubject {
public:
    virtual ~ISubject(){}
    virtual void attach(IObserver* o) = 0;
    virtual void detach(IObserver* o) = 0;
    virtual void notify() = 0;
};

class Subject: public ISubject {
public:
    virtual ~Subject() { std::cout << "~Subject" << std::endl; }
    void attach(IObserver* o) override { list_observer_.push_back(o); }
    void detach(IObserver* o) override { list_observer_.remove(o); }
    void notify() override {
        auto it = list_observer_.begin();
        HowManyObserver();
        while(it != list_observer_.end()) {
            (*it)->update(message_);
            ++it;
        }
    }
    void createMsg(const std::string& msg = "empty") {
        this->message_ = msg;
        notify();
    }
    void HowManyObserver() {
        std::cout << "how may observer ? " << this->list_observer_.size() << std::endl;
    }
    void buniess() {
        this->message_ = "another message";
        notify();
    }
    private:
        std::list<IObserver*> list_observer_;
        std::string message_;
};

class Observer: public IObserver {
public:
    Observer(Subject& s): s_(s) {
        this->s_.attach(this);
        ++Observer::static_num_;
        this->num_ = Observer::static_num_;
    }
    ~Observer() {
        std::cout << R"(~Observer \)" << this->num_ << std::endl;
    }
    void update(const std::string& msg_from_subject) override {
        msg_from_subject_ = msg_from_subject;
        PrintInfo();
    }
    void removeSelfFromSub() {
        s_.detach(this);
        std::cout << "remove" << std::endl;
    }
    void PrintInfo() {
        std::cout << this->num_ << "---" << this->msg_from_subject_ << std::endl;
    }

private:
    std::string msg_from_subject_;
    Subject& s_;
    static int static_num_;
    int num_;
};
int Observer::static_num_ = 0;

int main() {
    Subject* s = new Subject;
    Observer* o1 = new Observer(*s);
    Observer* o2 = new Observer(*s);
    Observer* o3 = new Observer(*s);

    s->createMsg("hello");
    o3->removeSelfFromSub();

    s->createMsg("hello now");

    delete s;
    delete o1;
    delete o2;
    delete o3;
}