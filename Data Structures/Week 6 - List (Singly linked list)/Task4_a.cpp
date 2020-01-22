#include <iostream>
#include "List.hpp"

template <class T>
size_t count(const T& a, List<T> l)
{
    size_t cnt = 0;

    while (!l.is_empty())
    {
        if (a == l.remove_first())
        {
            ++cnt;
        }
    }

    return cnt;
}

int main()
{
    List<int> l1;
    l1.insert_front(0);
    l1.insert_front(1);
    l1.insert_front(0);
    l1.insert_front(1);

    std::cout << count(0, l1) << ' ' << count(5, l1) << std::endl;

    return 0;
}