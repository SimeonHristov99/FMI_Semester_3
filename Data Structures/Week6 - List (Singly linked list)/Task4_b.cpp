#include <iostream>
#include <list>

template <class T>
void remove(const T& a, std::list<T>& l)
{
    for (const T& x : l)
    {
        l.remove_if([a](const T& x) {return x == a; });
    }
}

int main()
{
    std::list<int> l1 = { 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 7, 4, 1, 2, 5, 6, 4, 2, 5, 6 };
    std::list<int> l2 = l1;

    std::cout << "Removing 6:\n\n";

    remove(6, l1);

    while (!l1.empty())
    {
        std::cout << l1.front() << ' ';
        l1.pop_front();
    }

    std::cout << "\n\nRemoving 5:\n\n";

    remove(6, l2);
    remove(5, l2);

    while (!l2.empty())
    {
        std::cout << l2.front() << ' ';
        l2.pop_front();
    }

    std::cout << '\n';

    return 0;
}