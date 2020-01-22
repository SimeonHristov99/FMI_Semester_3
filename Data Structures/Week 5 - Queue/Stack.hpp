#pragma once

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

	bool dump(std::ostream& out);
};

template<class T>
inline void Stack<T>::copy(const Stack& rhs)
{
	m_capacity = rhs.m_capacity;
	m_tos = rhs.m_tos;

	m_data = new T[m_capacity];

	for (size_t i = 0; i < m_tos; i++)
	{
		m_data[i] = rhs.m_data[i];
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
inline void Stack<T>::del()
{
	delete[] m_data;
}

template<class T>
inline Stack<T>::Stack()
	: m_capacity(8),
	m_data(new T[m_capacity]),
	m_tos(0)
{ }

template<class T>
Stack<T>::Stack(const Stack& rhs)
{
	copy(rhs);
}

template<class T>
inline Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if (this != &rhs)
	{
		del();
		copy(rhs);
	}
	return *this;
}

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

template<class T>
inline bool Stack<T>::dump(std::ostream& out)
{
	for (int i = m_tos - 1; i >= 0; --i)
	{
		if (!(out << m_data[i]))
		{
			return false;
		}
	}

	return true;
}