// C++ OOP Cheatsheet

#include <iostream>
#include <string>

// 1. CLASSES AND OBJECTS
class Car {
public:
    std::string brand;
    int speed;

    // Constructor
    Car(std::string b, int s) : brand(b), speed(s) {}

    // Method
    void displayInfo() {
        std::cout << "Brand: " << brand << ", Speed: " << speed << " km/h" << std::endl;
    }
};

int main() {
    Car car1("Toyota", 180);  // Create an object of Car
    car1.displayInfo();  // Call method

    return 0;
}

// 2. ENCAPSULATION (Private Members and Getter/Setter)
class Employee {
private:
    int salary;  // Private member

public:
    // Constructor
    Employee(int sal) : salary(sal) {}

    // Getter (public method to access private member)
    int getSalary() {
        return salary;
    }

    // Setter (public method to modify private member)
    void setSalary(int sal) {
        if (sal > 0)
            salary = sal;
        else
            std::cout << "Invalid salary!" << std::endl;
    }
};

int main() {
    Employee emp1(50000);
    std::cout << "Initial salary: " << emp1.getSalary() << std::endl;
    
    emp1.setSalary(60000);  // Modify private member via setter
    std::cout << "Updated salary: " << emp1.getSalary() << std::endl;

    return 0;
}

// 3. INHERITANCE
class Animal {
public:
    void sound() {
        std::cout << "This is an animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void bark() {
        std::cout << "The dog barks!" << std::endl;
    }
};

int main() {
    Dog dog1;
    dog1.sound();  // Inherited method
    dog1.bark();   // Child class method

    return 0;
}

// 4. POLYMORPHISM (Compile-time and Run-time)

// Compile-time (Function Overloading)
class MathOperation {
public:
    int add(int a, int b) {
        return a + b;
    }

    // Overloaded method with different parameters
    int add(int a, int b, int c) {
        return a + b + c;
    }
};

int main() {
    MathOperation mathOp;
    std::cout << "Sum of 2 numbers: " << mathOp.add(10, 20) << std::endl;
    std::cout << "Sum of 3 numbers: " << mathOp.add(10, 20, 30) << std::endl;

    return 0;
}

// Run-time Polymorphism (Using `virtual` functions and inheritance)
class Shape {
public:
    virtual void draw() {
        std::cout << "Drawing a generic shape" << std::endl;
    }
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a square" << std::endl;
    }
};

int main() {
    Shape* shape;
    Circle circle;
    Square square;

    shape = &circle;
    shape->draw();  // Will call Circle's draw()

    shape = &square;
    shape->draw();  // Will call Square's draw()

    return 0;
}

// 5. ABSTRACTION (Using Abstract Class and Pure Virtual Function)
class AbstractDevice {
public:
    virtual void turnOn() = 0;  // Pure virtual function (must be overridden)
};

class Smartphone : public AbstractDevice {
public:
    void turnOn() override {
        std::cout << "Turning on the smartphone" << std::endl;
    }
};

class Laptop : public AbstractDevice {
public:
    void turnOn() override {
        std::cout << "Turning on the laptop" << std::endl;
    }
};

int main() {
    Smartphone phone;
    Laptop laptop;

    phone.turnOn();
    laptop.turnOn();

    return 0;
}

// 6. DESTRUCTORS (For Cleaning Up)
class Resource {
public:
    Resource() {
        std::cout << "Resource acquired!" << std::endl;
    }

    ~Resource() {
        std::cout << "Resource released!" << std::endl;
    }
};

int main() {
    {
        Resource res1;  // Automatically calls destructor when it goes out of scope
    }  // Destructor called here

    return 0;
}

// 7. FRIEND FUNCTION (Accessing Private Members)
class Box {
private:
    int width;

public:
    Box(int w) : width(w) {}

    // Friend function
    friend int getWidth(Box& b);
};

int getWidth(Box& b) {
    // Accessing private member of class Box
    return b.width;
}

int main() {
    Box box1(10);
    std::cout << "Width of box: " << getWidth(box1) << std::endl;

    return 0;
}

// 8. COPY CONSTRUCTOR (For Copying Objects)
class CopyDemo {
public:
    int value;

    CopyDemo(int v) : value(v) {}

    // Copy constructor
    CopyDemo(const CopyDemo& obj) {
        value = obj.value;
    }
};

int main() {
    CopyDemo obj1(100);      // Normal constructor
    CopyDemo obj2 = obj1;    // Copy constructor called

    std::cout << "Original object value: " << obj1.value << std::endl;
    std::cout << "Copied object value: " << obj2.value << std::endl;

    return 0;
}
