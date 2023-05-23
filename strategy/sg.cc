#include <algorithm>
#include <iostream>
#include <memory>

class strategy {
public:
    virtual ~strategy() = default;
    virtual std::string doWork(std::string) const = 0;
};

class context {
private:
    std::unique_ptr<strategy> us_;
public:
    explicit context(std::unique_ptr<strategy>&& s = {}): us_(std::move(s)){}
    void set_strategy(std::unique_ptr<strategy>&& s) { us_ = std::move(s); }
    void doContextWork() const {
        if(us_) {
            std::string result = us_->doWork("doContextWork");
            std::cout << result << std::endl;
        } else {
            std::cout << "context: strategy isn't set" << std::endl;
        }
    }
};

class strategyA: public strategy {
public:
    std::string doWork(std::string msg) const override {
        auto temp = msg;
        return std::string(msg.rbegin(), msg.rend());
    }
};

class strategtB: public strategy {
public:
    std::string doWork(std::string msg) const override {
        return msg + msg;
    }
};

int main() {
    context c(std::make_unique<strategyA>());
    c.doContextWork();
    c.set_strategy(std::make_unique<strategtB>());
    c.doContextWork();
}