#include "singly_linkedList.hpp"


#pragma once // include guard
#include <exception>
#include <iostream>
#include <stdexcept>

// Stores the Type T in the Container
template <typename T>
class SinglyLinkedList
{
private:
    struct ListNode
    {
        T m_val;
        std::unique_ptr<ListNode> next;
        ListNode();
        ListNode(T value);
    };
    std::unique_ptr<ListNode> mp_head; // A Pointer to the head of the List
    ListNode* mp_tail; // A Pointer to the End of the List

public:
    // Constructor with dummy head and tail
    SinglyLinkedList();
    SinglyLinkedList(T val);
    SinglyLinkedList(SinglyLinkedList &other);  // Copy Contructor
    SinglyLinkedList(SinglyLinkedList &&other); // Move Construcotr
    ~SinglyLinkedList();

public:
    SinglyLinkedList &operator=(SinglyLinkedList &other);  // Copy Assignment operator
    SinglyLinkedList &operator=(SinglyLinkedList &&other); // Move Assignment operator
public:
    // Add
    bool AddLast(T t);
    bool AddFirst(T t);
    bool Add(unsigned int index, T val);
    
    // Remove
    bool RemoveLast(T t);
    bool RemoveFirst(T t);
    bool Remove(unsigned int index);

    // Get
    T Get(unsigned int index) const;
    T GetFirst() const;
    T GetLast() const;

    // Set

    T Set(unsigned int index, T val);
    
    // Other useful functions
    unsigned int GetSize() const;
    bool IsEmpty() const;

    // Friend markers
    friend std::ostream& operator<<(std::ostream& os, SinglyLinkedList<T>& list);
};

#include "singly_linkedList.tpp"
