#include "Uneven_Tree.h"
#include "AVL.h"
#include <fstream>

void Uneven_Tree::clear(Node*& n)
{
	if (!n)
	{
		return;
	}

	for (Node* ptr : n->m_children)
	{
		clear(ptr);
	}

	delete n;
	n = nullptr;
}

void Uneven_Tree::serialize_helper(std::string& str, Node* node) const
{
	if (!node)
	{
		str.append("null").append(" ");
		return;
	}
	
	str.append(std::to_string(node->m_value)).append(" ");

	// Write the number of children.
	str.append(std::to_string(node->m_children.size())).append(" ");

	for (Node* a : node->m_children)
	{
		serialize_helper(str, a);
	}
}

Uneven_Tree::Node* Uneven_Tree::deserialize_helper(Queue<std::string>& q, Node*& node)
{
	std::string current = q.peek();
	q.dequeue();

	size_t number_children = to_number(q.peek());
	q.dequeue();

	Node* child = new Node();
	++m_size;

	for (size_t i = 0; i < number_children; i++)
	{
		child->m_children.push_back(deserialize_helper(q, child));
	}

	return child;
}

bool Uneven_Tree::is_gracious(std::vector<unsigned>& elements, Node* node)
{
	AVL differences;

	Queue<Node*> q;

	node->m_value = elements.back();
	elements.pop_back();

	q.enqueue(node);

	while (!q.is_empty())
	{
		Node* current = q.peek();
		q.dequeue();

		for (Node*& a : current->m_children)
		{
			a->m_value = elements.back();
			elements.pop_back();

			if (differences.insert(abs_diff(a->m_value, current->m_value)) == false)
			{
				return false;
			}
		}

		if (elements.empty())
		{
			return true;
		}

		for (Node* a : current->m_children)
		{
			q.enqueue(a);
		}
	}

	return false;
}

Uneven_Tree::Uneven_Tree()
	: m_root(nullptr),
	m_size(0)
{ }

Uneven_Tree::~Uneven_Tree()
{
	clear(m_root);
}

size_t Uneven_Tree::size() const
{
	return m_size;
}

void Uneven_Tree::serialize(const char* file) const
{
	std::string str;

	serialize_helper(str, m_root);

	std::ofstream fout(file, std::ios::trunc);
	if (!fout)
	{
		return;
	}

	if (!(fout << str))
	{
		return;
	}

	fout.close();
}

void Uneven_Tree::deserialize(const char* file)
{
	std::ifstream fin(file);
	if (!fin)
	{
		return;
	}

	Queue<std::string> string_q;

	std::string s;

	while (fin && fin.peek() != EOF)
	{
		if (!(fin >> s))
		{
			return;
		}

		string_q.enqueue(s);
	}

	if (string_q.is_empty() || string_q.peek() == "null")
	{
		return;
	}

	m_root = deserialize_helper(string_q, m_root);
}

bool Uneven_Tree::is_gracious(std::vector<unsigned> elements)
{
	if (!m_root)
	{
		return true;
	}

	return is_gracious(elements, m_root);
}