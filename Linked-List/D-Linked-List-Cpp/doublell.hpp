#ifndef DOUBLELL_HPP
#define DOUBLELL_HPP

#include <memory>
#include <optional>

template <typename T>
class Doublell
{
  private:
    struct ListNode
    {
        T m_val;
        std::unique_ptr<ListNode> mp_next;

        // constructors and desctructors

        ListNode ();                 // defaultw
        ListNode (T val);            // val
        ListNode (ListNode& other);  // copy
        ListNode (ListNode&& other); // move
        ~ListNode ();                // destructors

        // some useful functions
        inline T
        getval () const
        {
            return m_val;
        };

        inline void
        setval (T val)
        {
            this->m_val = val;
        };

        inline ListNode*
        getnext () const
        {
            return mp_next.get ();
        };

        inline void
        setnext (std::unique_ptr<ListNode> next)
        {
            this->mp_next = std::move (next);
        };
    };

    // class members
  private:
    std::unique_ptr<ListNode> mp_head;
    ListNode* mp_tail;

  public:
    // constructors
    Doublell ();
    Doublell (T val_head);

    // copy constructors
    Doublell (Doublell& other);

    // move constructors
    Doublell (Doublell&& other);

    // Destructors
    ~Doublell ();

  public:
    // operators, getters and setters
    // copy assignment operator
    Doublell& operator= (Doublell& other);
    // move assignment operator
    Doublell& operator= (Doublell&& other);

    // getters and setters
    ListNode* GetHead () const;
    ListNode* GetTail () const;

    std::optional<T> SetHead (T val);
    std::optional<T> SetTail (T val);
    // member methods
};

#include "doublell.tpp"

#endif
