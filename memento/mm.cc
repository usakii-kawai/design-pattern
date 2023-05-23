#include <iostream>
#include <vector>
#include <ctime>

class memento {
public:
    virtual ~memento(){}
    virtual std::string GetName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
};

class concreteMemento: public memento {
private:
    std::string state_;
    std::string date_;
public:
    concreteMemento(std::string state): state_(state){
        this->state_ = state;
        std::time_t now_ = std::time(0);
        this->date_ = std::ctime(&now_);
    }

    std::string state() const override { return this->state_; }
    std::string GetName() const override {
        return this->date_ + "/(" + this->state_.substr(0,9) + "...)";
    }
    std::string date() const override { return this->date_; }
};

class originator {
private:
    std::string state_;
public:
    std::string GenerateRandomString(int length = 10) {
        const char alphaNum[] = 
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcedfghijklmnopqrstuvwxyz";
        int strLen = sizeof alphaNum - 1;
        
        std::string random_string;
        for(int i = 0; i != length; i++) {
            random_string += alphaNum[std::rand() % strLen];
        }
        return random_string;
    }
    originator(std::string state): state_(state) {
        std::cout << "originator: my initial state is: " << this->state_ << std::endl;
    }

    void doSomething()  {
        std::cout << "originator: i'm doing something important." << std::endl;
        this->state_ = this->GenerateRandomString(30);
        std::cout << "originator: and my state has changed to: " << this->state_ << std::endl;
    }

    memento* save() {
        return new concreteMemento(this->state_);
    }

    void restore(memento* m) {
        this->state_ = m->state();
        std::cout << "originator: my state has changed to: " << this->state_ << std::endl;
    }
};


class caretaker {
private:
    std::vector<memento*> vms_;
    originator* og_;
public:
    caretaker(originator* o): og_(o) {}
    ~caretaker() {
        for(auto m: vms_) delete m;
    }
    void backup() {
        std::cout << "\ncaretaker: saving originator's state..." << std::endl;
        this->vms_.push_back(this->og_->save());
    }
    void undo() {
        if(!this->vms_.size()) return;
        auto m = this->vms_.back();
        std::cout << "caretaker: restoring state to: " << m->GetName() << std::endl;
        try {
            this->og_->restore(m);
        } catch(...) {
            this->undo();
        }
    }
    void showHistory() const {
        std::cout << "caretaker: here's the list of mementos:" << std::endl;
        for(auto m: this->vms_) {
            std::cout << m->GetName() << std::endl;
        }
    }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    originator* ori = new  originator("Super-duper-super-puper-super.");
    caretaker* car = new caretaker(ori);
    car->backup();
    ori->doSomething();
    car->backup();
    ori->doSomething();
    car->backup();
    ori->doSomething();
    std::cout << "\n";
    car->showHistory();
    std::cout << "\nClient: Now, let's rollback!\n\n";
    car->undo();
    std::cout << "\nClient: Once more!\n\n";
    car->undo();

    delete ori;
    delete car;
}