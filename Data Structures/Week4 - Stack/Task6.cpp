#include <iostream>

template <class T>
class Stack
{
private:
	size_t m_capacity;

	T* m_data;

	int m_tos;

	void copy(const Stack& rhs);
	void resize();
	void del();

public:
	Stack();

	Stack(const Stack& rhs);
	Stack& operator=(const Stack& rhs);

	~Stack();

	bool is_full() const;

	bool is_empty() const;

	void push(const T& element);

	void pop();

	T top() const;

	void to_string(char* write_to) const;
};

template<class T>
void Stack<T>::copy(const Stack& rhs)
{
	m_capacity = rhs.m_capacity;

	m_data = new T[m_capacity];

	for (size_t i = 0; i < rhs.m_tos; i++)
	{
		push(rhs.m_data[i]);
	}
}

template<class T>
inline void Stack<T>::resize()
{
	T* data = new T[m_capacity * 2];

	for (size_t i = 0; i < m_tos; i++)
	{
		data[i] = m_data[i];
	}

	m_capacity *= 2;

	delete[] m_data;
	m_data = data;
}

template<class T>
void Stack<T>::del()
{
	delete[] m_data;
}

template<class T>
Stack<T>::Stack(const Stack& rhs)
{
	copy(rhs);
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if (this != &rhs)
	{
		del();
		copy(rhs);
	}

	return *this;
}

template<class T>
inline Stack<T>::Stack()
	: m_capacity(8),
	m_data(new T[m_capacity]),
	m_tos(0)
{ }

template<class T>
inline Stack<T>::~Stack()
{
	del();
}

template<class T>
inline bool Stack<T>::is_full() const
{
	return m_tos == m_capacity;
}

template<class T>
inline bool Stack<T>::is_empty() const
{
	return m_tos == 0;
}

template<class T>
inline void Stack<T>::push(const T& element)
{
	if (is_full())
	{
		resize();
	}

	m_data[m_tos++] = element;
}

template<class T>
inline void Stack<T>::pop()
{
	--m_tos;
}

template<class T>
inline T Stack<T>::top() const
{
	return m_data[m_tos - 1];
}

template<>
void Stack<char>::to_string(char* write_to) const
{
	size_t i = 0;

	for (i; i < m_tos; i++)
	{
		write_to[i] = m_data[i];
	}

	write_to[i] = '\0';
}

void decompress(char* expression)
{
	Stack<int> numbers;
	Stack<char> letters;

	for (const char* c = expression; *c; ++c)
	{
		if (*c > '0' && *c <= '9')
		{
			unsigned num = 0;

			while (*c > '0' && *c <= '9')
			{
				num = num * 10 + (*c - '0');
				++c;
			}
			
			numbers.push(num);
		}
		
		if (*c == ')')
		{
			Stack<char> to_repeat;
			
			unsigned times_to_repeat = numbers.top();
			numbers.pop();

			while (letters.top() != '(')
			{
				to_repeat.push(letters.top());
				letters.pop();
			}

			letters.pop();

			// Make a copy of to_repeat.
			Stack<char> to_repeat_copy = to_repeat;

			// Dump the copy in letters while times_to_repeat > 1.
			while (times_to_repeat > 1)
			{
				while (!to_repeat_copy.is_empty())
				{
					letters.push(to_repeat_copy.top());
					to_repeat_copy.pop();
				}

				if (times_to_repeat != 1)
				{
					to_repeat_copy = to_repeat;
				}

				--times_to_repeat;
			}

			// Dump to_repeat in repeated.
			while (!to_repeat.is_empty())
			{
				letters.push(to_repeat.top());
				to_repeat.pop();
			}
		}
		else
		{
			letters.push(*c);
		}
	}

	letters.to_string(expression);
}

int main()
{
	char expression0[50] = "A";
	char expression1[50] = "AB";
	char expression2[50] = "3(A)";
	char expression3[50] = "3(AB2(B))";
	char expression4[50] = "12(ZQ)";

	decompress(expression0);
	decompress(expression1);
	decompress(expression2);
	decompress(expression3);
	decompress(expression4);

	std::cout << expression1 << std::endl;
	std::cout << expression2 << std::endl;
	std::cout << expression3 << std::endl;
	std::cout << expression4 << std::endl;

	return 0;
}