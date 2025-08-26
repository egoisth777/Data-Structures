#ifndef DOUBLELL_HPP
#define DOUBLELL_HPP

#include <malloc.h>
#include <memory>
#include <optional>
#include <stdexcept>

/**
 * @brief A personal implementation of a Templated Doubly Linked List using
 * Smart Pointers (Unique Pointer Solution)
 *
 * @param T
 */

template <typename T>
class Doublell
{
    // Inner Node Class defined inside the class
  public:
    struct ListNode
    {
      protected:
        T m_data;                          // The Data that the current List Node is Holding
        std::unique_ptr<ListNode> mp_next; // The Pointer to the next ListNode
        ListNode* mp_prev;                 // The Pointer to the prev ListNode

        // constructors and destructor

      public:
        ListNode () noexcept = default; // default
        ListNode (T data);              // val
        ListNode (ListNode& other);     // copy
        ListNode (ListNode&& other);    // move
        ~ListNode ();                   // destructors

        // some useful functions
        inline const T&
        GetData () const
        {
            return m_data;
        }

        inline ListNode*
        GetNext () const
        {
            return this->mp_next.get ();
        }

        inline ListNode*
        GetPrev () const
        {
            return this->mp_prev;
        }

        inline std::optional<T>
        SetNext (std::unique_ptr<ListNode>& next) noexcept
        {
            this->mp_next = std::move (std::forward (next));
        }

        inline std::optional<T>
        SetPrev (ListNode* prev)
        {
            this->mp_prev = prev;
        }

        inline std::optional<T>
        SetData (const T& val)
        {
            this->m_data = val;
        }
    };

    // class members
  protected:
    std::unique_ptr<ListNode> mp_head;
    ListNode* mp_tail;
    size_t m_size;

  public:
    // Default Constructor
    Doublell (); // Create an empty Linked-List

    // copy constructors
    Doublell (Doublell& other); // Create a linked List from another linked list

    // move constructors
    Doublell (Doublell&& other); // Create a Linked-List from another Linked List by stealing its resource

    // Destructors
    ~Doublell () noexcept = default; // Destructor Dealing with Cleaning up

  public: // Get Head and Tail (Real)
    inline ListNode*
    GetHead () const
    {
        return mp_head->mp_next.get ();
    }
    inline ListNode*
    GetTail () const
    {
        return mp_tail->mp_prev;
    }

  public: // Operators
    // copy assignment operator
    Doublell& operator= (Doublell& other);
    // move assignment operator
    Doublell& operator= (Doublell&& other);

  public:
    // Add
    std::optional<T> AddFirst ();              // add the head, return the val of addd if successful
    std::optional<T> AddLast ();               // add the tail, return the val of addd if successful
    std::optional<T> Add (unsigned int index); // add by the index, return the val of the removed if successful

    // Remove

    std::optional<T> RemoveFirst ();     // remove the head, return the val of removed if successful
    std::optional<T> RemoveLast ();      // remove the tail, return the val of removed if successful
    std::optional<T> Remove (int index); // remove the ListNode by index, return the val of removed if successful

    // Get

    std::optional<T> GetFirst ();     // get the element in the head
    std::optional<T> GetLast ();      // get the element in the tail
    std::optional<T> Get (int index); // ge the optional
    size_t GetSize () const;

    // Set
    std::optional<T> Set (T data);
    // member methods

  public: // Some helper methods
    bool IsEmpty () noexcept;
};

// Definition of Internal ListNode Structure

template <typename T>
Doublell<T>::ListNode::ListNode (T data)
    : m_data{ data }, mp_next{ nullptr }
{
}

template <typename T>
Doublell<T>::ListNode::ListNode (ListNode& other)
{
    if (other != *this)
        {
            m_data = other.m_data;
            mp_next = other.mp_next;
        }
}

// Move Constructor for ListNode
template <typename T>
Doublell<T>::ListNode::ListNode (ListNode&& other)
    : m_data{ std::move (other.m_data) },
      mp_next{ std::move (other.mp_next) }
{
    other.m_data = T{}; // reset to default value
}

template <typename T
              Doublell<T>::ListNode::~ListNode ()
          = default;

// Constructors for Doublell

/**
 * @brief Construct a new Doublell< T>:: Doublell object
 * with T parameter
 *
 * @param T
 */
template <typename T>
Doublell<T>::Doublell ()
    : mp_head{ std::make_unique<ListNode> () }, // Create New ListNode on the Stack
      mp_tail{ new ListNode () },               // Create New ListNode on the Heap
      m_size{ 0 }
{
    mp_head->mp_next = std::make_unique<mp_tail> (); // make the head to piont to the tail
    mp_tail->mp_prev = mp_head.get ();               // make the tail point to the head
}

/**
 * @brief Copy Constructors
 * Copy the Data from the Other Doubly Linked List
 *
 * @param other the target for copying
 */
