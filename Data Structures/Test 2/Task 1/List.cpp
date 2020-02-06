#include <iostream>
#include "List.h"

void List::copy(const List& rhs)
{
	m_first = m_last = nullptr;

	Node* current = rhs.m_first;

	if (current)
	{
		push_back(current->m_value);
		current = current->m_next;
	}
}

void List::del()
{
	while (m_first && m_first != m_last)
	{
		Node* current = m_first;

		m_first = m_first->m_next;

		current = nullptr;
		delete current;
	}

	m_last = nullptr;
	delete m_first;
}

void List::push_back(const int value)
{
	if (!m_last)
	{
		push(value);
	}
	else
	{
		m_last->m_next = new Node(value, nullptr);
		m_last = m_last->m_next;
	}
}

void List::pop_front()
{
	Node* current = m_first;
	m_first = m_first->m_next;

	current->m_next = nullptr;
	delete current;
}

List List::merge_helper(const List& rhs)
{
	List new_list;

	Node* current_lhs = m_first;
	Node* current_rhs = rhs.m_first;

	while (current_lhs && current_rhs)
	{
		while (current_lhs && current_lhs->m_value < current_rhs->m_value)
		{
			new_list.push_back(current_lhs->m_value);
			current_lhs = current_lhs->m_next;
		}

		do
		{
			new_list.push_back(current_rhs->m_value);
			current_rhs = current_rhs->m_next;
		} while (current_lhs && current_rhs && current_rhs->m_value < current_lhs->m_value);
	}

	if (current_lhs && !current_rhs)
	{
		while (current_lhs)
		{
			new_list.push_back(current_lhs->m_value);
			current_lhs = current_lhs->m_next;
		}
	}
	else if (!current_lhs && current_rhs)
	{
		while (current_rhs)
		{
			new_list.push_back(current_rhs->m_value);
			current_rhs = current_rhs->m_next;
		}
	}

	return new_list;
}

List::List()
	: m_first(nullptr),
	m_last(nullptr)
{ }

List::List(const List & rhs)
{
	copy(rhs);
}

List& List::operator=(const List& rhs)
{
	if (this != &rhs)
	{
		del();
		copy(rhs);
	}
	return *this;
}

List::~List()
{
	del();
}

void List::print() const
{
	Node* current = m_first;

	while (current)
	{
		std::cout << current->m_value;

		if (current->m_next)
		{
			std::cout << "->";
		}

		current = current->m_next;
	}
}

void List::sort()
{
	Node* current = m_first;

	while (current && current->m_next && current->m_value <= current->m_next->m_value)
	{
		current = current->m_next;
	}

	if (current && current->m_next)
	{
		current = current->m_next;

		while (m_first != current)
		{
			push_back(m_first->m_value);
			pop_front();
		}
	}	
}

bool List::is_sorted() const
{
	Node* current = m_first;

	while (current && current->m_next)
	{
		if (current->m_value > current->m_next->m_value)
		{
			while (current->m_next)
			{
				current = current->m_next;
			}

			return m_first->m_value >= current->m_value;
		}

		current = current->m_next;		
	}

	return true;
}

void List::push(const int value)
{
	m_first = new Node(value, m_first);

	if (m_last == nullptr)
	{
		m_last = m_first;
	}
}

List List::merge(List rhs)
{
	List current_copy;

	if (!is_sorted())
	{
		std::cout << "The first argument is wrong!";
		return current_copy;
	}

	if (!rhs.is_sorted())
	{
		std::cout << "The second argument is wrong!";
		return current_copy;
	}

	current_copy = *this;

	current_copy.sort();
	rhs.sort();

	return current_copy.merge_helper(rhs);
}