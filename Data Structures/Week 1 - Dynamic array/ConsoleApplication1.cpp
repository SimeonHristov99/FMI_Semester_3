#include "pch.h"
#include <iostream>

template <typename T>
class DynamicArray
{
public:
	DynamicArray(const T* _elements = nullptr, const unsigned& _size = 0)
	{
		if (!_elements)
		{
			m_size = 0;
			m_CAPACITY = 8;

			m_elements = new T[m_CAPACITY];

			return;
		}

		m_size = _size;
		m_CAPACITY = m_size * 2;

		m_elements = new T[m_CAPACITY];

		for (size_t i = 0; i < m_size; i++)
		{
			m_elements[i] = _elements[i];
		}
}

	DynamicArray(const DynamicArray& other)
	{
		copy(other);
	}

	DynamicArray& operator=(const DynamicArray& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}

		return *this;
	}

	~DynamicArray()
	{
		del();
	}

	void resize()
	{
		m_CAPACITY *= 2;

		T* _temp = new T[m_CAPACITY];

		for (size_t i = 0; i < m_size; i++)
		{
			_temp[i] = m_elements[i];
		}

		delete[] m_elements;
		m_elements = _temp;
	}

	void push_back(const T& _element)
	{
		if (m_size == m_CAPACITY)
		{
			resize();
		}

		m_elements[m_size++] = _element;
	}

	void push_front(const T& _element)
	{
		if (m_size == m_CAPACITY)
		{
			resize();
		}

		for (size_t i = m_size; i > 0; --i)
		{
			m_elements[i] = m_elements[i - 1];
		}

		m_elements[0] = _element;

		m_size++;
	}

	void pop_back()
	{
		--m_size;
	}

	void pop_front()
	{
		for (size_t i = 1; i <= m_size; i++)
		{
			m_elements[i - 1] = m_elements[i];
		}

		--m_size;
	}

	void insertElement(const size_t& position, const T& element)
	{
		if (position < 0 || position > m_size)
		{
			std::cout << "\n\n\t\tERROR: insertElement() detected an invalid index!\n\n";
			return;
		}

		if (m_size == m_CAPACITY)
		{
			resize();
		}

		for (size_t i = m_size + 1; i >= position; --i)
		{
			m_elements[i] = m_elements[i - 1];
		}

		m_elements[position - 1] = element;

		++m_size;
	}

	unsigned getSize() const
	{
		return m_size;
	}

	void print() const
	{
		std::cout << "Your dynamic array:{ ";

		for (size_t i = 0; i < m_size; i++)
		{
			std::cout << m_elements[i] << " ";
		}

		std::cout << "}\n\n";
	}

private:
	T* m_elements;

	unsigned m_size;
	unsigned m_CAPACITY;

	void copy(const DynamicArray& other)
	{
		if (!other.m_elements)
		{
			std::cout << "\n\n\t\tERROR: copy() detected a nullptr!\n\n";
			return;
		}

		m_size = other.m_size;
		m_CAPACITY = m_size * 2;

		m_elements = new T[m_CAPACITY];

		for (size_t i = 0; i < m_size; i++)
		{
			m_elements[i] = other.m_elements[i];
		}
	}

	void del()
	{
		delete[] m_elements;
	}
};

int main()
{
	std::cout << "Testing default constructor and print() ---------------------------------------------------------------------------\n\n";
    DynamicArray<int> d1;

	d1.print();

	std::cout << "Testing copy constructor ---------------------------------------------------------------------------\n\n";

	DynamicArray<double> d2;
	d2.push_back(1.5);

	std::cout << "Next must be: ";
	d2.print();

	DynamicArray<double> d3 = d2;

	d3.print();

	std::cout << "Testing operator = ---------------------------------------------------------------------------\n\n";

	DynamicArray<double> d4;
	d4 = d3;
	d4.print();

	std::cout << "Testing resize() and push_back() ---------------------------------------------------------------------------\n\n";

	d4.push_back(1);
	d4.push_back(2);
	d4.push_back(3);
	d4.push_back(4);
	d4.push_back(5);
	d4.push_back(6);
	d4.push_back(7);
	d4.push_back(8);
	d4.push_back(9);
	d4.print();

	std::cout << "Testing push_front() and getSize() ---------------------------------------------------------------------------\n\n";

	d4.push_front(100);
	d4.print();
	std::cout << "Size is " << d4.getSize() << std::endl << std::endl;

	std::cout << "Testing pop_front() and pop_back() ---------------------------------------------------------------------------\n\n";
	
	d4.pop_front();
	d4.pop_back();
	d4.print();

	std::cout << "Testing insertElemenent() ---------------------------------------------------------------------------\n\n";
	d4.insertElement(2, 500);
	d4.print();

	return 0;
}