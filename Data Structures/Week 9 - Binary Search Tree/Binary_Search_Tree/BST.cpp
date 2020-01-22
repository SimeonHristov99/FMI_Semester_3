#include "BST.h"

void BST::clear(Node*& node)
{
	if (!node)
	{
		return;
	}

	clear(node->m_left);
	clear(node->m_right);

	delete node;
	node = nullptr;
}

bool BST::insert(unsigned value, Node*& node)
{
	if (!node)
	{
		node = new Node(value);

		return true;
	}

	if (value < node->m_value)
	{
		return insert(value, node->m_left);
	}

	if (value > node->m_value)
	{
		return insert(value, node->m_right);
	}

	return false;
}

BST::BST()
	: m_root(nullptr)
{ }

BST::~BST()
{
	clear(m_root);
}

bool BST::insert(unsigned value)
{
	return insert(value, m_root);
}
