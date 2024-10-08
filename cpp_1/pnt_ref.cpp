// C++ Pointers and References Cheatsheet

#include <iostream>

// 1. BASICS OF POINTERS
int main() {
    int num = 42;     // A normal integer variable
    int* ptr = &num;  // Pointer to the address of num

    std::cout << "Value of num: " << num << std::endl;
    std::cout << "Address of num (&num): " << &num << std::endl;
    std::cout << "Pointer ptr (address of num): " << ptr << std::endl;
    std::cout << "Value pointed to by ptr (*ptr): " << *ptr << std::endl;

    *ptr = 100; // Modifying the value of num through the pointer
    std::cout << "Updated value of num: " << num << std::endl;

    return 0;
}

// 2. BASICS OF REFERENCES
void referenceDemo() {
    int x = 10;
    int& ref = x;   // Reference to x

    std::cout << "Original value of x: " << x << std::endl;
    ref = 20;  // Changing value via the reference
    std::cout << "Modified value of x (via reference): " << x << std::endl;
}

// 3. POINTERS IN ARRAYS
void pointerToArrayDemo() {
    int arr[3] = {1, 2, 3};
    int* arrPtr = arr;  // Pointer to the first element of the array

    std::cout << "Array elements via pointer: " << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << *(arrPtr + i) << std::endl; // Accessing array elements using pointer arithmetic
    }
}

// 4. PASSING BY REFERENCE (WITHOUT COPYING)
void modifyByReference(int& ref) {
    ref = 100;  // Modify the original value
}

// 5. PASSING BY POINTER (ALTERNATE METHOD)
void modifyByPointer(int* ptr) {
    *ptr = 200;  // Modify the original value via pointer dereferencing
}

// 6. PRACTICAL USE CASE: SWAPPING TWO NUMBERS
void swapWithPointers(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapWithReferences(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 7. DYNAMIC MEMORY ALLOCATION
void dynamicMemoryDemo() {
    int* dynamicPtr = new int;   // Allocate memory for an integer on the heap
    *dynamicPtr = 50;            // Store a value in the dynamically allocated memory
    std::cout << "Dynamically allocated value: " << *dynamicPtr << std::endl;

    delete dynamicPtr;  // Free the dynamically allocated memory
}

// 8. POINTERS TO FUNCTIONS (CALLBACKS)
void callbackFunction(int a) {
    std::cout << "Callback function called with value: " << a << std::endl;
}

void executeCallback(void (*funcPtr)(int), int value) {
    funcPtr(value);  // Call the function via pointer
}

// MAIN PROGRAM TO DEMONSTRATE USE CASES
int main() {
    // Basic Pointers
    int x = 10;
    int* ptr = &x;
    std::cout << "Pointer demo: " << std::endl;
    std::cout << "Value of x: " << x << ", Pointer points to: " << *ptr << std::endl;

    // Passing by reference
    std::cout << "\nPass by reference demo: " << std::endl;
    modifyByReference(x);
    std::cout << "Value of x after modifying by reference: " << x << std::endl;

    // Passing by pointer
    std::cout << "\nPass by pointer demo: " << std::endl;
    modifyByPointer(ptr);
    std::cout << "Value of x after modifying by pointer: " << x << std::endl;

    // Swapping two numbers using pointers
    int a = 5, b = 10;
    std::cout << "\nBefore swap (pointers): a = " << a << ", b = " << b << std::endl;
    swapWithPointers(&a, &b);
    std::cout << "After swap (pointers): a = " << a << ", b = " << b << std::endl;

    // Swapping two numbers using references
    a = 5, b = 10;
    std::cout << "\nBefore swap (references): a = " << a << ", b = " << b << std::endl;
    swapWithReferences(a, b);
    std::cout << "After swap (references): a = " << a << ", b = " << b << std::endl;

    // Dynamic memory demo
    std::cout << "\nDynamic memory allocation demo: " << std::endl;
    dynamicMemoryDemo();

    // Pointers to functions (callback example)
    std::cout << "\nCallback function demo: " << std::endl;
    void (*funcPtr)(int) = &callbackFunction;
    executeCallback(funcPtr, 123);

    return 0;
}
