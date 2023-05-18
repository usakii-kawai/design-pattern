#include <atomic>
#include <fstream>
#include <iostream>
#include <iterator>
#include <mutex>
#include <thread>
#include <vector>

// std::mutex mtx;

class singletion {
singletion(singletion&) = delete;
singletion& operator=(const singletion&) = delete;
private:
    singletion(const std::string& value): str(value) {
        //  test
            std::cout << "create object" << std::endl;
        // 
    }
public:
    static std::atomic<int> count;
    static singletion& GetInstance(const std::string& value) {
        static singletion sg(value);
        // std::lock_guard<std::mutex> lg(mtx);
        // std::cout << "count value is: " << ++count << std::endl;
        return sg;
    }
private:
    std::string str;
};
// std::atomic<int> singletion::count = 0;

bool hungerInit() {
    // 1 init
    auto& temp = singletion::GetInstance("abc");
    // 2 init
    // 3 init
    // std::cout << "hunger" << std::endl;
    return true;
}

static bool hunger = hungerInit();

int main() {
    // std::cout << "get in main func" << std::endl;
    const std::string s = "abc";
    auto func = [&s](){ auto& sg = singletion::GetInstance(s);};
    std::vector<std::thread> vt;
    vt.reserve(10000);
    while(vt.size() != vt.capacity()) {
        vt.emplace_back(std::thread(func));
    }
    for(auto& t: vt) {
        t.join();
    }
}

