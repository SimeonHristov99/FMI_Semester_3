#pragma once

class List
{
private:
    struct Node
    {
        int m_value;
        Node* m_next;

        Node(const int value, Node* next = nullptr)
            : m_value(value),
            m_next(next)
        { }
    } *m_first, *m_last;

    void copy(const List& rhs);
    void del();

    void push_back(const int value);
    void pop_front();

    List merge_helper(const List& rhs);

public:
    List();
    List(const List& rhs);
    List& operator=(const List& rhs);
    ~List();

    bool is_sorted() const;

    void print() const;

    void sort();

    void push(const int value);

    List merge(List rhs);
};