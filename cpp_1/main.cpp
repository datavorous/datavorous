// C++ CHEATSHEET

#include <iostream>
#include <vector>
#include <map>
#include <memory>  // For smart pointers
#include <algorithm>
#include <functional> // For function/bind/lambda

// 1. BASICS
int main() {
    std::cout << "Hello, World!" << std::endl;  // Basic I/O

    // Variables
    int a = 10;
    double b = 20.5;
    char c = 'C';
    bool flag = true;
    
    // Control Structures
    if (a > 5) std::cout << "a is greater than 5" << std::endl;
    for (int i = 0; i < 5; ++i) std::cout << i << " ";
    std::cout << std::endl;

    // Arrays & Vectors
    std::vector<int> vec = {1, 2, 3};
    for (auto val : vec) std::cout << val << " ";
    std::cout << std::endl;

    // Functions
    auto sum = [](int x, int y) { return x + y; };
    std::cout << "Sum: " << sum(5, 10) << std::endl;

    return 0;
}

// 2. OBJECT-ORIENTED PROGRAMMING
class Animal {
protected:
    std::string name;
public:
    Animal(const std::string& name) : name(name) {}
    virtual void speak() const { std::cout << name << " makes a sound" << std::endl; }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}
    void speak() const override { std::cout << name << " barks" << std::endl; }
};

// 3. MEMORY MANAGEMENT
void smartPointerExample() {
    std::unique_ptr<Dog> dog = std::make_unique<Dog>("Buddy");
    dog->speak();  // Automatically deleted when out of scope
}

// 4. COMMON STL (Standard Template Library) CONTAINERS
void stlExample() {
    std::map<std::string, int> ageMap = {{"Alice", 30}, {"Bob", 25}};
    for (const auto& pair : ageMap) {
        std::cout << pair.first << " is " << pair.second << " years old" << std::endl;
    }
}

// 5. EXCEPTION HANDLING
void divide(int a, int b) {
    if (b == 0) throw std::invalid_argument("Division by zero");
    std::cout << "Result: " << a / b << std::endl;
}

void exceptionHandlingExample() {
    try {
        divide(10, 0);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// 6. DESIGN PATTERNS
// a) Singleton Pattern
class Singleton {
private:
    static Singleton* instance;
    Singleton() {}  // Private constructor
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};
Singleton* Singleton::instance = nullptr;

// b) Factory Pattern
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() {}
};

class ConcreteProductA : public Product {
public:
    void use() override { std::cout << "Using Product A" << std::endl; }
};

class Factory {
public:
    std::unique_ptr<Product> createProduct(const std::string& type) {
        if (type == "A") return std::make_unique<ConcreteProductA>();
        return nullptr;
    }
};

// c) Observer Pattern
class Observer {
public:
    virtual void update(int value) = 0;
};

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
    int value;
public:
    void addObserver(const std::shared_ptr<Observer>& obs) { observers.push_back(obs); }
    void notifyObservers() {
        for (const auto& obs : observers) {
            obs->update(value);
        }
    }
    void setValue(int newValue) {
        value = newValue;
        notifyObservers();
    }
};

class ConcreteObserver : public Observer {
public:
    void update(int value) override {
        std::cout << "Observer updated with value: " << value << std::endl;
    }
};

// d) Strategy Pattern
class Strategy {
public:
    virtual int execute(int a, int b) = 0;
};

class AddStrategy : public Strategy {
public:
    int execute(int a, int b) override {
        return a + b;
    }
};

class Context {
    std::unique_ptr<Strategy> strategy;
public:
    void setStrategy(std::unique_ptr<Strategy> strat) { strategy = std::move(strat); }
    int executeStrategy(int a, int b) {
        return strategy->execute(a, b);
    }
};

// 7. TEMPLATES (for generic programming)
template <typename T>
T add(T x, T y) {
    return x + y;
}

// 8. LAMBDA EXPRESSIONS
void lambdaExample() {
    auto multiply = [](int a, int b) { return a * b; };
    std::cout << "Multiply: " << multiply(5, 10) << std::endl;
}

// Main function to showcase usage of patterns
int main() {
    // OOP
    Animal* myDog = new Dog("Rex");
    myDog->speak();
    delete myDog;

    // Memory management
    smartPointerExample();

    // STL
    stlExample();

    // Exception handling
    exceptionHandlingExample();

    // Singleton
    Singleton* s = Singleton::getInstance();

    // Factory
    Factory factory;
    std::unique_ptr<Product> product = factory.createProduct("A");
    product->use();

    // Observer
    auto subject = std::make_shared<Subject>();
    auto observer1 = std::make_shared<ConcreteObserver>();
    subject->addObserver(observer1);
    subject->setValue(42);

    // Strategy
    Context context;
    context.setStrategy(std::make_unique<AddStrategy>());
    std::cout << "Strategy result: " << context.executeStrategy(3, 4) << std::endl;

    // Templates
    std::cout << "Template add: " << add<int>(5, 10) << std::endl;

    // Lambda
    lambdaExample();

    return 0;
}
