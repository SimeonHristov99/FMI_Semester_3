#include <iostream>
#include "Queue.hpp"

template <class T>
bool is_sorted(Queue<T>& q)
{
    T current = q.peek();
    q.dequeue();

    while (!q.is_empty() && q.peek() == current)
    {
        q.dequeue();
    }

    if (q.is_empty())
    {
        return true;
    }

    if (q.peek() > current)
    {
        current = q.peek();
        q.dequeue();

        while (!q.is_empty() && q.peek() >= current)
        {
            current = q.peek();
            q.dequeue();
        }

        return ((q.is_empty()) ? true : false);
    }

    current = q.peek();
    q.dequeue();

    while (!q.is_empty() && q.peek() <= current)
    {
        current = q.peek();
        q.dequeue();
    }

    return ((q.is_empty()) ? true : false);
}

int main()
{
    Queue<int> q1;
    q1.enqueue(5);
    q1.enqueue(8);
    q1.enqueue(10);
    q1.enqueue(11);

    std::cout << "Should be true: " << std::boolalpha << is_sorted(q1);

    q1.enqueue(-1);
    q1.enqueue(-2);
    q1.enqueue(-5);
    q1.enqueue(-8);

    std::cout << "\nShould be true: " << std::boolalpha << is_sorted(q1);

    q1.enqueue(-1);
    q1.enqueue(-5);
    q1.enqueue(5);

    std::cout << "\nShould be false: " << std::boolalpha << is_sorted(q1);

    q1.enqueue(0);
    
    std::cout << "\nShould be true: " << std::boolalpha << is_sorted(q1);

    q1.enqueue(5);
    q1.enqueue(5);
    q1.enqueue(5);
    q1.enqueue(5);
    q1.enqueue(8);
    q1.enqueue(10);

    std::cout << "\nShould be true: " << std::boolalpha << is_sorted(q1);

    q1.enqueue(5);
    q1.enqueue(5);
    q1.enqueue(6);
    q1.enqueue(6);
    q1.enqueue(7);
    q1.enqueue(8);
    q1.enqueue(9);
    q1.enqueue(10);
    q1.enqueue(15);
    q1.enqueue(15);
    q1.enqueue(14);

    std::cout << "\nShould be false: " << std::boolalpha << is_sorted(q1) << std::endl;

    return 0;
}