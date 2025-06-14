#include "singlell.hpp"
#include <iostream>
#include <cassert>
#include <string>

void test_constructor() {
    std::cout << "Testing constructors..." << std::endl;
    
    // Test default constructor
    SinglyLinkedList<int> list1;
    assert(list1.GetSize() == 0);
    assert(list1.IsEmpty());
    
    // Test constructor with value
    SinglyLinkedList<int> list2(42);
    assert(list2.GetSize() == 1);
    assert(!list2.IsEmpty());
    assert(list2.GetFirst().value() == 42);
}

void test_add_operations() {
    std::cout << "Testing add operations..." << std::endl;
    
    SinglyLinkedList<int> list;
    
    // Test AddFirst
    assert(list.AddFirst(1));
    assert(list.GetSize() == 1);
    assert(list.GetFirst().value() == 1);
    
    // Test AddLast
    assert(list.AddLast(2));
    assert(list.GetSize() == 2);
    assert(list.GetLast().value() == 2);
    
    // Test Add at index
    assert(list.Add(1, 3));
    assert(list.GetSize() == 3);
    assert(list.Get(1).value() == 3);
}

void test_remove_operations() {
    std::cout << "Testing remove operations..." << std::endl;
    
    SinglyLinkedList<int> list;
    list.AddLast(1);
    list.AddLast(2);
    list.AddLast(3);
    
    // Test RemoveFirst
    auto first = list.RemoveFirst(0);
    assert(first.has_value());
    assert(first.value() == 1);
    assert(list.GetSize() == 2);
    
    // Test RemoveLast
    auto last = list.RemoveLast(0);
    assert(last.has_value());
    assert(last.value() == 3);
    assert(list.GetSize() == 1);
    
    // Test Remove at index
    auto middle = list.Remove(0);
    assert(middle.has_value());
    assert(middle.value() == 2);
    assert(list.GetSize() == 0);
}

void test_get_set_operations() {
    std::cout << "Testing get/set operations..." << std::endl;
    
    SinglyLinkedList<int> list;
    list.AddLast(1);
    list.AddLast(2);
    list.AddLast(3);
    
    // Test Get
    assert(list.Get(0).value() == 1);
    assert(list.Get(1).value() == 2);
    assert(list.Get(2).value() == 3);
    
    // Test Set
    auto old_val = list.Set(1, 42);
    assert(old_val.has_value());
    assert(old_val.value() == 2);
    assert(list.Get(1).value() == 42);
}

void test_copy_move_operations() {
    std::cout << "Testing copy/move operations..." << std::endl;
    
    SinglyLinkedList<int> list1;
    list1.AddLast(1);
    list1.AddLast(2);
    
    // Test copy constructor
    SinglyLinkedList<int> list2(list1);
    assert(list2.GetSize() == 2);
    assert(list2.Get(0).value() == 1);
    assert(list2.Get(1).value() == 2);
    
    // Test move constructor
    SinglyLinkedList<int> list3(std::move(list1));
    assert(list3.GetSize() == 2);
    assert(list1.GetSize() == 0);
    
    // Test copy assignment
    SinglyLinkedList<int> list4;
    list4 = list2;
    assert(list4.GetSize() == 2);
    assert(list4.Get(0).value() == 1);
    
    // Test move assignment
    SinglyLinkedList<int> list5;
    list5 = std::move(list2);
    assert(list5.GetSize() == 2);
    assert(list2.GetSize() == 0);
}

int main() {
    try {
        test_constructor();
        test_add_operations();
        test_remove_operations();
        test_get_set_operations();
        test_copy_move_operations();
        
        std::cout << "All tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
