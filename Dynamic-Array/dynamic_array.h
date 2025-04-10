#pragma once
#include <iostream>

template <typename E> // E represents the Dynamic Type of template that we are
                      // going to store
class MyVec {
private:
  size_t m_size; // keep track of how large the dynamic arrays are
  size_t m_capacity;  // keep track of how many elements can this array be filled
  E *mp_data;    // a pointer to the actual data
public:
  MyVec();             // Default Constructor
  MyVec(size_t size);  // Constructor with 1 parameter
  MyVec(MyVec &other); // Copy Constructor
  MyVec(MyVec &&other) noexcept; // Move Constructor
  ~MyVec(); // Clear the memory footprint in this function

public: // Getters and Operators
  // Getters
  size_t size() const; // return the size
  size_t capacity() const; // return the capacity

  // Operators
  // Copy Assignment Operator
  MyVec& operator=(const MyVec &other);
  // Move Assignment Operator
  MyVec& operator=(MyVec &&other);
  E& operator[](size_t idx); // give the index, return the Data

private: // Specific Method
  bool mf_checkElementPos(); // check whether an newly added
  bool mf_checkIndexPos();
  bool grow(); // grow the capacity
  bool shrink(); //shrink the capacity

public:
  // Add Element
  bool push_back(const E& data); // add element to the end
  template<typename...Args>
  E& emplace_back(Args&&... data); // add element to the end, and construct that
  // Delete Element 
  bool remove(size_t idx); // Given an index, remove the element
  // Change Element
  bool replace(const E& data); // Give the data, replace the data in the array with the new one
  // Look up for Element
  size_t find(const E& data) const; // Give the Data, return the index
  // Look up for the index
  E& at(size_t idx); // Give the index, return the Lval reference to the Data
  
};

#include "dynamic_array.tpp"