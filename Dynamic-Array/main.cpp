#include "dynamic_array.h"
#include <iostream>
#include <string>

int main(){
  std::cout << "Testing MyVec template class with std::string\n";
  
  MyVec<std::string> test_vec{};
  
  std::cout << "Initial size: " << test_vec.size() << "\n";
  std::cout << "Initial capacity: " << test_vec.capacity() << "\n";
  
  std::cout << "Adding elements with emplace_back...\n";
  test_vec.emplace_back("hello");
  test_vec.emplace_back("world");
  
  std::cout << "Vector contents: " << test_vec[0] << " " << test_vec[1] << "\n";
  std::cout << "Size after adding: " << test_vec.size() << "\n";
  std::cout << "Capacity after adding: " << test_vec.capacity() << "\n";
  
  std::cout << "Test completed successfully!\n";
  std::cin.get();
  return 0;
}