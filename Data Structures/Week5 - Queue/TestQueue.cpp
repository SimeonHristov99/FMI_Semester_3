#include <iostream>
#include "Queue.hpp"

// Test peek and dequeue.
template <class T>
void print(Queue<T>& q)
{
	while (!q.is_empty())
	{
		std::cout << q.peek() << ' ';
		q.dequeue();
	}
}

int main()
{
	std::cout << "Testing default constructor-----------------------------------\n";
	Queue<int> qi;
	Queue<char> qc;

	print(qi);
	print(qc);

	std::cout << "\n\nTesting enqueue() and destructor-----------------------------------\n";
	qi.enqueue(1);
	qi.enqueue(2);
	qi.enqueue(3);
	qi.enqueue(4);

	qc.enqueue('1');
	qc.enqueue('2');
	qc.enqueue('3');
	qc.enqueue('4');

	// Should be 1, 2, 3, 4 on both calls.
	print(qi);
	std::cout << std::endl;
	print(qc);

	std::cout << std::endl;

	std::cout << "\n\nTesting resize-----------------------------------\n";

	for (size_t i = 0; i < 200; i++)
	{
		if (i == 7)
		{
			std::cout << "Is full: " << qi.is_full() << "\nIs empty: " << qi.is_empty();
		}
		qi.enqueue(i);
	}

	std::cout << std::endl;

	for (char i = 'a'; i <= 'z'; i++)
	{
		qc.enqueue(i);
		qc.enqueue(i + ('A' - 'a'));
	}

	print(qi);
	std::cout << std::endl;
	print(qc);

	std::cout << "\n\nTesting dequeue-----------------------------------\n";

	for (size_t i = 0; i < 200; i++)
	{
		qi.enqueue(i);
	}

	for (size_t i = 0; i < 199; i++)
	{
		qi.dequeue();
	}

	print(qi); // Only 199 should show up.

	for (char i = 'a'; i <= 'z'; i++)
	{
		qc.enqueue(i);
		qc.enqueue(i + ('A' - 'a'));
	}

	for (size_t i = 0; i < 50; i++)
	{
		qc.dequeue();
	}

	print(qc); // Only 'z' and 'Z' should show up.

	std::cout << "\n\nTesting is_empty-----------------------------------\n";
	std::cout << std::boolalpha << "IntQ: " << qi.is_empty() << "\nCharQ: " << qc.is_empty();

	std::cout << "\n\nTesting peek-----------------------------------\n";
	qi.enqueue(1);
	qc.enqueue('1');

	std::cout << qi.peek() << ' ' << qc.peek();
	std::cout << std::boolalpha << "\nIntQ: " << qi.is_empty() << "\nCharQ: " << qc.is_empty();

	return 0;
}