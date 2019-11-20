#include <iostream>
#include <fstream>

class Stack
{
private:
	size_t m_capacity;
	char* m_data;
	int m_tos;

	void resize()
	{
		m_capacity *= 2;

		char* temp = new char[m_capacity];

		for (size_t i = 0; i < m_tos; i++)
		{
			temp[i] = m_data[i];
		}

		delete[] m_data;
		m_data = temp;
	}

public:
	Stack()
		: m_capacity(8),
		m_data(new char[m_capacity]),
		m_tos(0)
	{ }

	Stack(const Stack& rhs) = delete;
	Stack& operator=(const Stack& rhs) = delete;

	~Stack()
	{
		delete[] m_data;
	}

	bool is_empty() const
	{
		return m_tos == 0;
	}

	bool is_full() const
	{
		return m_tos == m_capacity;
	}

	void push(char element)
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

	char top() const
	{
		return m_data[m_tos - 1];
	}

	char& top()
	{
		return m_data[m_tos - 1];
	}
};

bool evaluate(const char* path)
{
	Stack s;

	std::ifstream fin(path);

	if (!fin)
	{
		std::cout << "no file";
		return false;
	}

	while (fin)
	{
		char c;

		fin.read(&c, 1);

		if (fin)
		{
			switch (c)
			{
			case ')':
			{
				if (s.is_empty() || s.top() != '(')
				{
					fin.close();
					return false;
				}

				s.pop();

				break;
			}
			case '(':
			{
				s.push(c);
				break;
			}
			case '[':
			{
				s.push(c);
				break;
			}
			case ']':
			{
				if (s.is_empty() || s.top() != '[')
				{
					fin.close();
					return false;
				}

				s.pop();

				break;
			}
			case '{':
			{
				s.push(c);
				break;
			}
			case '}':
			{
				if (s.is_empty() || s.top() != '{')
				{
					fin.close();
					return false;
				}

				s.pop();

				break;
			}
			}
		}
	}

	fin.close();

	if (!s.is_empty())
	{
		return false;
	}

	return true;
}

int main()
{
	const char* path = "check.txt";

	std::cout << std::boolalpha << evaluate(path) << std::endl;

	return 0;
}