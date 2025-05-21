#ifndef VECTOR_MYVECTOR_H
#define VECTOR_MYVECTOR_H
#include <iostream>
#include <stdexcept>
template <typename T, int N> class MyVector
{

  public:
    MyVector() : m_size(0), m_max_size(N), pArr(new T[N])
    {
    }
    ~MyVector()
    {
        delete[] pArr;
    }

    unsigned int size()
    {
        return m_size;
    }
    void push(T element)
    {
        if (++m_size > m_max_size)
        {
            m_max_size *= 2; // enlarge the array by size of 2
            T *s = pArr;     // copy pointer (keep the original pointer pointed to a new mem location)
            pArr = new T[2 * m_max_size];
            T *d = pArr; // copy pointer 2, keep the new orignal location
            for (int i = 0; i < m_max_size / 2; i++)
            {
                d[i] = s[i];
            }
            delete[] s;
        }
        // insert the element
        pArr[m_size - 1] = element;
    } // push an element at the back of the current vector

    T pop()
    {
        // check that the empty pop behavior is detected (Not implemented in STD)
        if (m_size == 0)
        {
            throw std::runtime_error("Attempted to pop from an empty MyVector");
        }
        return this->pArr[--m_size];
    } // pop up the last element in the vector

  protected:
    T *pArr;                 // container that actually stores the data (A pointer to typename T)
    unsigned int m_size;     // size that keeps track of the inner container size (How many elements are stored)
    unsigned int m_max_size; // use to track the max size of the current array
};
#endif // VECTOR_MYVECTOR_H
