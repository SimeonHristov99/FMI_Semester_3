#include "List.hpp"
#include <iostream>

void print(const int x)
{
	std::cout << x << ' ';
}

int main()
{
    std::cout << "Testing constructor and destructor ------------------------------------------------\n\n";

	List<int> l1;

	l1.map(print);
	
	std::cout << "\n\nTesting insert_front() and map ------------------------------------------------\n\n";

	l1.insert_front(8);
	l1.insert_front(7);
	l1.insert_front(6);
	l1.insert_front(5);
	l1.insert_front(4);
	l1.insert_front(3);
	l1.insert_front(2);
	l1.insert_front(1);

	// Should be 1 .. 8
	l1.map(print);
	
	std::cout << "\n\nTesting insert_last() ------------------------------------------------\n\n";

	l1.insert_last(9);
	l1.insert_last(10);
	l1.insert_last(11);
	l1.insert_last(12);
	l1.insert_last(13);
	l1.insert_last(14);
	l1.insert_last(15);
	l1.insert_last(16);

	// Should be 1 .. 16
	l1.map(print);

	std::cout << "\n\nTesting is_empty(), remove_first() and map ------------------------------------------------\n\n";

	while (!l1.is_empty())
	{
		l1.map([](int& x) {x += 1; });
		l1.map(print);
		l1.remove_first();
		std::cout << '\n';
	}

	std::cout << "\n\nTesting find() ------------------------------------------------\n\n";

	l1.insert_front(42);

	*(l1.find(42)) = 24;

	l1.map(print);

	std::cout << "\n\nTesting remove(key) ------------------------------------------------\n\n";

	l1.remove(24);

	l1.insert_last(1);
	l1.insert_last(2);
	l1.insert_last(5);
	l1.insert_last(2);
	l1.insert_last(3);

	l1.remove(2);

	l1.map(print);

	std::cout << "\n\nTesting remove(ptr) ------------------------------------------------\n\n";

	if (l1.find(200) == nullptr)
	{
		std::cout << "Not found\n";
	}

	l1.remove(l1.find(2));

	l1.map(print);

	std::cout << '\n';

	l1.remove(l1.find(1));
	l1.remove(l1.find(3));
	l1.map(print);

	std::cout << "\n\nTesting insert_after() ------------------------------------------------\n\n";

	l1.insert_after(nullptr, 100);
	l1.insert_after(l1.find(5), 300);
	l1.insert_after(l1.find(5), 99);
	l1.map(print);

	std::cout << "\n\nTesting get_at() ------------------------------------------------\n\n";

	if (l1.get_at(1))
	{
		std::cout << l1.remove(l1.get_at(1)) << std::endl;
	}

	if (l1.get_at(0))
	{
		std::cout << l1.remove(l1.get_at(0)) << std::endl;
	}

	l1.map(print);

	std::cout << '\n';
	
	return 0;
}