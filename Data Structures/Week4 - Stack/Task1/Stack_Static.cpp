#include <iostream>

template <class T>
class Stack
{
private:
	// Total size of the array (stack).
	size_t m_capacity;

	// Uses an array based stack, i.e. static stack.
	T* m_data;

	// Index of the (first) position in which an element could be written.
	int m_tos;

	// Not needed if copying is forbidden.
	void copy(const Stack& rhs)
	{
		rhs.tos = 0;
		rhs.m_capacity = m_capacity;
		rhs.m_data = new T[rhs.m_capacity];

		for (size_t i = 0; i < m_tos; i++)
		{
			rhs.push(m_data[i]);
		}
	}

	void resize()
	{
		m_capacity *= 2;

		T* data = new T[m_capacity];

		for (size_t i = 0; i < m_tos; i++)
		{
			data[i] = m_data[i];
		}

		delete[] m_data;
		m_data = data;
	}

	// Not needed if copying is forbidden.
	void del()
	{
		delete[] m_data;
	}

public:
	Stack()
		: m_capacity(8),
		m_data(new T[m_capacity]),
		m_tos(0)
	{ }

	Stack(const Stack& rhs)
	{
		copy(rhs);
	}

	Stack& operator=(const Stack& rhs)
	{
		if (this != &rhs)
		{
			del();
			copy(rhs);
		}

		return *this;
	}

	~Stack()
	{
		del();
	}

	bool is_full() const
	{
		return m_tos == m_capacity;
	}

	bool is_empty() const
	{
		return m_tos == 0;
	}

	void push(const T& element)
	{
		if (is_full())
		{
			resize();
		}

		m_data[m_tos++] = element;
	}

	void pop()
	{
		--m_tos;
	}

	T top() const
	{
		return m_data[m_tos - 1];
	}

	T& top()
	{
		return m_data[m_tos - 1];
	}
};

int main()
{
	// Tests.
    Stack<int> s1;

	for (size_t i = 0; i < 10; i++)
	{
		s1.push(i);
	}

	for (size_t i = 0; !s1.is_empty(); i++)
	{
		std::cout << s1.top() << ' ';
		s1.pop();
	}

	return 0;
}