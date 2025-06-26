#ifndef DOUBLELL_HPP
#define DOUBLELL_HPP
#include <memory>
#include <optional>

template <typename T> class Doublell
{
  private:
    struct ListNode
    {
        T m_val;
        std::unique_ptr<ListNode> mp_next;
        inline T getVal() const
        {
            return m_val;
        };
        inline void setVal(T val)
        {
            this->m_val = val;
        };
        inline ListNode *getNext() const
        {
            return mp_next.get();
        };
        inline void setNext(std::unique_ptr<ListNode> next)
        {
            this->mp_next = std::move(next);
        };

        // Constructors and Desctructors

        ListNode();
        ListNode(T val);
        ListNode(ListNode &other);
        ListNode(ListNode &&other);
        ~ListNode();
    };

    // Class Members

    std::unique_ptr<ListNode> mp_head;
    ListNode *mp_tail;

  public:
    // Constructors
    Doublell();
    Doublell(T val_head);

    // Copy Constructors
    Doublell(Doublell &other);

    // Move Constructors
    ~Doublell();

    // Operators, Getters and Setters
    // Copy Assignment Operator
    Doublell &operator=(Doublell &other);
    // Move Assignment Operator
    Doublell &operator=(Doublell &&other);

    // Getters and Setters
    ListNode *GetHead() const;
    ListNode *GetTail() const;

    std::optional<T> SetHead();
    std::optional<T> SetTail();

    // Member Methods
    //
};

#endif
