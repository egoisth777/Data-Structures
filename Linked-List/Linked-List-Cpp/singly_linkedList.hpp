#pragma once // include guarad
#include <iostream>
#include <stdexcept>

template <typename T> class SinglyLinkedList {
  struct Node {
    T m_val;
    Node *mp_next;
    Node();
    Node(T value);
  };

public:
  // Constructor with dummy head and tail
  SinglyLinkedList();
  SinglyLinkedList(T val);
  SinglyLinkedList(SinglyLinkedList &other);  // Copy Contructor
  SinglyLinkedList(SinglyLinkedList &&other); // Move Construcotr
  ~SinglyLinkedList();

public:
  SinglyLinkedList &
  operator=(SinglyLinkedList &other); // Copy Assignment operator
  SinglyLinkedList &
  operator=(SinglyLinkedList &&other); // Move Assignment operator
private:
};

#include "singly_linkedList.tpp"
