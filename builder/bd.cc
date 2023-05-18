#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <map>

class Ship {
public:
    virtual ~Ship(){}
    virtual void showParts() = 0;
};

class SunnyShip: public Ship {
public:
    void addPart(std::string name) { m_parts.push_back(name); }
    void showParts() override {
        for(auto& v: m_parts) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
private:
    std::vector<std::string> m_parts;
};

class MerryShip: public Ship {
public:
    void assemble(std::string name, std::string parts) { m_parts.insert(std::make_pair(name, parts)); }
    void showParts() override {
        for(auto& v: m_parts) {
            std::cout << v.first << ": " << v.second << " ";
        }
        std::cout << std::endl;
    }
private:
    std::map<std::string, std::string> m_parts;
};

class ShipBuilder {
public:
    virtual void reset() = 0;
    virtual Ship* getShip() = 0;
    virtual void buildBody() = 0;
    virtual void buildWeapon() = 0;
    virtual void buildEngine() = 0;
    virtual ~ShipBuilder(){}
};

class SunnyBuilder: public ShipBuilder {
SunnyBuilder(const SunnyBuilder&) = delete;
SunnyBuilder& operator=(const SunnyBuilder) = delete;
public:
    SunnyBuilder() { reset(); }
    ~SunnyBuilder() { if(m_sunny) delete m_sunny; }
    void reset() override { 
        if(m_sunny) { delete m_sunny; }
        m_sunny = new SunnyShip; 
    }
    void buildBody() override { m_sunny->addPart("body"); }
    void buildWeapon() override { m_sunny->addPart("weapon"); }
    void buildEngine() override { m_sunny->addPart("engine"); }

    Ship* getShip() override {
        SunnyShip* ship = m_sunny;
        m_sunny = nullptr;
        return ship;
    }
private:
    SunnyShip* m_sunny = nullptr;
};

class MerryBuilder: public ShipBuilder {
MerryBuilder(const MerryBuilder&) = delete;
MerryBuilder& operator=(const MerryBuilder&) = delete;
public:
    MerryBuilder() { reset(); }
    ~MerryBuilder() { if(m_merry) delete m_merry; }
    void reset() override { 
        if(m_merry) { delete m_merry; }
        m_merry = new MerryShip; 
    }
    void buildBody() override { m_merry->assemble("body", "body of merry"); }
    void buildWeapon() override { m_merry->assemble("weapon", "weapon of merry"); }
    void buildEngine() override { m_merry->assemble("engine", "engine of merry"); }

    Ship* getShip() override {
        MerryShip* ship = m_merry;
        m_merry = nullptr;
        return ship;
    }

private:
    MerryShip* m_merry = nullptr;
};

class Director {
public:
    void setBuilder(ShipBuilder* builder) { 
        if(m_builder) {
            delete m_builder;
        }
        m_builder = builder; 
    }
    void buildSimpleShip() {
        m_builder->buildBody();
        m_builder->buildEngine();
    }
    void buildRegalShip() {
        buildSimpleShip();
        m_builder->buildWeapon();
    }
    ~Director() {
        if(m_builder) {
            delete m_builder;
        }
    }
private:
    ShipBuilder* m_builder = nullptr;
};

int main() {
    std::unique_ptr<Director> d = std::make_unique<Director>();

    MerryBuilder* mb = new MerryBuilder;
    d->setBuilder(mb);
    d->buildSimpleShip();
    auto p1 = mb->getShip();
    p1->showParts();

    SunnyBuilder* sb = new SunnyBuilder;
    d->setBuilder(sb);
    d->buildRegalShip();
    auto p2 =sb->getShip();
    p2->showParts();
    sb->reset();
    d->buildSimpleShip();
    
    delete p1;
    delete p2;
}