template <typename T>
Doublell<T>::Doublell (Doublell<T>& other)
    : mp_head{ std::make_unique<ListNode> () },
      m_size (other.m_size)
{
    this->mp_head = std::make_unique<ListNode> (); // Create Dummy Head

    ListNode* pIter1 = this->mp_head.get (); // Pointer to this
    ListNode* pIter2 = other.mp_head.get (); // Pointer to other
    for (int i = 0; i < m_size; ++i)
        {
            pIter1->mp_next = std::make_unique<ListNode> (*pIter2); // Copy Constructor
            pIter1->mp_next->mp_prev = pIter1;                      // Need to set the prev of next ListNode to the current one
            pIter1 = pIter1->mp_next.get ();                        // Need to update the iter1
            pIter2 = pIter2->mp_next.get ();                        // Need to update the iter2
        }
    // Create List Tail at the end
    pIter1->mp_next = std::make_unique<ListNode> ();
    pIter1->mp_next->mp_prev = pIter1; // Need to set the prev of next ListNode to the current one
    mp_tail = pIter1;
}

/**
 * @breif Move Constructor
 * Move the resources of the other Linked List to the Current One
 *
 *  @param other Doublell&& Represents the other Linked List
 */
template <typename T>
Doublell<T>::Doublell (Doublell<T>&& other)
    : mp_head{ std::move (other.mp_head) },
      mp_tail (other.mp_tail),
      m_size (other.m_size)
{
    other.mp_tail = nullptr;
    other.m_size = 0;
}

/**
 * @brief Copy Assignment Operators
 */
template <typename T>
Doublell<T>&
Doublell<T>::operator= (Doublell<T>& other)
{
    mp_head = std::make_unique<ListNode> (*other.mp_head); // Copy Construct a Dummy Head

    ListNode* pIter1 = this->mp_head.get ();
    ListNode* pIter2 = other.mp_head.get ();

    for (int i = 0; i < other.m_size; ++i)
        {
            pIter1->mp_next = std::make_unique<ListNode> (*pIter2);
            pIter1->mp_next->mp_prev = pIter1;
            pIter1 = pIter1->mp_next.get ();
            pIter2 = pIter2->mp_next.get ();
        }

    // Create List Tail at the end
    pIter1->mp_next = std::make_unique<ListNode> ();
    pIter1->mp_next->mp_prev = pIter1; // Need to set the prev of next ListNode to the current one
    mp_tail = pIter1;
}

// Add
/**
 * @brief Add an Element to the front of the Lilnked-List
 * dummy -> head -> ... -> tail => dummy -> newNode -> head -> ... -> tail
 */
template <typename T>
std::optional<T>
Doublell<T>::AddFirst (T data)
{
    // Create a new Unique Pointer
    std::unique_ptr<ListNode> pTemp{ std::make_unique<ListNode> (data) };
    std::swap (mp_head->mp_next, pTemp);
    mp_head->mp_next->mp_next = std::move (pTemp);

    // Clean and Set up the Previous Pointers
    mp_head->mp_next->mp_prev = mp_head.get ();
    mp_head->mp_next->mp_next->mp_prev = mp_head->mp_next.get ();
}

template <typename T>
std::optional<T>
Doublell<T>::AddLast (T data)
{
    // Add to the tail
    ListNode* pCurrTail = mp_tail->mp_prev; // The Curr Tail Node
    auto pTemp = std::make_unique<ListNode> (data);
    std::swap (mp_tail->mp_prev->mp_next, pTemp);           // pTemp -> DummyTail,
    mp_tail->mp_prev->mp_next->mp_next = std::move (pTemp); // Let New Tail's mp_next -> Dummy

    // Clean up the mp_prev dependencies
    ListNode* pNew = mp_tail->mp_prev->mp_next.get (); // A Pointer to the Newly Created Node
    ListNode* pPrevTail = mp_tail->mp_prev;

    pNew->mp_prev = pPrevTail;
    mp_tail->mp_rev->mp_prev = pNew;

    return pNew.GetData ();
}

/**
 * @breif Give an Arbitrary Location, add Node after that index
 * DummyHead -> Head(0) -> Node(1) -> ... -> Tail(size - 1) -> DummyTail
 *
 * Invalid: Index < 0
 */
template <typename T>
std::optional<T>
Doublell<T>::Add (unsigned int index)
{
    if (index > m_size)
        {
            throw std::out_of_range ("The Index is out of Range");
        }
    ListNode* pIter = GetHead (); // Starting from the DummyHead
    for (unsigned int i = 0; i < index; ++i)
        {
            pIter = pIter->mp_next.get ();
        }
}

// Remove
template <typename T>
std::optional<T>
Doublell<T>::RemoveFirst ()
{
}

template <typename T>
std::optional<T>
Doublell<T>::Remove (int index)
{
}

// Get
template <typename T>
std::optional<T>
Doublell<T>::GetFirst ()
{
}

template <typename T>
std::optional<T>
Doublell<T>::Get (int index)
{
}

template <typename T>
size_t
Doublell<T>::GetSize () const
{
}

// Set

std::optional<T>
Set (T data)
{
}
// member methods

bool
IsEmpty () noexcept
{
}

#endif
