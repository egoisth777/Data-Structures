#ifndef SINGLELL_H
#define SINGLELL_H
#include <iostream>
#include <memory>
#include <optional>

// Stores the Type T in the Container
template <typename T> class SinglyLinkedList
{
  private:
    struct ListNode
    {
        T m_val;
        std::unique_ptr<ListNode> mp_next;
        ListNode();
        ListNode(T value);
    };

    std::unique_ptr<ListNode> mp_head; // A Pointer to the head of the List
    ListNode *mp_tail;                 // A Pointer to the End of the List
    size_t m_size;

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
    std::optional<T> RemoveLast(T t);

    std::optional<T> RemoveFirst(T t);
    std::optional<T> Remove(unsigned int index);

    // Get
    std::optional<T> Get(unsigned int index) const;
    std::optional<T> GetFirst() const;
    std::optional<T> GetLast() const;

    // Set

    std::optional<T> Set(unsigned int index, T val);

    // Other useful functions
    unsigned int GetSize() const;
    bool IsEmpty() const;

    // Friend markers
    friend std::ostream &operator<<(std::ostream &os, SinglyLinkedList<T> &list);
};
#include "singlell.tpp"
#endif
