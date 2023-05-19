#include <initializer_list>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>

struct sharedState {
    std::string brand_;
    std::string model_;
    std::string color_;

    sharedState(const std::string& b, const std::string& m, const std::string& c)
    :brand_(b), model_(m), color_(c) {}

    friend std::ostream& operator<<(std::ostream& os, const sharedState& ss) {
        return os << "[ " << ss.brand_ << " , " << ss.model_ << " , " << ss.color_ << " ]";
    }
};

struct uniqueState {
    std::string owner_;
    std::string plate_;

    uniqueState(const std::string& o, const std::string& p): owner_(o), plate_(p) {}
    friend std::ostream& operator<<(std::ostream& os, const uniqueState& us) {
        return os << "[ " << us.owner_ << " , " << us.plate_ << " ]";
    }
};

class flyweight {
private:
    sharedState* shared_;
public:
    flyweight(const sharedState* ss): shared_(new sharedState(*ss)){}
    flyweight(const flyweight& other): shared_(new sharedState(*other.shared_)){}
    ~flyweight(){ if(shared_) delete shared_; }
    
    sharedState* share_state() const { return shared_; }
    void operation(const uniqueState& us) const {
        std::cout << "flyweight's:: shared: " << *shared_ << ", unique: " << us << std::endl;
    }
};

class flyweightFactory {
private:
    std::unordered_map<std::string, flyweight> flyweights_;
    std::string getKey(const sharedState& ss) const {
        return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
    }
public:
    flyweightFactory(std::initializer_list<sharedState>&& ss) {
        for(const auto& v: ss) {
            this->flyweights_.insert(
                std::make_pair<std::string, flyweight>(this->getKey(v), flyweight(&v))
            );
        }
    }

    flyweight getFlyweight(const sharedState& ss) {
        std::string key = this->getKey(ss);
        if(this->flyweights_.find(key) == this->flyweights_.end()) {
            std::cout << "flyweight: can't find..." << std::endl;
            this->flyweights_.insert(std::make_pair(key, flyweight(&ss)));
        } else {
            std::cout << "flyweightFactory: reusing existing flyweight.\n" << std::endl;
        }
        return this->flyweights_.at(key);
    }

    void listFlyweight() const {
        auto count = this->flyweights_.size();
        std::cout << "flyweigths have " << count << " flyweights..." << std::endl;
        for(const auto& p: this->flyweights_) {
            std::cout << p.first << std::endl;
        }
    }
};

void addCarToPoliceDatabase (
    flyweightFactory& ff, const std::string& plates, const std::string& owner,
    const std::string& brand, const std::string& model, const std::string& color
) {
    std::cout << "client: adding a car to database" << std::endl;
    const flyweight& f = ff.getFlyweight({brand, model, color});
    f.operation({owner, plates});
}

template<typename T>
std:: initializer_list<T> make_init_list ( std:: initializer_list<T> && l ) {
    return l;
}

int main() {
    auto ff = flyweightFactory(  
    {
            {"Chevrolet", "Camaro2018", "pink"},
            {"Mercedes Benz", "C300", "black"}, 
            {"Mercedes Benz", "C500", "red"}, 
            {"BMW", "M5", "red"},
            {"BMW", "X6", "white"}
        }
    );
    ff.listFlyweight();

    addCarToPoliceDatabase(
        ff,
        "CL234IR",
        "James Doe",
        "BMW",
        "M5",
        "red"
    );

    addCarToPoliceDatabase(
        ff,
        "CL234IR",
        "James Doe",
        "BMW",
        "X1",
        "red"
    );

    ff.listFlyweight();

    return 0;
}