#include <iostream>
#include "Stack.hpp"
#include "Queue.hpp"

int main()
{
    int n = -1;

    do
    {
        std::cout << "Enter in a number greater than zero: ";
        std::cin >> n;
    } while (n < 1);

    Queue<Stack<unsigned>> q;

    for (size_t i = 1; i <= n; i++)
    {
        Stack<unsigned> s;

		for (int j = i; j > 0; j /= 2)
        {
            s.push(j % 2);
        }

        q.enqueue(s);
    }

    while (!q.is_empty())
    {
        q.peek().dump(std::cout);
        q.dequeue();
        std::cout << '\n';
    }

    return 0;
}