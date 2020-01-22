#pragma once

///
/// Store the differences in a binary search tree. If a difference repeats, signal by returning false on insert.
///

class BST
{
private:
	struct Node
	{
		unsigned m_value;
		Node* m_left;
		Node* m_right;

		Node(unsigned value, Node* left = nullptr, Node* right = nullptr)
			: m_value(value),
			m_left(left),
			m_right(right)
		{ }
	} *m_root;

	void clear(Node*& node);

	bool insert(unsigned value, Node*& node);

public:
	BST();
	BST(const BST& rhs) = delete;
	BST& operator=(const BST& rhs) = delete;
	~BST();

	///
	/// Returns false, if element is already present.
	///
	bool insert(unsigned value);
};