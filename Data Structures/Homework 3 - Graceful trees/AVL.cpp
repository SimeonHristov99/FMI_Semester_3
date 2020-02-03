#include "AVL.h"
#include "helper_functions.h"
#include <iostream>

void AVL::clear(Node* n)
{
	if (!n)
	{
		return;
	}

	clear(n->m_left);
	clear(n->m_right);
	delete n;
	n = nullptr;
}

void AVL::update(Node* node)
{
	int left_height = node->m_left == nullptr ? -1 : node->m_left->m_height;
	int right_height = node->m_right == nullptr ? -1 : node->m_right->m_height;

	node->m_height = 1 + max(left_height, right_height);

	node->m_balance_factor = right_height - left_height;
}

AVL::Node* AVL::rotate_left(Node* node)
{
	Node* new_parent = node->m_right;
	node->m_right = new_parent->m_left;
	new_parent->m_left = node;

	update(node);
	update(new_parent);

	return new_parent;
}

AVL::Node* AVL::rotate_right(Node* node)
{
	Node* new_parent = node->m_left;
	node->m_left = new_parent->m_right;
	new_parent->m_right = node;

	update(node);
	update(new_parent);

	return new_parent;
}

AVL::Node* AVL::left_left(Node* node)
{
	return rotate_right(node);
}

AVL::Node* AVL::left_right(Node* node)
{
	node->m_left = rotate_left(node->m_left);
	return left_left(node);
}

AVL::Node* AVL::right_right(Node* node)
{
	return rotate_left(node);
}

AVL::Node* AVL::right_left(Node* node)
{
	node->m_right = rotate_right(node->m_right);
	return right_right(node);
}

AVL::Node* AVL::balance(Node* node)
{
	if (node->m_balance_factor == -2)
	{
		if (node->m_left->m_balance_factor <= 0)
		{
			return left_left(node);
		}

		return left_right(node);
	}

	if (node->m_balance_factor == 2)
	{
		if (node->m_right->m_balance_factor >= 0)
		{
			return right_right(node);
		}

		return right_left(node);
	}

	return node;
}

bool AVL::insert(unsigned value, Node*& node)
{
	if (!node)
	{
		node = new Node(value);
		return true;
	}

	if (node->m_value == value)
	{
		return false;
	}

	node->m_value > value ? insert(value, node->m_left) : insert(value, node->m_right);

	update(node);

	node = balance(node);

	return true;
}

void AVL::print(Node* node) const
{
	if (!node)
	{
		return;
	}

	std::cout << node->m_value;
	print(node->m_left);
	print(node->m_right);
}

AVL::AVL()
	: m_root(nullptr)
{ }

AVL::~AVL()
{
	clear(m_root);
}

bool AVL::insert(unsigned value)
{
	return insert(value, m_root);
}

void AVL::print() const
{
	print(m_root);
}
