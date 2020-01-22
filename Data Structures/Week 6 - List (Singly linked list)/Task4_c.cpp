#include <iostream>
#include <list>

template <class T>
void hist(std::list<T> l)
{
    l.sort();

    while (!l.empty())
    {
        size_t cntr = 1;
        T current = l.front();
        l.pop_front();
        while (!l.empty() && l.front() == current)
        {
            ++cntr;
            l.pop_front();
        }

        std::cout << current << ", " << cntr;

        if (!l.empty())
        {
            std::cout << " \\ ";
        }
    }
}

int main()
{
    std::list<int> l1 = { 1, 2, 3, 1, 5, 3 };

    hist(l1);

    return 0;
}