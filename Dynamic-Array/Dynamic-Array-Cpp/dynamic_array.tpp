#ifndef DYNAMIC_ARRAY_TPP
#define DYNAMIC_ARRAY_TPP

#include "dynamic_array.h"  // Include the header first

#include <cstddef>  // For size_t
#include <cstring>  // For memcpy
#include <iostream> // For cout
#include <stdexcept> // For exceptions
#include <utility>  // For std::forward

// Template implementations for MyVec

/**
 * A constructor with no parameter
 */
template <typename E> MyVec<E>::MyVec() :
 m_size{0}, 
 m_capacity{1},
 mp_data(new E[1])
{}

/**
 * A constructor with 1 default parameter
 * @param in_capacity how much capacity user defined
 */
template <typename E>
MyVec<E>::MyVec(size_t in_capacity) :
  m_size(0),
  m_capacity(in_capacity),
  mp_data(new E[in_capacity])
{}


/**
 * A Copy Constructor
 */
template <typename E>
MyVec<E>::MyVec(MyVec &other):
  m_size{other.m_size},
  m_capacity{other.m_capacity}
{
  std::cout << "copy contructor called" << std::endl;
  delete[] mp_data; // empty the data pointed by mp_data
  mp_data = new E[m_capacity];
  std::memcpy(mp_data, other.mp_data, m_size * sizeof(E));
}


/**
 *  A Move Constructor
 */
template <typename E>
MyVec<E>::MyVec(MyVec &&other) noexcept: 
  m_size{std::move(other.m_size)}, 
  m_capacity{std::move(other.m_capacity)},
  mp_data{std::move(other.mp_data)}
{
  // for debug
  std::cout << "move constructor called" << std::endl;
  // Simply nullify everything that the other contains
  other.m_size = 0;
  other.m_capacity = 0;
  other.mp_data = nullptr;
}

template <typename E>
MyVec<E>::~MyVec() {
  // Release the memory acquired by this class
  if(mp_data != nullptr){
    delete[] mp_data;
  }
}

// Helper functions
template <typename E> 
size_t MyVec<E>::size() const {
  return this->m_size;
}

template <typename E> 
size_t MyVec<E>::capacity() const {
  return this->m_capacity;
}

template <typename E>
bool
MyVec<E>::grow()
{
  size_t new_capacity = this->m_capacity * 2;
  if (new_capacity == 0) {
    new_capacity = 1;  // Start with capacity of 1 if current is 0
  }
  try {
    E* new_data = new E[new_capacity];
    // Copy existing elements
    std::memcpy(new_data, mp_data, m_size * sizeof(E));
    // Delete old array and update pointers
    delete[] mp_data;
    mp_data = new_data;
    this->m_capacity = new_capacity;
    return true;
  } catch (const std::bad_alloc&){
    // Memory allocation failed
    return false;
  }
} // grow the capacity


template <typename E>
bool
MyVec<E>::shrink()
{
  m_capacity = static_cast<size_t>(this->m_capacity * 0.5);
  return true;
} //shrink the capacity

// Operators
// Copy Assignment Operator
template <typename E>
MyVec<E>& MyVec<E>::operator=(const MyVec &other)
{
    if (this != &other) {  // Handle self-assignment
        delete[] mp_data;   // Free existing memory
        m_size = other.m_size;
        mp_data = new E[m_size];  // Allocate new memory
        std::memcpy(mp_data, other.mp_data, m_size * sizeof(E));  // Copy data
    }
    return *this;  // Return reference to current object
}

// Move Assignment Operator
template <typename E>
MyVec<E>&
MyVec<E>::operator=(MyVec &&other)
{
  if(this != &other)
  {
    delete[] mp_data; // Free existing memory
    m_size = other.m_size; // Transfer size 
    mp_data = other.mp_data; // Transfer ownership of data
    other.mp_data = nullptr; // Nullify the moved-from object
  }
  return *this; // Return referenceto current object
}

template<typename E>
E&
MyVec<E>::operator[](size_t idx){
  if(idx < 0 || idx >= m_size){
    throw std::out_of_range("Index out of range");
  }
  return mp_data[idx];
}

template<typename E>
template<typename...Args>
E&
MyVec<E>::emplace_back(Args&&... args)
{
  //Check availability
  if(m_size == m_capacity){
    if(!grow()){
      throw std::bad_alloc();
    }
  }
  // Construct in-place using placement new
  new (&mp_data[m_size]) E(std::forward<Args>(args)...);
  
  // Return reference to the newly added element
  return mp_data[m_size++];
}

// Add Element
/**
 * Add element to the back of the array
 * Given the data has already be constructed
 */
template<typename E>
bool
MyVec<E>::push_back(const E& data)
{
  // Check availabilities
  if(m_size == m_capacity){
    if (!grow()) {
      return false;  // Return false if memory allocation in grow() failed
    }
  } 
  mp_data[m_size] = data;
  ++m_size;
  return true;
}

/**
 * @param idx the index of the element to be removed
 */
// Delete Element 
template<typename E>
bool MyVec<E>::remove(size_t idx)
{
  if(idx < 0 || idx >= m_size){
    return false;
  }
  
  // Copy the elements after the index to the index
  std::memcpy(mp_data + idx, mp_data + idx + 1, sizeof(E) * (m_size - idx - 1));
  --m_size;
  
  // Check if the size is less than 25% of the capacity
  if(m_size <= m_capacity * 0.25)
    shrink();

  // Return true if the element is removed
  return true;
}

// Change Element
template<typename E>
bool MyVec<E>::replace(const E& data)
{
  if(find(data) != m_size){
    mp_data[find(data)] = data;
    return true;
  }else{
    return false;
  }
}

// Look up for an Element
template<typename E>
size_t MyVec<E>::find(const E& data) const
{
  for(size_t i = 0; i < m_size; ++i){
    if(mp_data[i] == data){
      return i; // return the index
    }
  }
  return m_size; // return the size if not found
}

template<typename E>
E&
MyVec<E>::at(size_t idx){
  if(idx < 0 || idx >= m_size){
    throw std::out_of_range("Index out of range");
  }
  return mp_data[idx];
}

#endif // DYNAMIC_ARRAY_TPP
