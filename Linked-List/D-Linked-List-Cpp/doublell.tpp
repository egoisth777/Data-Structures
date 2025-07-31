// Definition of Internal ListNode Structure

template <typename T>
Doublell<T>::ListNode::ListNode () : m_val{ -1 }, mp_next{ nullptr }
{
}

template <typename T>
Doublell<T>::ListNode::ListNode (T val)
    : m_val{ val }, mp_next{ nullptr }
{
}

template <typename T>
Doublell<T>::ListNode::ListNode (ListNode& other)
{
    if (other != *this)
        {
            m_val = other.m_val;
            mp_next = other.mp_next;
        }
}

template <typename T>
Doublell<T>::ListNode::ListNode (ListNode&& other)
    : m_val{ std::move (other.m_val) },
      mp_next{ std::move (other.mp_next) }
{
}

template <typename T>
Doublell<T>::ListNode::~ListNode ()
{
}

template <typename T>
Doublell<T>::Doublell ()
    : mp_head{ new ListNode{} },
      mp_tail{ this->mp_head }
{
}

template <typename T>
Doublell<T>::Doublell (T val_head)
    : mp_head{ new ListNode{ val_head } }, mp_tail{ this->mp_head }
{
}

// Copy constructors (Copy the Resourcess)
template <typename T>
Doublell<T>::Doublell (Doublell& other)
{
}

// Move constructors (Move the Resrources)
template <typename T>
Doublell<T>::Doublell (Doublell&& other)
{
}

template <typename T>
Doublell<T>::~Doublell ()
{
}

// operators, getters and setters
//
// copy assignment operator
template <typename T>
Doublell<T>&
Doublell<T>::operator= (Doublell<T>& other)
{
}

// move assignment operator
template <typename T>
Doublell<T>&
Doublell<T>::operator= (Doublell<T>&& other)
{
}

// getters and setters
template <typename T>
Doublell<T>::ListNode*
Doublell<T>::GetHead () const
{
}

template <typename T>
Doublell<T>::ListNode*
Doublell<T>::GetTail () const
{
}

template <typename T>
std::optional<T>
Doublell<T>::SetHead (T val)
{
}

template <typename T>
std::optional<T>
Doublell<T>::SetTail (T val)
{
}
