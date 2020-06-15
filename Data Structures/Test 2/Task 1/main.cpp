#include <iostream>
#include "List.h"

int main()
{
    std::cout << "Result 1: ";
    List lhs;

    lhs.push(10);
    lhs.push(7);
    lhs.push(5);
    lhs.push(2);
    lhs.push(1);

    List rhs;

    rhs.push(7);
    rhs.push(6);
    rhs.push(4);
    rhs.push(2);
    rhs.push(11);
    rhs.push(9);

    lhs.merge(rhs).print();

    std::cout << "\n\nResult 2: ";

    List lhs_2;

    lhs_2.push(7);
    lhs_2.push(5);
    lhs_2.push(2);
    lhs_2.push(1);
    lhs_2.push(10);

    List rhs_2;

    rhs_2.push(9);
    rhs_2.push(7);
    rhs_2.push(6);
    rhs_2.push(4);
    rhs_2.push(2);
    rhs_2.push(11);
    rhs_2.push(8);

    lhs_2.merge(rhs_2).print();

    std::cout << '\n';

    return 0;
}