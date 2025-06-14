#ifndef SINGLELL_TPP
#define SINGLELL_TPP

#include "singlell.hpp"
#include <memory>
#include <optional>

template <typename T> SinglyLinkedList<T>::ListNode::ListNode() : m_val(T{}), mp_next(nullptr)
{}

template <typename T> SinglyLinkedList<T>::ListNode::ListNode(T value) : m_val(value), mp_next(nullptr)
{}


// Default contructor without parameter
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() 
    : mp_head(std::make_unique<ListNode>()), mp_tail(mp_head.get()), m_size{0}
{}

// Copy Constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T> &other)
    : mp_head{std::make_unique<ListNode>()}, mp_tail{mp_head.get()}
{
    if(this!= &other){
        ListNode* curr = other.mp_head->mp_next.get();
        while(curr)
        {
            AddLast(curr->m_val);
            curr = curr->mp_next.get();
        }
    }
}


// Move Constrcutor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T> &&other)
{
    if(this != &other)
    {
        this->mp_head = std::move(other.mp_head);
        this->mp_tail = other.mp_tail;
        this->m_size = other.m_size;
    }

    other.mp_head = nullptr;
    other.mp_tail = nullptr;
    other.m_size = 0;
}

// Destructor
template <typename T> SinglyLinkedList<T>::~SinglyLinkedList()
{}


// Operators
//  Assignment Operators
// Copy Assignment Operators
template <typename T>
SinglyLinkedList<T> &
SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &other) // Move Assignment operator
{
    if(&this != other)
    {
        this->mp_head = std::make_unique<ListNode>();
        this->mp_tail = mp_head.get();
        m_size = 0;
        
        ListNode* curr = other.mp_head->mp_next.get();
        while(curr != nullptr){
            AddLast(curr->m_val);
            curr = curr->mp_next.get();
        }
    }

    return *this;
}

// Move Assignment Operator
template <typename T> 
SinglyLinkedList<T>&
SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &&other)
{
    if(&this != other)
    {
        this->mp_head = std::move(other.mp_head);
        this->mp_tail = other.mp_tail;
        this->m_size = other.m_size;
        
        other.mp_head = nullptr;
        other.mp_tail = nullptr;
        other.m_size = 0;
    }
    return *this;
}


// Add elements to the array
template <typename T> bool SinglyLinkedList<T>::AddLast(T t)
{
    // find the last element
    ListNode *curr = this->mp_head.get();
    for (int i = 0; i < m_size; ++i)
    {
        curr = curr->mp_next.get();
    }

    curr->mp_next = std::make_unique<ListNode>(0);
    mp_tail = curr->mp_next.get();
    ++m_size;
}

/**
 * Add an element in front of the first element, if there's no element in the array, then add the element to the array
 */
template <typename T>
bool SinglyLinkedList<T>::AddFirst(T t)
{
    std::unique_ptr<ListNode> p_new = std::make_unique<ListNode>(t);
    p_new->mp_next = std::move(mp_head->mp_next);
    mp_head->mp_next = p_new.get();
    if (m_size == 0)
    {
        mp_tail = p_new.get();
    }
    ++m_size;
}

/**
 * Add an element in anywhere in the array by the index
 * return false if something's wrong with the input, true ifd successfully added
 */
template <typename T> bool SinglyLinkedList<T>::Add(unsigned int index, T val)
{
    if (index > m_size)
    {
        return false;
    }

    if (index == m_size)
    {
        addLast(val);
        return true;
    }

    ListNode *curr = mp_head.get();

    for (int i = 0; i < m_size; ++i)
    {
        curr = curr->mp_next.get();
    }

    std::unique_ptr<T> p_new = std::make_unique<T>(val);
    p_new->mp_next = std::move(curr->mp_next);
    curr->mp_next = std::move(p_new);

    ++m_size;

    return true;
}

/**
 *  Remove the last element in the LinkedList
 */
template <typename T> std::optional<T> SinglyLinkedList<T>::RemoveLast(T t)
{
    if (this->m_size == 0) // empty list
    {
        return std::nullopt;
    }

    // need to find the preceding element to the last element
    ListNode *prev = mp_head.get();
    for (int i = 0; i < m_size - 1; i++)
    {
        prev = prev->mp_next.get();
    }

    T ret_val = prev->mp_next->m_val;
    prev->mp_next.reset();
    mp_tail = prev;
    return ret_val;
}

/**
 * Remove the first element of the LinkedList
 */
template <typename T> std::optional<T> SinglyLinkedList<T>::RemoveFirst(T t)
{
    if (this->m_size == 0)
    {
        return std::nullopt;
    }

    T ret_val = mp_head->mp_next->m_val;
    mp_head->mp_next = std::move(mp_head->mp_next->mp_next);

    if (m_size == 1)
    {
        mp_tail = mp_head.get();
    }

    --m_size;

    return ret_val;
}

/**
 * Remove an arbitraray element from the SinglyLinkedList
 */
template <typename T> std::optional<T> SinglyLinkedList<T>::Remove(unsigned int index)
{
    if (m_size == 0)
    {
        return std::nullopt;
    }

    ListNode *prev = mp_head.get();
    for (int i = 0; i < index - 1; ++i)
    {
        prev = prev->mp_next.get();
    }

    T ret_val = prev->mp_next.m_val;
    prev->mp_next = std::move(prev->mp_next->mp_next);
    if (m_size == 1)
    {
        mp_tail = mp_head.get();
    }

    --m_size;

    return ret_val;
}

// Get
template <typename T>
std::optional<T> SinglyLinkedList<T>::Get(unsigned int index) const
{
    if (index >= m_size) {
        return std::nullopt;
    }
    
    ListNode* curr = mp_head->mp_next.get();
    for (unsigned int i = 0; i < index; ++i) {
        curr = curr->mp_next.get();
    }
    
    return curr->m_val;
}

template <typename T> std::optional<T> SinglyLinkedList<T>::GetFirst() const
{
    if (m_size == 0)
    {
        return std::nullopt;
    }

    return mp_head->mp_next.m_val;
}

template <typename T> std::optional<T> SinglyLinkedList<T>::GetLast() const
{
    return mp_tail->m_val;
}

// Change
/**
 * Return the Original value of the changed node
 */

template <typename T>
std::optional<T> SinglyLinkedList<T>::Set(unsigned int index, T val)
{
    if (index >= m_size) {
        return std::nullopt;
    }
    
    ListNode* curr = mp_head->mp_next.get();
    for (unsigned int i = 0; i < index; ++i) {
        curr = curr->mp_next.get();
    }
    
    T prev_val = curr->m_val;
    curr->m_val = val;
    return prev_val;
}

// Other useful functions
template <typename T> unsigned int SinglyLinkedList<T>::GetSize() const
{
    return this->m_size;
}

template <typename T> bool SinglyLinkedList<T>::IsEmpty() const
{
    return this->m_size == 0;
}

/**
 * Custom printing fucntion
 */
template <typename T> std::ostream &operator<<(std::ostream &os, SinglyLinkedList<T> &list)
{
    if (list.getSize() == 0)
    {
        os << "[]";
        return os;
    }
    
    // otherwise, print content of the linked list
    os << "[";

    typename SinglyLinkedList<T>::ListNode *curr = list.mp_head->mp_next.get();
    for (int i = 0; i < list.GetSize(); ++i)
    {
        if (i != list.GetSize() - 1)
        {
            os << " " << curr->m_val << " ->";
        }
        else
        {
            os << " " << curr->m_val;
        }
    }
    os << "]";
}

#endif
