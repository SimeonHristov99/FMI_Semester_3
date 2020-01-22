#pragma once

class AVL
{
private:
	struct Node
	{
		size_t m_height;
		int m_balance_factor;
		unsigned m_value;


		Node* m_left;
		Node* m_right;

		Node(unsigned value, size_t height = 0, int balance = 0, Node* left = nullptr, Node* right = nullptr)
			: m_height(height),
			m_balance_factor(balance),
			m_value(value),
			m_left(left),
			m_right(right)
		{ }
	} *m_root;

	void clear(Node* n);

	int height()
	{
		if (m_root == nullptr)
		{
			return 0;
		}

		return m_root->m_height;
	}

	Node* rotate_left(Node* node);
	Node* rotate_right(Node* node);

	Node* left_left(Node* node);
	Node* left_right(Node* node);
	Node* right_right(Node* node);
	Node* right_left(Node* node);

	Node* balance(Node* node);

	void update(Node* node);
	bool insert(unsigned value, Node*& node);

	void print(Node* node) const;

public:
	AVL();
	AVL(const AVL& rhs) = delete;
	AVL& operator=(const AVL& rhs) = delete;
	~AVL();

	bool insert(unsigned value); // Time complexity: O(log(n))

	void print() const;
};