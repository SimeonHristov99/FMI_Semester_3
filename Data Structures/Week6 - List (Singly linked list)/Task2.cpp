#include <iostream>
#include "List_task2.hpp"

int main()
{
    List<int> l1;

    l1.insert_last(-5);
    l1.insert_last(5);
    l1.insert_last(5);
    l1.insert_last(5);
    l1.insert_last(5);
    l1.insert_last(-5);
    l1.insert_last(6);
    l1.insert_last(5);
    l1.insert_last(5);
    l1.insert_last(16);

    l1.remove_repeating();

    l1.map([](int x) {std::cout << x << ' '; });

    return 0;
}