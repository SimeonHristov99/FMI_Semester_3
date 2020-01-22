#pragma once

#include <vector>
#include "helper_functions.h"
#include "Queue.hpp"

class Uneven_Tree
{
private:
	struct Node
	{
		unsigned m_value;
		std::vector<Node*> m_children;

		// Set a default value in order to build the initial Uneven_Tree and also debug easier.
		explicit Node(unsigned value = 0)
			: m_value(value)
		{ }
	} *m_root;

	size_t m_size;

	void clear(Node*& n);

	void serialize_helper(std::string& str, Node* node) const;
	Node* deserialize_helper(Queue<std::string>& q, Node*& node);

	bool is_gracious(std::vector<unsigned>& elements, Node* node);

public:
	Uneven_Tree();
	Uneven_Tree(const Uneven_Tree& rhs) = delete;
	Uneven_Tree& operator=(const Uneven_Tree& rhs) = delete;
	~Uneven_Tree();

	size_t size() const;

	void serialize(const char* file) const;
	void deserialize(const char* file);

	bool is_gracious(std::vector<unsigned> elements);
};