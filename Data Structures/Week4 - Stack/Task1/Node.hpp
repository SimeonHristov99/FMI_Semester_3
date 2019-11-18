#pragma once

template <class T>
struct Node
{
	T m_data;
	Node* m_next;

	Node(const T& data, Node* next = nullptr)
		: m_data(data),
		m_next(next)
	{ }
};