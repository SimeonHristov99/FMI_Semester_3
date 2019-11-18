#pragma once

#include "Node.hpp"

template <class T>
class Stack
{
private:
	Node<T>* tos;

	void copy(const Stack& rhs);
	void del();

public:
	Stack();
	Stack(const Stack& rhs);
	Stack& operator=(const Stack& rhs);
	~Stack();

	void push(const T& element);
	T pop();
	bool is_empty() const;

	T& top() const;
};

template<class T>
inline void Stack<T>::copy(const Stack& rhs)
{
	Node<T>* t = rhs.tos;

	Stack temp;

	while (t)
	{
		temp.push(t->m_data);

		t = t->m_next;
	}

	t = temp.tos;

	while (t)
	{
		push(t->m_data);

		t = t->m_next;
	}
}

template<class T>
inline void Stack<T>::del()
{
	while (tos)
	{
		Node<T>* t = tos;

		tos = tos->m_next;

		delete t;
	}
}

template<class T>
inline Stack<T>::Stack()
	: tos(nullptr)
{ }

template<class T>
inline Stack<T>::Stack(const Stack& rhs)
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
inline void Stack<T>::push(const T& element)
{
	tos = new Node<T>(element, tos);
}

template<class T>
inline T Stack<T>::pop()
{
	if (is_empty())
	{
		std::cout << "\n\t\tERROR: Stack is empty!\n\n";
	}
	else
	{
		Node<T>* t = tos;

		tos = tos->m_next;

		T element = t->m_data;

		delete t;

		return element;
	}
}

template<class T>
inline T& Stack<T>::top() const
{
	if (is_empty())
	{
		std::cout << "\n\t\tERROR: Stack is empty!\n\n";
	}

	return tos->m_data;
}

template<class T>
inline bool Stack<T>::is_empty() const
{
	return tos == nullptr;
}