#include <iostream>
#include "List_task3.hpp"

int main()
{
    List<int> l1;

    l1.insert_last(1);
    l1.insert_last(2);
    l1.insert_last(3);
    l1.insert_last(4);
    l1.insert_last(5);
    l1.insert_last(6);

    l1.reverse();

    l1.map([](int x) {std::cout << x << ' '; });

    return 0;
}