#include <iostream>
#include "Queue.hpp"

long long generate_kth(const long long N, long long k)
{
    Queue<long long> q;

    q.enqueue(N);
    q.enqueue(N + 1);
    q.enqueue(N * 2);

    while (k != 1)
    {
        q.dequeue();
        long long current = q.peek();
        q.enqueue(current + 1);
        q.enqueue(current * 2);

        --k;
    }

    return q.peek();
}

int main()
{
    std::cout << "Should be 12: " << generate_kth(5, 5);
    std::cout << "\nShould be 19: " << generate_kth(16, 8);

    return 0;
}